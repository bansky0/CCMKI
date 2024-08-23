/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel/KnobLookAndFeel.h"
#include "LookAndFeel/KnobLookAndFeel2.h"
#include "LookAndFeel/KnobLookAndFeel3.h"
#include "LookAndFeel/KnobLookAndFeel4.h"
#include "LookAndFeel/Button16LookAndFeel.h"
#include "LookAndFeel/Button4LookAndFeel.h"
#include "LookAndFeel/Button2LookAndFeel.h"
#include "Components/LevelMeters.h"
#include "Components/ViewOne.h"

//==============================================================================
/**
*/
class CCMkIAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer, public juce::ComboBox::Listener //, juce::Slider::Listener
{
public:
    CCMkIAudioProcessorEditor (CCMkIAudioProcessor&);
    ~CCMkIAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

    void prepareBackground();
    void prepareSliders();
    void prepareButtons();
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void showEditor();
    void prepareLabels();
    void prepareMeters();
    void prepareCombos();

    //void sliderValueChanged(juce::Slider*) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    int contListenerCalls;

    CCMkIAudioProcessor& audioProcessor;
    bool isInitialized;

    juce::Slider inputSlider, thresholdSlider, attackSlider, releaseSlider, outputSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputAttach, thresholdAttach,attackAttach, releaseAttach, outputAttach;

    juce::TextButton ratio16Button, ratio4Button, ratio2Button;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> ratio16Attach, ratio4Attach, ratio2Attach;

    juce::ComboBox presetsListCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> presetsListAttach;

    juce::Label inputLabel, thresholdLabel, attackLabel, releaseLabel, ratioLabel, outputLabel, rmsLabelL,rmsLabelR;

    KnobLookAndFeel knobLookAndFeel;
    KnobLookAndFeel2 knobLookAndFeel2;
    KnobLookAndFeel3 knobLookAndFeel3;
    KnobLookAndFeel4 knobLookAndFeel4;
    Button16LookAndFeel button16LookAndFeel;
    Button4LookAndFeel button4LookAndFeel;
    Button2LookAndFeel button2LookAndFeel;

    juce::Image backgroundImage;
    juce::ImageComponent backgroundComponent;

    LevelMeters levelMeterL, levelMeterR;

    ViewOne viewOne{ audioProcessor };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CCMkIAudioProcessorEditor)
};
