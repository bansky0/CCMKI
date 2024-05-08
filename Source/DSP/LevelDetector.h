/*
  ==============================================================================

    LevelDetector.h
    Created: 18 Apr 2024 1:19:44pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LevelDetector
{
public:
	LevelDetector();
	~LevelDetector();

    void process(juce::AudioBuffer<float>& buffer);

private:

};

