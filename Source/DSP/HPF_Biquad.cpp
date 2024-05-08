/*
  ==============================================================================

    HPF_Biquad.cpp
    Created: 21 Mar 2024 10:58:22pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "HPF_Biquad.h"

HPF_Biquad::HPF_Biquad() {}

HPF_Biquad::~HPF_Biquad() {}

void HPF_Biquad::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); //necesita actualizar porque el filtro depende delos coeficientes y estos del sample rate.
}

void HPF_Biquad::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float inSample = inBuffer.getSample(channel, i);

            float outSample = processSample(inSample, channel);

            inBuffer.setSample(channel, i, outSample);
        }
    }
}
float HPF_Biquad::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
}

void HPF_Biquad::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}
void HPF_Biquad::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void HPF_Biquad::updateFilter()
{
    //calcular coeficientes apra un HPF
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    b0 = (1.0f + cosf(w0)) / 2.0f;
    b1 = -(1.0f + cosf(w0)); //ojo la tabal de tark no muestra que se debe implementar el filtro asi.
    b2 = (1.0f + cosf(w0)) / 2.0f;

    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;
}
