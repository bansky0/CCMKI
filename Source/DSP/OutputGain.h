/*
  ==============================================================================

    GainOutput.h
    Created: 23 Apr 2024 1:21:13pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OutputGain
{
public:
	OutputGain();
	~OutputGain();

    void setOutputGain(float inGainValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float outputValue{0};
};
