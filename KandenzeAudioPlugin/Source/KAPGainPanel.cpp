/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 18 Jul 2023 8:51:51pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPGainPanel.h"

#include "KAPParameters.h"

KAPGainPanel::KAPGainPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::SetParameterID(int inParameterID)
{
    mSlider = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[inParameterID]);
    const int sliderSize = 54;
    mSlider->setBounds((getWidth() - sliderSize) * 0.5f, (getHeight() - sliderSize) * 0.5f, sliderSize, sliderSize);
    addAndMakeVisible(*mSlider);
}