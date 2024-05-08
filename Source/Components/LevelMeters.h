/*
  ==============================================================================

    LevelMeters.h
    Created: 1 May 2024 3:20:35pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LevelMeters : public juce::Component
{
public:

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        g.setColour(juce::Colours::white.withBrightness(0.4f));
        g.fillRoundedRectangle(bounds, 5.0f);

        g.setColour(juce::Colours::white);

        const auto scaledX = juce::jmap(level, -48.0f, 0.0f, 0.0f, static_cast<float>(getWidth())); //rescale rectangle with new values. RMS to linear.
        g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.0f);
    }

    void setLevels(const float value)
    {
        level = value;
    }
private:
    float level = -60.0f;
};