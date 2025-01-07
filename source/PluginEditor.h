//
// Created by David Richter on 12/31/24.
//

#pragma once

#include "PluginProcessor.h"



class FiltersEditor : public juce::AudioProcessorEditor
{
public:
    explicit FiltersEditor (FiltersProcessor&);
    ~FiltersEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FiltersProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersEditor)
};
