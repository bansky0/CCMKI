/*
  ==============================================================================

    ViewOne.h
    Created: 1 May 2024 9:59:45pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../source/PluginProcessor.h"
#include "../LookAndFeel/FaderLookAndFeel.h"

//==============================================================================
/*
*/
class ViewOne  : public juce::Component, public juce::Timer
{
public:
    ViewOne(CCMkIAudioProcessor&);
    ~ViewOne() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    CCMkIAudioProcessor& audioProcessor;

    juce::Image backgroundView;
    juce::ImageComponent backgroundComponent;

    juce::AudioVisualiserComponent audioVisualiserComponent{ 2 };

    juce::Slider bufferSizeSlider;
    FaderLookAndFeel faderViewSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViewOne)
};
