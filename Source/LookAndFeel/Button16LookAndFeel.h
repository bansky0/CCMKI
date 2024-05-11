/*
  ==============================================================================

    ButtonLookAndFeel.h
    Created: 10 May 2024 5:01:21pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Button16LookAndFeel : public juce::LookAndFeel_V4
{
public:
    Button16LookAndFeel()
    {
        // Carga las imágenes
        imageOn = juce::ImageFileFormat::loadFrom(BinaryData::ratioOn16_png, BinaryData::ratioOn16_pngSize);
        imageOff = juce::ImageFileFormat::loadFrom(BinaryData::ratioOff16_png, BinaryData::ratioOff16_pngSize);
    }
    ~Button16LookAndFeel()
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
        juce::Image& buttonImage = button.getToggleState() ? imageOn : imageOff;
        g.drawImage(buttonImage, button.getLocalBounds().toFloat());

        // Obtiene el texto según el estado del botón y configura el color
        //juce::String buttonText = button.getToggleState() ? "Activado" : "Desactivado";
        //juce::Colour textColour = button.getToggleState() ? juce::Colours::green : juce::Colours::red;
        //g.setColour(textColour);
        ////g.setFont(button.getFont());
        //g.drawFittedText(buttonText, button.getLocalBounds(), juce::Justification::centred, 1);
    }

private:
    juce::Image imageOn;
    juce::Image imageOff;
};