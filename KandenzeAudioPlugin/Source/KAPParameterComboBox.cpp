/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 20 Jul 2023 10:39:13pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID)
    : juce::ComboBox(parameterID)
{
    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(stateToControl, parameterID, *this);
}

KAPParameterComboBox::~KAPParameterComboBox()
{

}