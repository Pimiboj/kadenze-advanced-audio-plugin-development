/*
  ==============================================================================

    KAPPresetManager.h
    Created: 24 Jul 2023 8:34:59pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENSION ".kpf"

class KAPPresetManager
{
public:
    KAPPresetManager(juce::AudioProcessor* inProcessor);
    ~KAPPresetManager();

    void GetXMLForPreset(juce::XmlElement* inElement);

    void LoadPresetForXML(juce::XmlElement* inElement);

    int GetNumberOfPresets();

    juce::String GetPresetName(int inPresetIndex);

    void CreateNewPreset();

    void SavePreset();

    void SaveAsPreset(juce::String inPresetName);

    void LoadPreset(int inPresetIndex);

    bool GetIsCurrentPresetSaved();

    juce::String GetCurrentPresetName();

private:
    void storeLocalPresets();

    bool mCurrentPresetIsSaved;
    juce::File mCurrentlyLoadedPreset;
    juce::Array<juce::File> mLocalPresets;
    juce::String mCurrentPresetName;
    juce::String mPresetDirectory;
    juce::AudioProcessor* mProcessor;
    juce::XmlElement* mCurrentPresetXml;
};