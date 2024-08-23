/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CCMkIAudioProcessorEditor::CCMkIAudioProcessorEditor (CCMkIAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), isInitialized(false)
{
    prepareBackground();

    prepareSliders();
    prepareButtons();
    prepareLabels();
    prepareMeters();
    prepareCombos();

    setSize (745, 220);

    startTimerHz(30);
}

CCMkIAudioProcessorEditor::~CCMkIAudioProcessorEditor()
{
    presetsListCombo.removeListener(this);
    inputSlider.setLookAndFeel(nullptr);
    thresholdSlider.setLookAndFeel(nullptr);
    attackSlider.setLookAndFeel(nullptr);
    releaseSlider.setLookAndFeel(nullptr);
    outputSlider.setLookAndFeel(nullptr);
    ratio16Button.setLookAndFeel(nullptr);
    ratio4Button.setLookAndFeel(nullptr);
    ratio2Button.setLookAndFeel(nullptr);

}

//==============================================================================
void CCMkIAudioProcessorEditor::timerCallback()
{
    addAndMakeVisible(viewOne);

    levelMeterL.setLevels(audioProcessor.getRmsValue(0));
    levelMeterR.setLevels(audioProcessor.getRmsValue(1));
    levelMeterL.repaint();
    levelMeterR.repaint();
    

    rmsLabelL.setText(juce::String(std::round(audioProcessor.getRmsValue(0) * 10.0f) / 10.0f)+ " RMS" , juce::dontSendNotification);
    rmsLabelL.setColour(juce::Label::ColourIds::textColourId, juce::Colour(55, 58, 65));
    addAndMakeVisible(rmsLabelL);

    rmsLabelR.setText(juce::String(std::round(audioProcessor.getRmsValue(1) * 10.0f) / 10.0f)+ " RMS", juce::dontSendNotification);
    rmsLabelR.setColour(juce::Label::ColourIds::textColourId, juce::Colour(55, 58, 65));
    addAndMakeVisible(rmsLabelR);
}

void CCMkIAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour(20,23,28));
}


void CCMkIAudioProcessorEditor::resized()
{
    backgroundComponent.setBounds(getLocalBounds());

    //inputSlider.setBoundsToFit(juce::Rectangle<int>(0, 0, 100, 100), juce::Justification::centred, false);
    inputSlider.setBounds       (juce::Rectangle<int>(10, 60, 100, 100));
    thresholdSlider.setBounds   (juce::Rectangle<int>(225, 75, 70, 70));
    attackSlider.setBounds      (juce::Rectangle<int>(335, 30, 70, 70));
    releaseSlider.setBounds     (juce::Rectangle<int>(335, 120, 70, 70));
    outputSlider.setBounds      (juce::Rectangle<int>(445, 60, 100, 100));

    ratio16Button.setBounds     (juce::Rectangle<int>(150, 55, 35, 35));
    ratio4Button.setBounds      (juce::Rectangle<int>(150, 90, 35, 35));
    ratio2Button.setBounds      (juce::Rectangle<int>(150, 125, 35, 35));

    presetsListCombo.setBounds  (juce::Rectangle<int>(210, 170, 100, 20));

    inputLabel.setBounds        (juce::Rectangle<int>(38, 155, 50, 20));
    thresholdLabel.setBounds    (juce::Rectangle<int>(225, 140, 80, 20));
    attackLabel.setBounds       (juce::Rectangle<int>(346, 15, 50, 20));
    releaseLabel.setBounds      (juce::Rectangle<int>(343, 185, 55, 20));
    ratioLabel.setBounds        (juce::Rectangle<int>(147, 35, 50, 20));
    outputLabel.setBounds       (juce::Rectangle<int>(469, 155, 50, 20));
    
    rmsLabelL.setBounds         (juce::Rectangle<int>(625, 165, 65, 15));
    rmsLabelR.setBounds         (juce::Rectangle<int>(625, 185, 65, 15));

    levelMeterL.setBounds       (juce::Rectangle<int>(585, 165, 140, 15));
    levelMeterR.setBounds       (juce::Rectangle<int>(585, 185, 140, 15));

    viewOne.setBounds           (juce::Rectangle<int>(585, 20, 140, 135));
}


