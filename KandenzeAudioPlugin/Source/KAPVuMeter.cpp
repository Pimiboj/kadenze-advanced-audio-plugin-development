/*
  ==============================================================================

    KAPVuMeter.cpp
    Created: 30 Jul 2023 5:22:24pm
    Author:  pimvl

  ==============================================================================
*/

#include "KAPVuMeter.h"
#include "KAPInterfaceDefines.h"
#include "KAPParameters.h"

KAPVuMeter::KAPVuMeter(KandenzeAudioPluginAudioProcessor* inProcessor)
    :mParameterID(-1),
    mCh0Level(0),
    mCh1Level(0),
    mProcessor(inProcessor)
{

}

KAPVuMeter::~KAPVuMeter()
{

}

void KAPVuMeter::paint(juce::Graphics& g)
{
    const int meterWidth = getWidth() / 3;
    const int meterHeight = getHeight();

    g.setColour(KAPColour_6);
    g.fillRect(0, 0, meterWidth, meterHeight);
    g.fillRect(meterWidth * 2, 0, meterWidth, meterHeight);

    int ch0Fill = meterHeight - (meterHeight * mCh0Level);
    int ch1Fill = meterHeight - (meterHeight * mCh1Level);

    if (ch0Fill < 0)
        ch0Fill = 0;

    if (ch1Fill < 0)
        ch1Fill = 0;

    g.setColour(KAPColour_7);
    g.fillRect(0, ch0Fill, meterWidth, meterHeight);
    g.fillRect(meterWidth * 2, ch0Fill, meterWidth, meterHeight);
}

void KAPVuMeter::timerCallback()
{
    float updatedCh0Level = 0.0f;
    float updatedCh1Level = 0.0f;

    switch (mParameterID)
    {
        case(KAPParameter::kInputGain) :
        {
            updatedCh0Level = mProcessor->getInputGainMeterLevel(0);
            updatedCh1Level = mProcessor->getInputGainMeterLevel(1);
        } break;

        case(KAPParameter::kOutputGain) :
        {
            updatedCh0Level = mProcessor->getOutputGainMeterLevel(0);
            updatedCh1Level = mProcessor->getOutputGainMeterLevel(1);
        } break;
    }

    if (updatedCh0Level > mCh0Level)
    {
        mCh0Level = updatedCh0Level;
    }
    else
    {
        mCh0Level = kMeterSmoothingCoeff * (mCh0Level - updatedCh0Level) + updatedCh0Level;
    }

    if (updatedCh1Level > mCh1Level)
    {
        mCh1Level = updatedCh1Level;
    }
    else
    {
        mCh1Level = kMeterSmoothingCoeff * (mCh1Level - updatedCh1Level) + updatedCh1Level;
    }

    mCh0Level = kap_denormalize(mCh0Level);
    mCh1Level = kap_denormalize(mCh1Level);

    if (mCh0Level || mCh1Level)
    {
        repaint();
    }
}

void KAPVuMeter::SetParameterID(int inParameterID)
{
    mParameterID = inParameterID;

    startTimerHz(30);
}