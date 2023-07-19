/*
  ==============================================================================

    KAPTopPanel.cpp
    Created: 18 Jul 2023 8:52:06pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPTopPanel.h"

KAPTopPanel::KAPTopPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
}

KAPTopPanel::~KAPTopPanel()
{

}

void KAPTopPanel::paint(juce::Graphics& g)
{
    KAPPanelBase::paint(g);

    g.drawFittedText("KADENZE AUDIO PLUGIN", 0, 0, getWidth() - 10, getHeight(), juce::Justification::centredRight, 1);
}