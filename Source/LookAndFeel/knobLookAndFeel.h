/*
  ==============================================================================

    knobLookAndFeel.h
    Created: 29 Apr 2024 11:54:19am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class KnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel()
    {
        knobImage = juce::ImageCache::getFromMemory(BinaryData::knob_input_png, BinaryData::knob_input_pngSize);
    }
    ~KnobLookAndFeel()
    {

    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override
    {
        //FILM STRIP
        const int numFrames = knobImage.getHeight() / knobImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));

        const float radius = fmin(width * 0.5, height * 0.5);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius;
        const float ry = centerY - radius;

        g.drawImage(knobImage,
            rx,
            ry,
            2 * radius,
            2 * radius,
            0,
            frameIndex * knobImage.getWidth(),
            knobImage.getWidth(),
            knobImage.getWidth());
    }

private:
    juce::Image knobImage;
};