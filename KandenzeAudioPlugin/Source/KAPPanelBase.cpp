/*
  ==============================================================================

    KAPPanelBase.cpp
    Created: 18 Jul 2023 8:51:04pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPPanelBase.h"
#include "KAPInterfaceDefines.h"

KAPPanelBase::KAPPanelBase(KandenzeAudioPluginAudioProcessor* inProcessor)
    : mProcessor(inProcessor)
{

}

KAPPanelBase::~KAPPanelBase()
{

}

void KAPPanelBase::mouseEnter(const juce::MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::mouseExit(const juce::MouseEvent& event)
{
    repaint();
}

void KAPPanelBase::paint(juce::Graphics& g)
{
    if (isMouseOver())
    {
        //g.setColour(KAPColour_4);
        //g.fillAll();
    }
}