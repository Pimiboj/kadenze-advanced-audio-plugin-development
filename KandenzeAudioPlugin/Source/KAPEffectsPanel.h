/*
  ==============================================================================

    KAPEffectsPanel.h
    Created: 18 Jul 2023 8:51:41pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

#include "KAPParameterSlider.h"

enum KAPEffectsPanelStyle
{
    kDelay,
    kChorus,
    kTotalNumStyles
};

class KAPEffectsPanel : public KAPPanelBase, public juce::ComboBox::Listener
{
public:
    KAPEffectsPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPEffectsPanel();

    void paint(juce::Graphics& g) override;

    void setEffectsPanelStyle(KAPEffectsPanelStyle inStyle);

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    KAPEffectsPanelStyle mStyle;

    std::vector<std::unique_ptr<KAPParameterSlider>> mSliders;
};