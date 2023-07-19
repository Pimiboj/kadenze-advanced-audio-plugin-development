/*
  ==============================================================================

    KAPTopPanel.h
    Created: 18 Jul 2023 8:52:06pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel : public KAPPanelBase
{
public:
    KAPTopPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();

    void paint(juce::Graphics& g) override;

private:
};
