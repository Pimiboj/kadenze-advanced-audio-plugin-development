/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 20 Jul 2023 10:39:00pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterSlider : public juce::Slider
{
public:
    KAPParameterSlider(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID);
    ~KAPParameterSlider();

private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterSlider)
};