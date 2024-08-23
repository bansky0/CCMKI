/*
  ==============================================================================

    SmoothingFilter.cpp
    Created: 20 Apr 2024 10:30:32am
    Author:  Jhonatan

  ==============================================================================
*/

#include "SmoothingFilter.h"

SmoothFilter::SmoothFilter()
{
}

SmoothFilter::~SmoothFilter()
{
}

void SmoothFilter::process(juce::AudioBuffer<float>& buffer) const
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);

            //conversión a dB.
            float processesedSample = 20.0f * std::log10(std::fabs(inSample));
            if (processesedSample < -120.0) //Ruido de fondo.
            {
                processesedSample = -120.0;
            }

            if (processesedSample > (thresholdValue))//(processesedSample > (thresholdValue + kneeValue/2.0f)) //condición para comprimir con valor de knee
            {
                float gain = thresholdValue + (processesedSample - thresholdValue) / ratioValue; //compresion
                //float gainLineal = std::pow(10.0, gain * 0.05); //conversion de db a lineal.
                //buffer.setSample(channel, i, gainLineal);
                float gainChange = gain - processesedSample;
                float gainSmooth = ((1 - alpha) * gainChange) + (alpha * gainSmoothPrev);
                float gainLineal = std::pow(10.0, gainSmooth * 0.05); //conversion de db a lineal.
                float output = gainLineal * inSample;
                float gainSmoothPrev = gainSmooth;
                buffer.setSample(channel, i, output);


                //float gainChange = processesedSample - gain; //diferencia entre entrada y compresion
                //if (gainChange < gainSmoothPrev)
                //{
                //    float gainSmooth = ((1 - alphaA) * gainChange) + (alphaA * gainSmoothPrev);
                //    float gainLineal = std::pow(10.0, gainSmooth * 0.05);
                //    float output = gainLineal * std::pow(10.0, processesedSample * 0.05);
                //    
                //    buffer.setSample(channel, i, output);
                //    float gainSmoothPrev = gainSmooth;
                //}
                //else
                //{
                //    float gainSmooth = ((1 - alphaR) * gainChange) + (alphaA * gainSmoothPrev);
                //    float gainLineal = std::pow(10.0, gainSmooth * 0.05);
                //    float output = gainLineal * std::pow(10.0, processesedSample * 0.05);
                //    
                //    buffer.setSample(channel, i, output);
                //    float gainSmoothPrev = gainSmooth;
                //}

            }
            //else if (processesedSample > (thresholdValue - kneeValue / 2.0f)) //condición2 para comprimir
            //{
            //    float gain = processesedSample + powf((1.0f / ratioValue - 1.0f) * (processesedSample - thresholdValue + kneeValue / 2.0f), 2.0f) / (2 * kneeValue);
            //    float gainLineal = std::pow(10.0, gain * 0.05);
            //    buffer.setSample(channel, i, gainLineal);
            //}
            else //No comprime
            {
                float gain = processesedSample;
                float gainLineal = std::pow(10.0, gain * 0.05);
                buffer.setSample(channel, i, gainLineal);
            }

        }
    }
}