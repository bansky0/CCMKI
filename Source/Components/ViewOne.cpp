/*
  ==============================================================================

    ViewOne.cpp
    Created: 1 May 2024 9:59:45pm
    Author:  Jhonatan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ViewOne.h"

//==============================================================================
ViewOne::ViewOne(CCMkIAudioProcessor& p) : audioProcessor(p)
{
    addAndMakeVisible(audioVisualiserComponent);
    
    bufferSizeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    bufferSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    bufferSizeSlider.setLookAndFeel(&faderViewSlider);
    addAndMakeVisible(bufferSizeSlider);

    //bufferSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    bufferSizeSlider.setRange(32, 128);
    bufferSizeSlider.onValueChange = [this]
        {
            audioVisualiserComponent.setBufferSize(bufferSizeSlider.getValue());
        };

    startTimerHz(30);
}

ViewOne::~ViewOne()
{
    stopTimer();
}

void ViewOne::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::white.withBrightness(0.4f));
    auto bounds = getLocalBounds().toFloat();

    g.setColour(juce::Colours::white.withBrightness(0.4f));
    g.fillRoundedRectangle(bounds, 5.0f);

}

void ViewOne::resized()
{
    audioVisualiserComponent.setBounds(5, 5, getWidth()-10, getHeight()-30);
    bufferSizeSlider.setBounds(5, getHeight() - 20, getWidth() - 10, 15);
}
void ViewOne::timerCallback()
{
    audioVisualiserComponent.pushBuffer(audioProcessor.samples);
}