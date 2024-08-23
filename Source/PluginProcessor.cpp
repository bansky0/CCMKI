/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CCMkIAudioProcessor::CCMkIAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

CCMkIAudioProcessor::~CCMkIAudioProcessor()
{
}

int CCMkIAudioProcessor::getCurrentPresetIndex() const
{
    return currentPresetIndex;
}

void CCMkIAudioProcessor::loadPreset(int presetIndex)
{
    currentPresetIndex = presetIndex;

    switch (presetIndex)
    {
    case 1:
        apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(3.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-12.0f, -100.0f, 0.0f, 0.0f, 1.0f));
        apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.008f, 0.00002f, 0.008f, 1.0f, 0.0f));
        apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.575f, 0.05f, 1.10f, 1.0f, 0.0f));
        apvts.getParameter("ratio16")->setValueNotifyingHost(1);
        apvts.getParameter("ratio4")->setValueNotifyingHost(1);
        apvts.getParameter("ratio2")->setValueNotifyingHost(1);
        apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(-1.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        break;
    case 2:
        apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(-1.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-15.0f, -100.0f, 0.0f, 0.0f, 1.0f));
        apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.0016f, 0.00002f, 0.008f, 1.0f, 0.0f));
        apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.3125f, 0.05f, 1.10f, 1.0f, 0.0f));
        apvts.getParameter("ratio16")->setValueNotifyingHost(1);
        apvts.getParameter("ratio4")->setValueNotifyingHost(0);
        apvts.getParameter("ratio2")->setValueNotifyingHost(1);
        apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(4.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        break;
    case 3:
        apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(-6.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-10.0f, -100.0f, 0.0f, 0.0f, 1.0f));
        apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.008f, 0.00002f, 0.008f, 1.0f, 0.0f));
        apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.575f, 0.05f, 1.10f, 1.0f, 0.0f));
        apvts.getParameter("ratio16")->setValueNotifyingHost(0);
        apvts.getParameter("ratio4")->setValueNotifyingHost(1);
        apvts.getParameter("ratio2")->setValueNotifyingHost(0);
        apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(+7.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        break;
    case 4:
        apvts.getParameter("input")->setValueNotifyingHost(juce::jmap(10.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        apvts.getParameter("threshold")->setValueNotifyingHost(juce::jmap(-3.0f, -100.0f, 0.0f, 0.0f, 1.0f));
        apvts.getParameter("attack")->setValueNotifyingHost(juce::jmap(0.002f, 0.00002f, 0.008f, 1.0f, 0.0f));
        apvts.getParameter("release")->setValueNotifyingHost(juce::jmap(0.525f, 0.05f, 1.10f, 1.0f, 0.0f));
        apvts.getParameter("ratio16")->setValueNotifyingHost(0);
        apvts.getParameter("ratio4")->setValueNotifyingHost(0);
        apvts.getParameter("ratio2")->setValueNotifyingHost(1);
        apvts.getParameter("output")->setValueNotifyingHost(juce::jmap(-6.0f, -42.0f, 12.0f, 0.0f, 1.0f));
        break;
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout CCMkIAudioProcessor::createParameters()
{

    juce::AudioProcessorValueTreeState::ParameterLayout parameters;

    static const std::function<float(float rangeStart, float rangeEnd, float normalised)> convertFrom0To1Func
    {
        [](float rangeStart, float rangeEnd, float normalised)
        {
            return rangeStart+(1.0f-normalised)*(rangeEnd-rangeStart);
        },
    };

    static const std::function<float(float rangeStart, float rangeEnd, float normalised)> convertTo0To1Func
    {
        [](float rangeStart, float rangeEnd, float value)
        {
            return 1.0f-(value-rangeStart)/(rangeEnd - rangeStart);
        },
    };

    static const std::function<float(float rangeStart, float rangeEnd, float normalised)> snapToLegalValueFunc
    {
        [](float rangeStart, float rangeEnd, float value)
        {
            float stepSize = 0.00002f;
            return std::round((value - rangeStart) / stepSize) * stepSize + rangeStart;
        },
    };

    auto rangeAttack = juce::NormalisableRange<float>(0.00002f, 0.008f, convertFrom0To1Func, convertTo0To1Func, snapToLegalValueFunc);
    auto rangeRelease = juce::NormalisableRange<float>(0.05f, 1.10f, convertFrom0To1Func, convertTo0To1Func, snapToLegalValueFunc);
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "input", 1 }, "Input", juce::NormalisableRange<float>(-42.0f, 12.0f,0.01f), 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "threshold", 1 }, "Threshold", juce::NormalisableRange<float>(-100.0f, 0.0f, 1.0f), -10.0f));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "ratio16", 1 }, "Ratio16", false));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "ratio4", 1 }, "Ratio4", false));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "ratio2", 1 }, "Ratio2", false));
    //parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "knee", 1 }, "Knee", juce::NormalisableRange<float>(0.0f, 10.0f), 4.0f));
    //parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "attack", 1 }, "Attack", juce::NormalisableRange<float>(0.00002f, 0.008f, 0.00002f), 0.0008f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("attack", 1), "Attack", rangeAttack, 0.0008f));
    //parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "release", 1 }, "Release", juce::NormalisableRange<float>(0.05f, 1.1f, 0.001), 0.525f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("release", 1), "Release", rangeRelease, 0.525f));

    //parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "g", 1 }, "G", juce::NormalisableRange<float>(0.0f, 2.5f, 0.1), 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "output", 1 }, "Output", juce::NormalisableRange<float>(-42.0f, 12.0f,0.01f), 0.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{ "presetList", 1 }, "PresetList", juce::StringArray("Sudaka", "Orangine", "Glue", "Colour"), 0));
    
    return parameters;
}

