/*
  ==============================================================================

    KAPDelay.cpp
    Created: 31 Dec 2022 4:21:28pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPDelay.h"

#include "JuceHeader.h"
#include "KAPAudioHelpers.h"

KAPDelay::KAPDelay()
    : mSampleRate(-1), mFeedbackSample(0.0f), mTimeSmoothed(0), mDelayIndex(0)
{
    
}

KAPDelay::~KAPDelay()
{

}

void KAPDelay::SetSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void KAPDelay::Reset()
{
    mTimeSmoothed = 0.0f;
    juce::zeromem(mBuffer, sizeof(mBuffer));
}

void KAPDelay::Process(float* inAudio,
    float inTime,
    float inFeedback,
    float inWetDry,
    float inType,
    float* inModulationBuffer,
    float* outAudio,
    int inNumSamplesToRender)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = juce::jmap(inFeedback, 0.0f, 1.0f, 0.0f, 0.95f);

    for (int i = 0; i < inNumSamplesToRender; i++)
    {

        if ((int)inType == KAPDelayType_Delay)
        {
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - inTime);
        }
        else
        {
            const double delayTimeModulation = (0.003 + (0.002 * inModulationBuffer[i]));
            mTimeSmoothed = mTimeSmoothed - kParameterSmoothingCoeff_Fine * (mTimeSmoothed - delayTimeModulation);
        }

        const double delayTimeInSamples = (mTimeSmoothed * mSampleRate);
        const double sample = getInterpolatedSample(delayTimeInSamples);

        mBuffer[mDelayIndex] = inAudio[i] + (mFeedbackSample * feedbackMapped);
        mFeedbackSample = sample;

        outAudio[i] = (inAudio[i] * dry + sample * wet);

        mDelayIndex += 1;

        if (mDelayIndex >= maxBufferDelaySize)
            mDelayIndex -= maxBufferDelaySize;
    }
}

double KAPDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;

    if (readPosition < 0.0f)
    {
        readPosition += maxBufferDelaySize;
    }

    int index_y0 = (int)readPosition - 1;
    int index_y1 = readPosition;

    if (index_y0 < 0)
        index_y0 += maxBufferDelaySize;

    if (index_y1 >= maxBufferDelaySize)
        index_y1 -= maxBufferDelaySize;

    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float t = readPosition - (int)readPosition;

    double outSample = kap_linear_interp(sample_y0, sample_y1, t);

    return outSample;
}