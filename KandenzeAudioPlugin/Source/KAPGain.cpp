/*
  ==============================================================================

    KAPGain.cpp
    Created: 31 Dec 2022 4:21:18pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPGain.h"

#include "KAPAudioHelpers.h"

KAPGain::KAPGain()
    : mOutputSmoothed(0)
{

}

KAPGain::~KAPGain()
{

}

void KAPGain::process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender)
{
    float gainMapped = juce::jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
    gainMapped = juce::Decibels::decibelsToGain(gainMapped, -24.0f);

    for (int i = 0; i < inNumSamplesToRender; i++)
    {
        outAudio[i] = inAudio[i] * gainMapped;
    }

    float absValue = fabs(outAudio[0]);
    mOutputSmoothed = kMeterSmoothingCoeff * (mOutputSmoothed - absValue) + absValue;
}

float KAPGain::GetMeterLevel()
{
    return mOutputSmoothed;
}