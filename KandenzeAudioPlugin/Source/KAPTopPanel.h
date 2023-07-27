/*
  ==============================================================================

    KAPTopPanel.h
    Created: 18 Jul 2023 8:52:06pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"

class KAPTopPanel : public KAPPanelBase, public juce::Button::Listener, public juce::ComboBox::Listener
{
public:
    KAPTopPanel(KandenzeAudioPluginAudioProcessor* inProcessor);
    ~KAPTopPanel();

    void paint(juce::Graphics& g) override;

    void buttonClicked(juce::Button* b) override;

    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    void displaySaveAsPopup();

    void updatePresetComboBox();

    std::unique_ptr<juce::ComboBox> mPresetDisplay;

    std::unique_ptr<juce::TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
};