void CCMkIAudioProcessorEditor::prepareBackground()
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    backgroundComponent.setImage(backgroundImage);
    addAndMakeVisible(backgroundComponent);
}

void CCMkIAudioProcessorEditor::prepareSliders()
{
    //input
    inputSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    inputSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    inputSlider.setLookAndFeel(&knobLookAndFeel);

    //inputSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(189, 185, 183));
    //inputSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(182, 68, 66));
    //inputSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(29, 86, 101));

    //threshold
    thresholdSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    thresholdSlider.setLookAndFeel(&knobLookAndFeel3);
    //thresholdSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(189, 185, 183));
    //thresholdSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(29, 86, 101));
    //thresholdSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(182, 68, 66));

    //attack
    attackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.setLookAndFeel(&knobLookAndFeel2);
    //attackSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(189, 185, 183));
    //attackSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(29, 86, 101));
    //attackSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(182, 68, 66));

    //release
    releaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.setLookAndFeel(&knobLookAndFeel2);
    //releaseSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(189, 185, 183));
    //releaseSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(29, 86, 101));
    //releaseSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(182, 68, 66));

    //output
    outputSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    outputSlider.setLookAndFeel(&knobLookAndFeel4);
    //outputSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(189, 185, 183));
    //outputSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(29, 86, 101));
    //outputSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(182, 68, 66));

    //Make Visible
    addAndMakeVisible(inputSlider);
    addAndMakeVisible(thresholdSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(outputSlider);
    
    //Attachment to apvts
    inputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "input", inputSlider);
    thresholdAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "threshold", thresholdSlider);
    attackAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    releaseAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    outputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "output", outputSlider);
}

void CCMkIAudioProcessorEditor::prepareButtons()
{
    //ratio16
    //ratio16Button.setButtonText("16");
    ratio16Button.setLookAndFeel(&button16LookAndFeel);
    //ratio16Button.setColour(juce::TextButton::buttonColourId, juce::Colour(20, 23, 28));
    //ratio16Button.setColour(juce::TextButton::buttonOnColourId, juce::Colour(20, 23, 28));
    //ratio16Button.setColour(juce::TextButton::textColourOffId, juce::Colour(189, 185, 183));
    //ratio16Button.setColour(juce::TextButton::textColourOnId, juce::Colour(182, 68, 66));
    ratio16Button.setClickingTogglesState(true);
    
    //ratio4
    //ratio4Button.setButtonText("4");
    ratio4Button.setLookAndFeel(&button4LookAndFeel);
    //ratio4Button.setColour(juce::TextButton::buttonColourId, juce::Colour(20, 23, 28));
    //ratio4Button.setColour(juce::TextButton::buttonOnColourId, juce::Colour(20, 23, 28));
    //ratio4Button.setColour(juce::TextButton::textColourOffId, juce::Colour(189, 185, 183));
    //ratio4Button.setColour(juce::TextButton::textColourOnId, juce::Colour(182, 68, 66));
    ratio4Button.setClickingTogglesState(true);

    //ratio2
    //ratio2Button.setButtonText("2");
    ratio2Button.setLookAndFeel(&button2LookAndFeel);
    //ratio2Button.setColour(juce::TextButton::buttonColourId, juce::Colour(20, 23, 28));
    //ratio2Button.setColour(juce::TextButton::buttonOnColourId, juce::Colour(20, 23, 28));
    //ratio2Button.setColour(juce::TextButton::textColourOffId, juce::Colour(189, 185, 183));
    //ratio2Button.setColour(juce::TextButton::textColourOnId, juce::Colour(182, 68, 66));
    ratio2Button.setClickingTogglesState(true);

    //Make Visible
    addAndMakeVisible(ratio16Button);
    addAndMakeVisible(ratio4Button);
    addAndMakeVisible(ratio2Button);
    
    //Attachment
    ratio16Attach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "ratio16", ratio16Button);
    ratio4Attach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "ratio4", ratio4Button);
    ratio2Attach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "ratio2", ratio2Button);

}

