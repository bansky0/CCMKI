/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DSP/Gain.h"
#include "DSP/Compressor.h"
#include "DSP/OutputGain.h"
#include "DSP/HPF_Biquad.h"
#include "DSP/LPF_Biquad.h"

//==============================================================================
/**
*/
class CCMkIAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    CCMkIAudioProcessor();
    ~CCMkIAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts; //creo my objeto apvts
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters(); //crea metodo

    void updateParameters();

    float getRmsValue(const int channel) const;

    juce::AudioBuffer<float> samples;

private:
    HPF_Biquad hpf;
    LPF_Biquad lpf;
    Gain input;
    //bool ratio { false };
    Compressor comp;
    OutputGain output;

    juce::LinearSmoothedValue<float> rmsLevelLeft, rmsLevelRight; //valores rms que van a entrar al meter.
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CCMkIAudioProcessor)
};
