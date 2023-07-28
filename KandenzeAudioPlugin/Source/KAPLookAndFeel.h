/*
  ==============================================================================

    KAPLookAndFeel.h
    Created: 28 Jul 2023 11:33:07pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPLookAndFeel : public juce::LookAndFeel_V4
{
public:
    KAPLookAndFeel()
    {
        // ComboBox Colors
        setColour(juce::ComboBox::backgroundColourId, KAPColour_3);
        setColour(juce::ComboBox::outlineColourId, KAPColour_2);
        setColour(juce::ComboBox::arrowColourId, KAPColour_1);
        setColour(juce::ComboBox::textColourId, KAPColour_1);

        // TextButton Colors
        setColour(juce::TextButton::buttonColourId, KAPColour_1);
        setColour(juce::TextButton::textColourOnId, KAPColour_1);
        setColour(juce::TextButton::textColourOffId, KAPColour_1);
    };

    virtual ~KAPLookAndFeel() {};


    // BUTTONS

    juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override
    {
        return font_1;
    }

    void drawButtonBackground(juce::Graphics& g,
        juce::Button& button,
        const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override
    {
        juce::Colour fillColor;

        if (shouldDrawButtonAsDown)
        {
            fillColor = KAPColour_5;
        }
        else if (shouldDrawButtonAsHighlighted)
        {
            fillColor = KAPColour_3;
        }

        const float cornerSize = 6.0f;
        const juce::Rectangle<float> bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

        g.setColour(fillColor);
        g.fillRoundedRectangle(bounds.reduced(1), cornerSize);
    }

    // COMBOBOXES

    juce::Font getLabelFont(juce::Label& label) override
    {
        return font_1;
    }

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
        const juce::String& text, const juce::String& shortcutKeyText,
        const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        juce::Rectangle<int> r(area);

        juce::Colour fillColor = isHighlighted ? KAPColour_5 : KAPColour_4;
        g.setColour(fillColor);

        g.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1);
        juce::Colour textColor = isTicked ? KAPColour_7 : KAPColour_1;
        g.setColour(textColor);
        g.setFont(font_1);

        r.setLeft(10);
        r.setY(1);
        g.drawFittedText(text, r, juce::Justification::left, 1);
    }

    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        juce::ComboBox& box) override
    {
        const float cornerSize = 3.0f;
        const juce::Rectangle<int> boxBounds(0, 0, width, height);

        g.setColour(KAPColour_3);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

        juce::Rectangle<int> arrow(width - 30, 0, 20, height);

        juce::Path path;

        path.startNewSubPath(arrow.getX() + 3.0f, arrow.getCentreY() - 2.0f);
        path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.0f);
        path.lineTo(arrow.toFloat().getRight() - 3.0f, arrow.toFloat().getCentreY() - 2.0f);

        juce::Colour arrowColor = box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
        g.setColour(arrowColor);
        g.strokePath(path, juce::PathStrokeType(2.0f));
    }

private:

};