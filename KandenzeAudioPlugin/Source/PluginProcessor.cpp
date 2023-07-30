/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "KAPParameters.h"

//==============================================================================
KandenzeAudioPluginAudioProcessor::KandenzeAudioPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    , Parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    initializeDSP();

    mPresetManager = std::make_unique<KAPPresetManager>(this);
}

KandenzeAudioPluginAudioProcessor::~KandenzeAudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String KandenzeAudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KandenzeAudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KandenzeAudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KandenzeAudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KandenzeAudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KandenzeAudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KandenzeAudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KandenzeAudioPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KandenzeAudioPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void KandenzeAudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KandenzeAudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < 2; i++)
    {
        mDelay[i]->SetSampleRate(sampleRate);
        mLFO[i]->SetSampleRate(sampleRate);
    }
}

void KandenzeAudioPluginAudioProcessor::releaseResources()
{
    for (int i = 0; i < 2; i++)
    {
        mDelay[i]->Reset();
        mLFO[i]->Reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KandenzeAudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KandenzeAudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        mInputGain[channel]->process(channelData,
            getParameter(KAPParameter::kInputGain),
            channelData,
            buffer.getNumSamples());

        float rate = (channel == 0) ? 0 : getParameter(KAPParameter::kModulationRate);

        mLFO[channel]->Process(rate,
            getParameter(KAPParameter::kModulationDepth),
            buffer.getNumSamples());

        mDelay[channel]->Process(channelData,
            getParameter(KAPParameter::kDelayTime),
            getParameter(KAPParameter::kDelayFeedback),
            getParameter(KAPParameter::kDelayWetDry),
            getParameter(KAPParameter::kDelayType),
            mLFO[channel]->GetBuffer(),
            channelData,
            buffer.getNumSamples());

        mOutputGain[channel]->process(channelData,
            getParameter(KAPParameter::kOutputGain),
            channelData,
            buffer.getNumSamples());
    }
}

//==============================================================================
bool KandenzeAudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KandenzeAudioPluginAudioProcessor::createEditor()
{
    return new KandenzeAudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void KandenzeAudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::XmlElement preset("KAP_StateInfo");
    juce::XmlElement* presetBody = new juce::XmlElement("KAP_Preset");
    mPresetManager->GetXMLForPreset(presetBody);
    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
}

void KandenzeAudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState = getXmlFromBinary(data, sizeInBytes);

    if (xmlState)
    {
        forEachXmlChildElement(*xmlState, subChild)
        {
            mPresetManager->LoadPresetForXML(subChild);
        }
    }
    else
    {
        jassertfalse;
    }
}

float KandenzeAudioPluginAudioProcessor::getInputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->GetMeterLevel());

    return normalizeddB;
}

float KandenzeAudioPluginAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
    const float normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->GetMeterLevel());

    return normalizeddB;
}

void KandenzeAudioPluginAudioProcessor::initializeParameters()
{
    for (int i = 0; i < kTotalNumParameters; i++)
    {
        Parameters.createAndAddParameter(KAPParameterID[i],
            KAPParameterID[i],
            KAPParameterID[i],
            juce::NormalisableRange<float>(0.0f, 1.0f),
            0.5f,
            nullptr,
            nullptr);
    }
}

void KandenzeAudioPluginAudioProcessor::initializeDSP()
{
    for (int i = 0; i < 2; i++)
    {
        mInputGain[i] = std::make_unique<KAPGain>();
        mOutputGain[i] = std::make_unique<KAPGain>();
        mDelay[i] = std::make_unique<KAPDelay>();
        mLFO[i] = std::make_unique<KAPLfo>();
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout KandenzeAudioPluginAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    for (int i = 0; i < KAPParameter::kTotalNumParameters; i++)
    {
        layout.add(std::make_unique<juce::AudioParameterFloat>(KAPParameterID[i],
            KAPParameterID[i],
            juce::NormalisableRange<float>(0.0f, 1.0f),
            0.5f,
            KAPParameterID[i],
            juce::AudioProcessorParameter::Category::genericParameter,
            nullptr,
            nullptr));
    }

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KandenzeAudioPluginAudioProcessor();
}
