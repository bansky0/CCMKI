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
        faderImage = juce::ImageCache::getFromMemory(BinaryData::faderView2_png, BinaryData::faderView2_pngSize);
    }
    ~FaderLookAndFeel()
    {

    }
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        juce::Slider::SliderStyle, juce::Slider&) override
    
    {
        //FILM STRIP
        const int numFrames = 101;
        const int frameIndex = (int)std::ceil(sliderPos * (numFrames - 1));

        g.drawImage(faderImage,
            x,
            y,
            width,
            height,
            0,
            frameIndex * faderImage.getWidth(),
            faderImage.getWidth(),
            faderImage.getHeight());
    }

private:
    juce::Image faderImage;
};