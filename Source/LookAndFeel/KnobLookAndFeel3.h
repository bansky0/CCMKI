/*
  ==============================================================================

    KnobLookAndFeel3.h
    Created: 30 Apr 2024 12:58:23am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class KnobLookAndFeel3 : public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel3()
    {
        knobImage = juce::ImageCache::getFromMemory(BinaryData::knob_T_png, BinaryData::knob_T_pngSize);
    }
    ~KnobLookAndFeel3()
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