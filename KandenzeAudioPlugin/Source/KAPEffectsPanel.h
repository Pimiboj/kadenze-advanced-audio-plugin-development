/*
  ==============================================================================

    KAPEffectsPanel.h
    Created: 18 Jul 2023 8:51:41pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

enum KAPEffectsPanelStyle
{
    kDelay,
    kChorus,
    kTotalNumStyles
};

class KAPEffectsPanel : public KAPPanelBase
{
public:
    KAPEffectsPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPEffectsPanel();

    void paint(juce::Graphics& g) override;

    void setEffectsPanelStyle(KAPEffectsPanelStyle inStyle);

private:
    KAPEffectsPanelStyle mStyle;
};