/*
  ==============================================================================

    FaderLookAndFeel.h
    Created: 6 May 2024 7:36:34pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FaderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    FaderLookAndFeel()
    {
        faderImage = juce::ImageCache::getFromMemory(BinaryData::faderView_png, BinaryData::faderView_pngSize);
    }
    ~FaderLookAndFeel()
    {

    }
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        juce::Slider::SliderStyle, juce::Slider& slider) override
    
    {
        //FILM STRIP
        const int numFrames = 101;
        const int relativePos = (int)juce::jmap<double>(slider.getValue(), slider.getMinimum(), slider.getMaximum(), 0.0, numFrames - 1);

        g.drawImage(faderImage,
            x,
            y,
            width,
            height,
            0,
            (faderImage.getHeight() / (int)numFrames) * (relativePos),
            faderImage.getWidth(),
            faderImage.getHeight() / (int)numFrames);
    }

private:
    juce::Image faderImage;
};