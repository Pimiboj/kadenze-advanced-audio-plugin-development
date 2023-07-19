/*
  ==============================================================================

    KAPMainPanel.h
    Created: 18 Jul 2023 8:51:11pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPTopPanel.h"
#include "KAPGainPanel.h"
#include "KAPCenterPanel.h"

class KAPMainPanel : public KAPPanelBase
{
public:
    KAPMainPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPMainPanel();

private:
    std::unique_ptr<KAPTopPanel> mTopPanel;
    std::unique_ptr<KAPGainPanel> mInputGainPanel;
    std::unique_ptr<KAPGainPanel> mOutputGainPanel;
    std::unique_ptr<KAPCenterPanel> mCenterPanel;
};