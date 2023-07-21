/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 20 Jul 2023 10:39:13pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class KAPParameterComboBox : public juce::ComboBox
{
public:
    KAPParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID);
    ~KAPParameterComboBox();

private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterComboBox)
};