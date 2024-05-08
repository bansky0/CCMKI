/*
  ==============================================================================

    SmoothingFilter.h
    Created: 20 Apr 2024 10:30:32am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SmoothFilter
{
public:
	SmoothFilter();
	~SmoothFilter();


    void process(juce::AudioBuffer<float>& buffer) const;

    void setThreshold(float inThresholdValue);
    void setRatio(float inRatioValue);
    void setKnee(float inKneeValue);

    void prepare(double inSampleRate);
    void update();

private:
    float thresholdValue = -10.0f;
    float ratioValue = 2.0f;
    float kneeValue = 4.0f;

    double sampleRate = 48000.0f;
    float Ts = 1 / static_cast<float>(sampleRate);

    float responseTime = 0.25; // time in seconds
    float alpha = exp(-log(9) / (static_cast<float>(sampleRate) * responseTime));
    float gainSmoothPrev = 0.0f;// Initialize smoothing variable

    float attackTime = 0.05f;
    float releaseTime = 0.25f;
    float alphaA = std::expf(-log(9) / (static_cast<float>(sampleRate) * attackTime));
    float alphaR = std::expf(-log(9) / (static_cast<float>(sampleRate) * releaseTime));
};

