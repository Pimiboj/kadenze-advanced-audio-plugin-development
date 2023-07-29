/*
  ==============================================================================

    KAPHelperFunctions.h
    Created: 23 Jul 2023 9:07:27pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "KAPInterfaceDefines.h"
#include "KAPLookAndFeel.h"

inline void paintComponentLabel(juce::Graphics& g, juce::Component* inComponent)
{
    const int x = inComponent->getX() - 0.25f * inComponent->getWidth();
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth() * 1.5f;
    const int h = 20;
    const float cornerSize = 3.0f;
    const juce::String label = inComponent->getName();

    KAPLookAndFeel look;

    g.setColour(KAPColour_3);
    g.fillRoundedRectangle(x, y, w, h, cornerSize);

    g.setColour(KAPColour_1);
    g.setFont(look.GetFont(1));

    g.drawFittedText(label, x, y, w, h, juce::Justification::centred, 1);
}