/*
  ==============================================================================

    GainComputer.cpp
    Created: 18 Apr 2024 4:16:03pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "GainComputer.h"

GainComputer::GainComputer()
{
}

GainComputer::~GainComputer()
{
}
void GainComputer::setThreshold(float inThresholdValue)
{
    float thresholdValue = inThresholdValue;
}

void GainComputer::setRatio(float inRatioValue)
{
    float ratioValue = inRatioValue;
}

void GainComputer::process(juce::AudioBuffer<float>& buffer) const
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            
            if (inSample > thresholdValue)
            {
                float gain = thresholdValue + (inSample - thresholdValue) / ratioValue;
                float gainLineal = juce::Decibels::decibelsToGain(gain); //std::pow(10.0, gain * 0.05);
                buffer.setSample(channel, i, gainLineal);
            }
            else
            {
                float gainLineal = juce::Decibels::decibelsToGain(inSample); //std::pow(10.0, inSample * 0.05);
                buffer.setSample(channel, i, gainLineal);
            }

            /*if (inSample > thresholdValue + (knee / 2))
            {
                float processesedSample = thresholdValue + (inSample - thresholdValue) / ratioValue;
                float output = std::pow(10.0, (inSample - processesedSample) * 0.05);

                buffer.setSample(channel, i, output);
            }
            else if (inSample >= thresholdValue - (knee / 2))
            {
                float processesedSample = inSample + (((1 / ratioValue) - 1) * powf(inSample - thresholdValue + (knee / 2),2) )/ (2 * knee);
                float output = std::pow(10.0, (inSample - processesedSample) * 0.05);
                buffer.setSample(channel, i, output);
            }
            else
            {
                float processesedSample = inSample;
                float output = std::pow(10.0, (processesedSample) * 0.05);
                buffer.setSample(channel, i, output);
            }*/
        }
    }
}