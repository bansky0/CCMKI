/*
  ==============================================================================

    LevelDetector.cpp
    Created: 18 Apr 2024 1:19:44pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "LevelDetector.h"

LevelDetector::LevelDetector()
{
}

LevelDetector::~LevelDetector()
{
}

void LevelDetector::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            //Obtener la muestra de entrada
            float inSample = buffer.getSample(channel, i);
            float processesedSample = std::fabs(inSample); //valor absoluto de la entrada. Este valor se va a comparar.
            buffer.setSample(channel, i, processesedSample);
        }
    }
}