/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 18 Jul 2023 8:51:41pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPEffectsPanel.h"

#include "KAPParameters.h"

KAPEffectsPanel::KAPEffectsPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(EFFECTS_PANEL_WIDTH, EFFECTS_PANEL_HEIGHT);
    setEffectsPanelStyle(kChorus);
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
        g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight(), juce::Justification::centred, 1);
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

    mSliders.clear();

    const int sliderSize = 56;
    int x = ((EFFECTS_PANEL_WIDTH - sliderSize) / 2) - (2 * sliderSize);
    int y = (getHeight() - sliderSize) * 0.5f;

    switch (mStyle)
    {
    case kDelay:
    {
        std::unique_ptr<KAPParameterSlider> time = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[kDelayTime]);
        time->setBounds(x, y, sliderSize, sliderSize);
        addAndMakeVisible(*time);
        mSliders.push_back(std::move(time));

        x += sliderSize * 2;
        std::unique_ptr<KAPParameterSlider> feedback = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[kDelayFeedback]);
        feedback->setBounds(x, y, sliderSize, sliderSize);
        addAndMakeVisible(*feedback);
        mSliders.push_back(std::move(feedback));

        x += sliderSize * 2;
        std::unique_ptr<KAPParameterSlider> wetDry = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[kDelayWetDry]);
        wetDry->setBounds(x, y, sliderSize, sliderSize);
        addAndMakeVisible(*wetDry);
        mSliders.push_back(std::move(wetDry));
    }   break;

    case kChorus:
    {
        std::unique_ptr<KAPParameterSlider> rate = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[kModulationRate]);
        rate->setBounds(x, y, sliderSize, sliderSize);
        addAndMakeVisible(*rate);
        mSliders.push_back(std::move(rate));

        x += sliderSize * 2;
        std::unique_ptr<KAPParameterSlider> depth = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[kModulationDepth]);
        depth->setBounds(x, y, sliderSize, sliderSize);
        addAndMakeVisible(*depth);
        mSliders.push_back(std::move(depth));

        x += sliderSize * 2;
        std::unique_ptr<KAPParameterSlider> wetDry = std::make_unique<KAPParameterSlider>(mProcessor->Parameters, KAPParameterID[kDelayWetDry]);
        wetDry->setBounds(x, y, sliderSize, sliderSize);
        addAndMakeVisible(*wetDry);
        mSliders.push_back(std::move(wetDry));
    }   break;

    default:
    case kTotalNumStyles:
    {
        /* SHOULD NOT HAPPEN */
        jassertfalse;
    }   break;
    }
}