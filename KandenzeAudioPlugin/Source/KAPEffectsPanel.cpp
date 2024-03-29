/*
  ==============================================================================

    KAPEffectsPanel.cpp
    Created: 18 Jul 2023 8:51:41pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPEffectsPanel.h"

#include "KAPParameters.h"
#include "KAPHelperFunctions.h"

KAPEffectsPanel::KAPEffectsPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(EFFECTS_PANEL_WIDTH, EFFECTS_PANEL_HEIGHT);
    KAPEffectsPanelStyle currentStyle = (KAPEffectsPanelStyle)(int)mProcessor->getParameter(kDelayType);
    setEffectsPanelStyle(currentStyle);
}

KAPEffectsPanel::~KAPEffectsPanel()
{

}

void KAPEffectsPanel::paint(juce::Graphics& g)
{
    KAPPanelBase::paint(g);

    juce::String label;

    switch (mStyle)
    {
    case kDelay:
        label = "DELAY";
        break;

    case kChorus:
        label = "CHORUS";
        break;

    default:
        jassertfalse;
    }

    KAPLookAndFeel look;

    g.setColour(KAPColour_5);
    g.setFont(look.GetFont(3));

    g.drawText(label, 0, 0, getWidth(), 80, juce::Justification::centred);

    for (int i = 0; i < mSliders.size(); i++)
    {
        paintComponentLabel(g, &*mSliders.at(i));
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

    repaint();
}

void KAPEffectsPanel::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    KAPEffectsPanelStyle style = (KAPEffectsPanelStyle) comboBoxThatHasChanged->getSelectedItemIndex();

    setEffectsPanelStyle(style);
}