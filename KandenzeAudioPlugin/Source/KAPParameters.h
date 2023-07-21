/*
  ==============================================================================

    KAPParameters.h
    Created: 20 Jul 2023 10:00:54pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

enum KAPParameter
{
    kInputGain = 0,
    kDelayTime,
    kDelayFeedback,
    kDelayWetDry,
    kDelayType,
    kOutputGain,
    kModulationRate,
    kModulationDepth,
    kTotalNumParameters
};

static juce::String KAPParameterID[kTotalNumParameters] =
{
    "Input Gain",
    "Time",
    "Feedback",
    "Wet/Dry",
    "Type",
    "Output Gain",
    "Modulation Rate",
    "Modulation Depth"
};