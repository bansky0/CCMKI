/*
  ==============================================================================

    Button4LookAndFeel.h
    Created: 10 May 2024 7:34:50pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Button4LookAndFeel : public juce::LookAndFeel_V4
{
public:
    Button4LookAndFeel()
    {
        // Carga las imágenes
        imageOn1 = juce::ImageFileFormat::loadFrom(BinaryData::ratioOn4_png, BinaryData::ratioOn4_pngSize);
        imageOff1 = juce::ImageFileFormat::loadFrom(BinaryData::ratioOff4_png, BinaryData::ratioOff4_pngSize);
    }
    ~Button4LookAndFeel()
    {

    }

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        juce::Colour buttonColour = backgroundColour.withBrightness(isButtonDown ? 0.8f : (isMouseOverButton ? 1.2f : 1.0f));
        g.fillAll(buttonColour);
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        juce::Image& buttonImage = button.getToggleState() ? imageOn1 : imageOff1;
        g.drawImage(buttonImage, button.getLocalBounds().toFloat());

        // Obtiene el texto según el estado del botón y configura el color
        //juce::String buttonText = button.getToggleState() ? "Activado" : "Desactivado";
        //juce::Colour textColour = button.getToggleState() ? juce::Colours::green : juce::Colours::red;
        //g.setColour(textColour);
        ////g.setFont(button.getFont());
        //g.drawFittedText(buttonText, button.getLocalBounds(), juce::Justification::centred, 1);
    }

private:
    juce::Image imageOn1;
    juce::Image imageOff1;
};