/*
  ==============================================================================

    KAPGainPanel.h
    Created: 18 Jul 2023 8:51:51pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"

class KAPGainPanel : public KAPPanelBase
{
public:
    KAPGainPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPGainPanel();

    void paint(juce::Graphics& g) override;

    void SetParameterID(int inParameterID);

private:
    std::unique_ptr<KAPParameterSlider> mSlider;
};