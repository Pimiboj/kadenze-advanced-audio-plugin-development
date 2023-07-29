/*
  ==============================================================================

    KAPPanelBase.h
    Created: 18 Jul 2023 8:51:04pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "KAPInterfaceDefines.h"

class KAPPanelBase : public juce::Component
{
public:
    KAPPanelBase(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPPanelBase();

    void mouseEnter(const juce::MouseEvent& event) override;

    void mouseExit(const juce::MouseEvent& event) override;

    void paint(juce::Graphics& g) override;

protected:
    KandenzeAudioPluginAudioProcessor* mProcessor;
};