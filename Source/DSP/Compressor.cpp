/*
  ==============================================================================

    Compressor.cpp
    Created: 19 Apr 2024 3:44:29pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Compressor.h"

Compressor::Compressor()
{
}

Compressor::~Compressor()
{
}
void Compressor::setThreshold(float inThresholdValue)
{
    thresholdValue = inThresholdValue;
}
void Compressor::setRatios(bool inRatio16Value, bool inRatio4Value, bool inRatio2Value)
{
    ratio16Value = inRatio16Value;
    ratio4Value = inRatio4Value;
    ratio2Value = inRatio2Value;

    if (ratio16Value && ratio4Value && ratio2Value)
    {
        ratioValue = 12.0f;
    }
    else if (ratio16Value && ratio4Value)
    {
        ratioValue = 20.0f;
    }
    else if (ratio16Value && ratio2Value)
    {
        ratioValue = 8.0f;
    }
    else if (ratio4Value && ratio2Value)
    {
        ratioValue = 6.0f;
    }
    else if (ratio16Value)
    {
        ratioValue = 16.0f;
    }
    else if (ratio4Value)
    {
        ratioValue = 4.0f;
    }
    else if (ratio2Value)
    {
        ratioValue = 2.0f;
    }
    else
    {
        ratioValue = 1.0f;
    }

}
void Compressor::setAttack(float inAttackValue)
{
    attackValue = inAttackValue;
}
void Compressor::setRelease(float inReleaseValue)
{
    releaseValue = inReleaseValue;
}
void Compressor::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
}
void Compressor::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);

            //conversión a dB.
            float processesedSample = 20.0f * std::log10(std::fabs (inSample)); 
            if (processesedSample < -100.0f) //Ruido de fondo.
            {
                processesedSample = -100.0f;
            }

            if (processesedSample > (thresholdValue)) //condición para comprimir
            {
                gain = thresholdValue + (processesedSample - thresholdValue) / ratioValue; //compresion
            }
            else //No comprime
            {
                gain = processesedSample;
            }
            
            float gainChange = gain - processesedSample;
            float alphaA = std::expf(-logf(9.0f) / (static_cast<float>(sampleRate) * attackValue));
            float alphaR = std::expf(-logf(9.0f) / (static_cast<float>(sampleRate) * releaseValue));

            if (gainChange < gainSmoothPrev) //attack
            {
                gainSmooth = ((1.0f - alphaA) * gainChange) + (alphaA * gainSmoothPrev);
            }
            else //release
            {
                gainSmooth = ((1.0f - alphaR) * gainChange) + (alphaR * gainSmoothPrev);
            }
            
            float gainLineal = std::powf(10.0f, gainSmooth * 0.05f); //conversion de db a lineal.
            float output = gainLineal * inSample;
            gainSmoothPrev = gainSmooth;
            buffer.setSample(channel, i, output);
        }
    }
}