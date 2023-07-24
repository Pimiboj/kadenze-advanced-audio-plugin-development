/*
  ==============================================================================

    KAPCenterPanel.cpp
    Created: 18 Jul 2023 8:51:21pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPCenterPanel.h"

KAPCenterPanel::KAPCenterPanel(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);

    mCenterPanelMenuBar = std::make_unique<KAPCenterPanelMenuBar>(inProcessor);
    mCenterPanelMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(*mCenterPanelMenuBar);

    mEffectsPanel = std::make_unique<KAPEffectsPanel>(inProcessor);
    mEffectsPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(*mEffectsPanel);

    mCenterPanelMenuBar->AddEffectsTypeComboBoxListener(&*mEffectsPanel);
}

KAPCenterPanel::~KAPCenterPanel()
{
    mCenterPanelMenuBar->RemoveEffectsTypeComboBoxListener(&*mEffectsPanel);
}