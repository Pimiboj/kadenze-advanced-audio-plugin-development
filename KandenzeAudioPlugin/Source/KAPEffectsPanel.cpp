/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 18 Jul 2023 8:51:41pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPEffectsPanel.h"

KAPEffectsPanel::KAPEffectsPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor),
      mStyle(KAPEffectsPanelStyle::kDelay)
{
    setSize(EFFECTS_PANEL_WIDTH, EFFECTS_PANEL_HEIGHT);
}

KAPEffectsPanel::~KAPEffectsPanel()
{

}

void KAPEffectsPanel::paint(juce::Graphics& g)
{
    KAPPanelBase::paint(g);

    switch (mStyle)
    {
    case kDelay:
        g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        break;

    case kChorus:
        g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        break;

    default:
    case kTotalNumStyles:
        /* SHOULD NOT HAPPEN */
        g.drawFittedText("NO NO NO", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
        jassertfalse;
        break;
    }
}

void KAPEffectsPanel::setEffectsPanelStyle(KAPEffectsPanelStyle inStyle)
{
    mStyle = inStyle;
}