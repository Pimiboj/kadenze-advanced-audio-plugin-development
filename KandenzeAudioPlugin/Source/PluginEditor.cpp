/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KandenzeAudioPluginAudioProcessorEditor::KandenzeAudioPluginAudioProcessorEditor (KandenzeAudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);

    mMainPanel = std::make_unique<KAPMainPanel>(&audioProcessor);
    addAndMakeVisible(*mMainPanel);

    mLookAndFeel = std::make_unique<KAPLookAndFeel>();
    setLookAndFeel(mLookAndFeel.get());

    juce::LookAndFeel::setDefaultLookAndFeel(mLookAndFeel.get());
}

KandenzeAudioPluginAudioProcessorEditor::~KandenzeAudioPluginAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
    setLookAndFeel(nullptr);
}

//==============================================================================
void KandenzeAudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void KandenzeAudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
