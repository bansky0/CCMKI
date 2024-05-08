/*
  ==============================================================================

    GainOutput.cpp
    Created: 23 Apr 2024 1:21:13pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "OutputGain.h"

OutputGain::OutputGain()
{
}

OutputGain::~OutputGain()
{
}

void OutputGain::setOutputGain(float inGainValue)
{
    outputValue = juce::Decibels::decibelsToGain(inGainValue);
}

void OutputGain::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float processesedSample = inSample * outputValue;
            buffer.setSample(channel, i, processesedSample);
        }
    }
}