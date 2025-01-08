//
// Created by David Richter on 12/31/24.
//

#pragma once

#include "HighPassFilter.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

#include <memory>

#if (MSVC)
#include "ipps.h"
#endif

class FiltersProcessor : public juce::AudioProcessor
{
public:
    FiltersProcessor();
    ~FiltersProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    std::unique_ptr<HighPassFilter> mHighpass = std::make_unique<HighPassFilter>();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersProcessor)
};

