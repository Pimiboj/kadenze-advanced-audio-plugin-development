/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 18 Jul 2023 8:51:31pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterComboBox.h"

class KAPCenterPanelMenuBar : public KAPPanelBase
{
public:
    KAPCenterPanelMenuBar(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPCenterPanelMenuBar();

    void AddEffectsTypeComboBoxListener(juce::ComboBox::Listener* inListener);
    void RemoveEffectsTypeComboBoxListener(juce::ComboBox::Listener* inListener);
 
private:
    std::unique_ptr<KAPParameterComboBox> mEffectsTypeComboBox;
};