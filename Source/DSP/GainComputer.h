/*
  ==============================================================================

    GainComputer.h
    Created: 18 Apr 2024 4:16:03pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainComputer
{
public:
	GainComputer();
	~GainComputer();

    void setThreshold(float inThresholdValue);
    void setRatio(float inRatioValue);
    //void attack(float inTauAttackValue);
    //void release(float inTauReleaseValue);

    void process(juce::AudioBuffer<float>& buffer) const;


private:
    float thresholdValue{}; // Compressor thresh. in dB
    float ratioValue{}; // Compression ratio
    float tauAttackValue{}, tauRelease{}; // Attack and release time
    float knee{ 4.0f };
};

