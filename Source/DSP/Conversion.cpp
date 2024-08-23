/*
  ==============================================================================

    Conversion.cpp
    Created: 18 Apr 2024 3:44:44pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Conversion.h"

Conversion::Conversion()
{
}

Conversion::~Conversion()
{
}

void Conversion::process(juce::AudioBuffer<float>& buffer) const 
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            //Obtener la muestra de entrada
            float inSample = buffer.getSample(channel, i);
            float processesedSample = 20.0f * std::log10(inSample); //conversión a dB.
            if (processesedSample< -120.0) //Ruido de fondo.
            {
                processesedSample = -120.0;
            }
            buffer.setSample(channel, i, processesedSample);           
        }
    }
}