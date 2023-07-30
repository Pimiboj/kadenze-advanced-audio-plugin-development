/*
  ==============================================================================

    KAPVuMeter.h
    Created: 30 Jul 2023 5:22:24pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class KAPVuMeter : public juce::Component, public juce::Timer
{
public:
    KAPVuMeter(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPVuMeter();

    void paint(juce::Graphics& g) override;

    void timerCallback() override;

    void SetParameterID(int inParameterID);

private:
    int mParameterID;

    float mCh0Level;
    float mCh1Level;
    KandenzeAudioPluginAudioProcessor* mProcessor;
};