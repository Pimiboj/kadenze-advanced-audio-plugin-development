/*
  ==============================================================================

    KAPPresetManager.cpp
    Created: 24 Jul 2023 8:34:59pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPPresetManager.h"

#if JUCE_WINDOWS
static juce::String directorySeparator = "\\";
#elif JUCE_MAC
static juce::String directorySeparator = "/";
#endif

KAPPresetManager::KAPPresetManager(juce::AudioProcessor* inProcessor)
    : mCurrentPresetIsSaved(false),
      mCurrentPresetName("Untitled"),
      mProcessor(inProcessor)
{
    const juce::String pluginName = (juce::String)mProcessor->getName();

    mPresetDirectory = (juce::File::getSpecialLocation(juce::File::userDesktopDirectory)).getFullPathName() + directorySeparator + pluginName;

    if (!juce::File(mPresetDirectory).exists())
    {
        juce::File(mPresetDirectory).createDirectory();
    }

    storeLocalPresets();
}

KAPPresetManager::~KAPPresetManager()
{

}

void KAPPresetManager::GetXMLForPreset(juce::XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++)
    {
        inElement->setAttribute(mProcessor->getParameterName(i), mProcessor->getParameter(i));
    }
}

void KAPPresetManager::LoadPresetForXML(juce::XmlElement* inElement)
{
    mCurrentPresetXml = inElement;

    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++)
    {
        const juce::String name = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);

        for (int j = 0; j < mProcessor->getNumParameters(); j++)
        {
            if (mProcessor->getParameterName(j) == name)
            {
                mProcessor->setParameterNotifyingHost(j, value);
            }
        }
    }
}

int KAPPresetManager::GetNumberOfPresets()
{
    return mLocalPresets.size();
}

juce::String KAPPresetManager::GetPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void KAPPresetManager::CreateNewPreset()
{
    const int numParameters = mProcessor->getNumParameters();

    for (int i = 0; i < numParameters; i++)
    {
        mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
    }

    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void KAPPresetManager::SavePreset()
{
    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    mCurrentlyLoadedPreset.deleteFile();

    mCurrentlyLoadedPreset.appendData(destinationData.getData(), destinationData.getSize());

    mCurrentPresetIsSaved = true;

}

void KAPPresetManager::SaveAsPreset(juce::String inPresetName)
{
    juce::File presetFile = juce::File(mPresetDirectory + directorySeparator + inPresetName + PRESET_FILE_EXTENSION);

    if (!presetFile.exists())
    {
        presetFile.create();
    }
    else
    {
        presetFile.deleteFile();
    }

    juce::MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);

    presetFile.appendData(destinationData.getData(), destinationData.getSize());

    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;

    storeLocalPresets();
}

void KAPPresetManager::LoadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];

    juce::MemoryBlock presetBinary;

    if (mCurrentlyLoadedPreset.loadFileAsData(presetBinary))
    {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = GetPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(),
                                        (int)presetBinary.getSize());
    }
}

bool KAPPresetManager::GetIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

juce::String KAPPresetManager::GetCurrentPresetName()
{
    return mCurrentPresetName;
}

void KAPPresetManager::storeLocalPresets()
{
    mLocalPresets.clear();

    for (juce::DirectoryIterator di(juce::File(mPresetDirectory), false, "*" + (juce::String)PRESET_FILE_EXTENSION, juce::File::TypesOfFileToFind::findFiles); di.next();)
    {
        juce::File preset = di.getFile();
        mLocalPresets.add(preset);
    }
}