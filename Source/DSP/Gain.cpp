/*
  ==============================================================================

    Gain.cpp
    Created: 17 Apr 2024 10:48:20pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain()
{
}
Gain::~Gain()
{
}
void Gain::setGainValue(float inGainValue)
{
    gainValue = juce::Decibels::decibelsToGain(inGainValue);
}
void Gain::setG(bool inRatio16Value, bool inRatio4Value, bool inRatio2Value)
{
    ratio16Value = inRatio16Value;
    ratio4Value = inRatio4Value;
    ratio2Value = inRatio2Value;

    if (ratio16Value && ratio4Value && ratio2Value)
    {
        g = 2.5f;
    }
    else
    {
        g = 1.0f;
    }
}
void Gain::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            //float processesedSample = ((2.0f / juce::MathConstants<float>::pi) * atanf(inSample * g) * gainValue);//std::tanh(inSample * gainValue);//std::clamp(inSample * gainValue, -1.0f, 1.0f);
            float processesedSample = 0.0f;
            //Condiciónes para generar distorsión.
            if (inSample >=0) 
            {
                processesedSample = 1 - expf(-fabs(g * inSample * gainValue));
            }
            else
            {
                processesedSample = -(1 - expf(-fabs(g * inSample * gainValue)));
            }
            buffer.setSample(channel, i, processesedSample);
        }
    }
}