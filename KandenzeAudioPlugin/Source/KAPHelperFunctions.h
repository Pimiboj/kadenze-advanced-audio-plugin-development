/*
  ==============================================================================

    KAPHelperFunctions.h
    Created: 23 Jul 2023 9:07:27pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

inline void paintComponentLabel(juce::Graphics& g, juce::Component* inComponent)
{
    const int x = inComponent->getX() - 0.25f * inComponent->getWidth();
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth() * 1.5f;
    const int h = 20;
    const juce::String label = inComponent->getName();

    g.setColour(juce::Colours::darkgrey);
    g.drawFittedText(label, x, y, w, h, juce::Justification::centred, 1);
}