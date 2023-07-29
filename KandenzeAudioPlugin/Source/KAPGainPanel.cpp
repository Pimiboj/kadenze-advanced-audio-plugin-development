/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 18 Jul 2023 8:51:51pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPGainPanel.h"

#include "KAPParameters.h"
#include "KAPHelperFunctions.h"

KAPGainPanel::KAPGainPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}

KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::paint(juce::Graphics& g)
{
    KAPPanelBase::paint(g);

    if (mSlider)
    {
        paintComponentLabel(g, &*mSlider);
    }
}

void KAPGainPanel::SetParameterID(int inParameterID)
{
    mSlider = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[inParameterID]);
    const int sliderSize = 54;
    mSlider->setBounds((getWidth() - sliderSize) * 0.5f,
        getHeight() * 0.2f - sliderSize * 0.5f,
        sliderSize,
        sliderSize);

    addAndMakeVisible(*mSlider);
}