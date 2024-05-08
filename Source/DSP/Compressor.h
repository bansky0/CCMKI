/*
  ==============================================================================

    Compressor.h
    Created: 19 Apr 2024 3:44:29pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Compressor
{
public:
	Compressor();
	~Compressor();

   void process(juce::AudioBuffer<float>& buffer);

   void setThreshold(float inThresholdValue);
   void setRatios(bool inRatio16Value, bool inRatio4Value, bool inRatio2Value);

   //void setKnee(float inKneeValue);
   void setAttack(float inAttackValue);
   void setRelease(float inRleaseValue);

   void prepare(double inSampleRate);
   //void update();
private:
    float thresholdValue = -10.0f;
    float ratioValue = 2.0f;
    bool  ratio16Value = false;
    bool  ratio4Value = false;
    bool  ratio2Value = false;
    //float kneeValue = 4.0f;
    
    double sampleRate = 48000.0f;
    //float Ts = 1 / static_cast<float>(sampleRate);

    float gain = 0.0f;
    
    //float responseTime = 0.25; // time in seconds
    //float alpha = exp(-log(9) / (static_cast<float>(sampleRate) * responseTime));
    float attackValue = 0.05f;
    float releaseValue = 0.25f;
    float gainSmoothPrev = 0.0f;// Initializa variable
    float gainSmooth = 0.0f;

    //float attackTime = 0.05f;
    //float releaseTime = 0.25f;
    
};