/*
  ==============================================================================

    KAPInterfaceDefines.h
    Created: 18 Jul 2023 8:58:56pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#ifdef JUCE_MAC
const static juce::String fontName = "Helvetica Neue";
#else
const static juce::String fontName = "Arial";
#endif

#include "JuceHeader.h"

#define MAIN_PANEL_WIDTH                750
#define MAIN_PANEL_HEIGHT               300

#define TOP_PANEL_WIDTH                 MAIN_PANEL_WIDTH
#define TOP_PANEL_HEIGHT                45

#define GAIN_PANEL_WIDTH                100
#define GAIN_PANEL_HEIGHT               (MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT)

#define CENTER_PANEL_WIDTH              (MAIN_PANEL_WIDTH - (GAIN_PANEL_WIDTH * 2))
#define CENTER_PANEL_HEIGHT             GAIN_PANEL_HEIGHT

#define CENTER_PANEL_MENU_BAR_WIDTH     CENTER_PANEL_WIDTH
#define CENTER_PANEL_MENU_BAR_HEIGHT    35

#define EFFECTS_PANEL_WIDTH             CENTER_PANEL_WIDTH
#define EFFECTS_PANEL_HEIGHT            (CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT)

const juce::Colour KAPColour_1 = juce::Colour(105, 105, 105);
const juce::Colour KAPColour_2 = juce::Colour(0, 0, 0).withAlpha(0.0f);
const juce::Colour KAPColour_3 = juce::Colour(0, 0, 0).withAlpha(0.3f);
const juce::Colour KAPColour_4 = juce::Colour(0, 0, 0).withAlpha(0.6f);
const juce::Colour KAPColour_5 = juce::Colour(105, 105, 105).withAlpha(0.3f);
const juce::Colour KAPColour_6 = juce::Colour(0, 0, 0).withAlpha(0.8f);
const juce::Colour KAPColour_7 = juce::Colour(125, 125, 125);

//const static juce::Font font_1(fontName, 12.00f, juce::Font::bold);
//const static juce::Font font_2(fontName, 22.00f, juce::Font::bold);
//const static juce::Font font_3(fontName, 48.00f, juce::Font::bold);

const static float font1Size = 12.0f;
const static float font2Size = 22.0f;
const static float font3Size = 48.0f;