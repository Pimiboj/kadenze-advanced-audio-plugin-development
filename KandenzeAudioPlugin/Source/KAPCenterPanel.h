/*
  ==============================================================================

    KAPCenterPanel.h
    Created: 18 Jul 2023 8:51:21pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPCenterPanelMenuBar.h"
#include "KAPEffectsPanel.h"

class KAPCenterPanel : public KAPPanelBase
{
public:
    KAPCenterPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanel();

private:
    std::unique_ptr<KAPCenterPanelMenuBar> mCenterPanelMenuBar;
    std::unique_ptr<KAPEffectsPanel> mEffectsPanel;
};