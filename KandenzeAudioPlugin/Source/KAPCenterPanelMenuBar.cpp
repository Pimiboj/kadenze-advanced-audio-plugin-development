/*
  ==============================================================================

    KAPCenterPanelMenuBar.cpp
    Created: 18 Jul 2023 8:51:31pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPCenterPanelMenuBar.h"
#include "KAPParameters.h"

KAPCenterPanelMenuBar::KAPCenterPanelMenuBar(KandenzeAudioPluginAudioProcessor* inProcessor)
    : KAPPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);

    const int width = 85;

    mEffectsTypeComboBox = std::make_unique<KAPParameterComboBox>(mProcessor->Parameters, KAPParameterID[kDelayType]);

    mEffectsTypeComboBox->setBounds(getWidth() - width, 0, width, getHeight());
    mEffectsTypeComboBox->addItem("DELAY", 1);
    mEffectsTypeComboBox->addItem("CHORUS", 2);
    mEffectsTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(kDelayType), juce::dontSendNotification);
    addAndMakeVisible(*mEffectsTypeComboBox);
}

KAPCenterPanelMenuBar::~KAPCenterPanelMenuBar()
{

}

void KAPCenterPanelMenuBar::AddEffectsTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mEffectsTypeComboBox->addListener(inListener);
}

void KAPCenterPanelMenuBar::RemoveEffectsTypeComboBoxListener(juce::ComboBox::Listener* inListener)
{
    mEffectsTypeComboBox->removeListener(inListener);
}