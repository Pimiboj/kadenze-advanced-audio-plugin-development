/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "KAPMainPanel.h"
#include "KAPLookAndFeel.h"

//==============================================================================
/**
*/
class KandenzeAudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KandenzeAudioPluginAudioProcessorEditor (KandenzeAudioPluginAudioProcessor&);
    ~KandenzeAudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KandenzeAudioPluginAudioProcessor& audioProcessor;

    std::unique_ptr<KAPLookAndFeel> mLookAndFeel;
    std::unique_ptr<KAPMainPanel> mMainPanel;
    juce::Image mBackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KandenzeAudioPluginAudioProcessorEditor)
};
