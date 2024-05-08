/*
  ==============================================================================

    PresetMang.h
    Created: 27 Apr 2024 12:03:59pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <Juceheader.h>

class PresetManager

{
public:
    PresetManager(juce::AudioProcessorValueTreeState& theApvts);
	~PresetManager();

    void savePreset();

private:
    juce::AudioProcessorValueTreeState& apvts;
};