void CCMkIAudioProcessorEditor::prepareLabels()
{


    inputLabel.setText("Input", juce::dontSendNotification);
    inputLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour(189, 185, 183));
    //inputLabel.setJustificationType(juce::Justification&inputSlider)
    addAndMakeVisible(inputLabel);

    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.setColour(juce::Label::ColourIds::textColourId ,juce::Colour(55, 58, 65));
    addAndMakeVisible(thresholdLabel);

    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour(55, 58, 65));
    addAndMakeVisible(attackLabel);

    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour(55, 58, 65));
    addAndMakeVisible(releaseLabel);

    ratioLabel.setText("Ratio", juce::dontSendNotification);
    ratioLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour(55, 58, 65));
    addAndMakeVisible(ratioLabel);

    outputLabel.setText("Output", juce::dontSendNotification);
    outputLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour(189, 185, 183));
    addAndMakeVisible(outputLabel);
}

void CCMkIAudioProcessorEditor::prepareMeters()
{
    addAndMakeVisible(levelMeterL);
    addAndMakeVisible(levelMeterR);
}

void CCMkIAudioProcessorEditor::prepareCombos()
{
    presetsListCombo.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour(20, 23, 28));
    presetsListCombo.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour(182, 68, 66));
    presetsListCombo.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colour(189, 185, 183));
    
    presetsListCombo.addItem("MyConfig", 1);
    presetsListCombo.addItem("Sudaka", 2);
    presetsListCombo.addItem("Orangine", 3);
    presetsListCombo.addItem("Glue", 4);
    presetsListCombo.addItem("Colour", 5);
    presetsListCombo.setSelectedId(1);
    presetsListCombo.addListener(this);
    addAndMakeVisible(presetsListCombo);

    presetsListCombo.setSelectedItemIndex(audioProcessor.getCurrentPresetIndex(), juce::dontSendNotification);
    showEditor();
    //presetsListAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "presetList", presetsListCombo);
}

void CCMkIAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (isInitialized && comboBoxThatHasChanged == &presetsListCombo)
    {
        int presetIndex = presetsListCombo.getSelectedItemIndex();
        audioProcessor.loadPreset(presetIndex);
    }
    //if (contListenerCalls > 0) 
    //{
    //    switch (presetsListCombo.getSelectedId())
    //    {
    //    case 1:
    //        audioProcessor.apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(3.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-12.0f, -100.0f, 0.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.008f, 0.00002f, 0.008f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.575f, 0.05f, 1.10f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("ratio16")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("ratio4")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("ratio2")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(3.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        break;
    //    case 2:
    //        audioProcessor.apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(0.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-15.0f, -100.0f, 0.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.0016f, 0.00002f, 0.008f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.3125f, 0.05f, 1.10f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("ratio16")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("ratio4")->setValueNotifyingHost(0);
    //        audioProcessor.apvts.getParameter("ratio2")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(-3.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        break;
    //    case 3:
    //        audioProcessor.apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(0.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-10.0f, -100.0f, 0.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.008f, 0.00002f, 0.008f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.575f, 0.05f, 1.10f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("ratio16")->setValueNotifyingHost(0);
    //        audioProcessor.apvts.getParameter("ratio4")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("ratio2")->setValueNotifyingHost(0);
    //        audioProcessor.apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(-3.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        break;
    //    case 4:
    //        audioProcessor.apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(10.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(5.0f, -100.0f, 0.0f, 0.0f, 1.0f));
    //        audioProcessor.apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.002f, 0.00002f, 0.008f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.525f, 0.05f, 1.10f, 1.0f, 0.0f));
    //        audioProcessor.apvts.getParameter("ratio16")->setValueNotifyingHost(0);
    //        audioProcessor.apvts.getParameter("ratio4")->setValueNotifyingHost(0);
    //        audioProcessor.apvts.getParameter("ratio2")->setValueNotifyingHost(1);
    //        audioProcessor.apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(-10.0f, -42.0f, 12.0f, 0.0f, 1.0f));
    //        break;
    //    }
    //}
    //contListenerCalls++;
}

void CCMkIAudioProcessorEditor::showEditor()
{
    isInitialized = true;
}