/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 18 Jul 2023 8:51:31pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"

KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}