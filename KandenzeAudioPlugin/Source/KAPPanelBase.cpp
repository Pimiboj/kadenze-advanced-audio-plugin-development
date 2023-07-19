/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 18 Jul 2023 8:51:04pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPPanelBase.h"

KAPPanelBase::KAPPanelBase(KandenzeAudioPluginAudioProcessor* inProcessor)
    : mProcessor(inProcessor)
{

}

KAPPanelBase::~KAPPanelBase()
{

}

void KAPPanelBase::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::whitesmoke);
    g.fillAll();

    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight(), 2);
}