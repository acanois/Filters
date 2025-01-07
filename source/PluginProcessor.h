//
// Created by David Richter on 12/31/24.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <vector>

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
    std::vector<float> mFilterBuffer;

    bool mHighpass { true };
    float mCutoff { 1000.f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersProcessor)
};

