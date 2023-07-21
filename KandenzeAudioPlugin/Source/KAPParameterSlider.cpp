/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 20 Jul 2023 10:39:00pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPParameterSlider.h"

KAPParameterSlider::KAPParameterSlider(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID)
    : juce::Slider(parameterID)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);

    setRange(0.0f, 1.0f, 0.001f);

    mAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(stateToControl, parameterID, *this);
}

KAPParameterSlider::~KAPParameterSlider()
{

}