//==============================================================================
const juce::String CCMkIAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CCMkIAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CCMkIAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CCMkIAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CCMkIAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CCMkIAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CCMkIAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CCMkIAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CCMkIAudioProcessor::getProgramName (int index)
{
    return {};
}

void CCMkIAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CCMkIAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    comp.prepare(getSampleRate());
    hpf.prepare(sampleRate);
    hpf.setFrequency(10.0f);
    hpf.setQ(0.5f);

    rmsLevelLeft.reset(sampleRate, 0.5);
    rmsLevelRight.reset(sampleRate, 0.5);

    rmsLevelLeft.setCurrentAndTargetValue(-100.0f);
    rmsLevelRight.setCurrentAndTargetValue(-100.0f);
}

void CCMkIAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CCMkIAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CCMkIAudioProcessor::updateParameters()
{
    float inInputParameter =     *apvts.getRawParameterValue("input");
    float inThresholdParameter = *apvts.getRawParameterValue("threshold");
    bool  inRatio16Parameter =   *apvts.getRawParameterValue("ratio16");
    bool  inRatio4Parameter =    *apvts.getRawParameterValue("ratio4");
    bool  inRatio2Parameter =    *apvts.getRawParameterValue("ratio2");
    float inAttackParameter =    *apvts.getRawParameterValue("attack");
    float inReleaseParameter =   *apvts.getRawParameterValue("release");
    //float inGParameter =         *apvts.getRawParameterValue("g");
    float inOutputParameter =    *apvts.getRawParameterValue("output");
    
    input.setGainValue  (inInputParameter);
    input.setG          (inRatio16Parameter, inRatio4Parameter, inRatio2Parameter);
    
    comp.setThreshold   (inThresholdParameter);
    
    comp.setRatios     (inRatio16Parameter, inRatio4Parameter, inRatio2Parameter);
    
    comp.setAttack      (inAttackParameter);
    comp.setRelease     (inReleaseParameter);
    output.setOutputGain(inOutputParameter);

}

void CCMkIAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateParameters();
    
    input.process(buffer);
    hpf.process(buffer);
    comp.process(buffer);
    output.process(buffer);
    //Level Meter Smooth
    rmsLevelLeft.skip(buffer.getNumSamples());
    rmsLevelRight.skip(buffer.getNumSamples());
    {
        const auto value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if (value < rmsLevelLeft.getCurrentValue())
        {
            rmsLevelLeft.setTargetValue(value);
        }
        else
        {
            rmsLevelLeft.setCurrentAndTargetValue(value);
        }
    }
    {
        const auto value = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
        if (value < rmsLevelRight.getCurrentValue())
        {
            rmsLevelRight.setTargetValue(value);
        }
        else
        {
            rmsLevelRight.setCurrentAndTargetValue(value);
        }
    }
    //rmsLevelLeft = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())); //Nivel Rms del canal Izquierdo
    //rmsLevelRight = juce::Decibels::gainToDecibels( buffer.getRMSLevel(1, 0, buffer.getNumSamples())); //Nivel Rms del canal Derecho

    samples = buffer;
}

//==============================================================================
bool CCMkIAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CCMkIAudioProcessor::createEditor()
{
    return new CCMkIAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void CCMkIAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<juce::XmlElement> xml(apvts.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void CCMkIAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(apvts.state.getType()))
        {
            auto state = juce::ValueTree::fromXml(*xmlState);
            apvts.replaceState(state);

            //DBG(state.toXmlString());
        }
    }
}

float CCMkIAudioProcessor::getRmsValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
    {
        return rmsLevelLeft.getCurrentValue();
    }
    if (channel == 1)
    {
        return rmsLevelRight.getCurrentValue();
    }
    else
    {
        return 0.0f;
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CCMkIAudioProcessor();
}
