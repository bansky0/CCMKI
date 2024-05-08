/*
  ==============================================================================

    Gain.h
    Created: 17 Apr 2024 10:48:20pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Gain
{
public:
	Gain();
	~Gain();

    void setGainValue(float inGainValue);
    void setG(bool inRatio16Value, bool inRatio4Value, bool inRatio2Value);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float gainValue{ 0.0f };
    float g{ 1.0f };
    bool  ratio16Value = false;
    bool  ratio4Value = false;
    bool  ratio2Value = false;
};