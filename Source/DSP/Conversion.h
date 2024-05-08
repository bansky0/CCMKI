/*
  ==============================================================================

    Conversion.h
    Created: 18 Apr 2024 3:44:44pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Conversion
{
public:
    Conversion();
	~Conversion();

    void process(juce::AudioBuffer<float>& buffer) const;

private:

};
