//
// Created by David Richter on 12/31/24.
//

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FiltersProcessor::FiltersProcessor()
    : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                          .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
)
{
}

FiltersProcessor::~FiltersProcessor() = default;

//==============================================================================
const juce::String FiltersProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FiltersProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FiltersProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool FiltersProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double FiltersProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FiltersProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int FiltersProcessor::getCurrentProgram()
{
    return 0;
}

void FiltersProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String FiltersProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void FiltersProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void FiltersProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void FiltersProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool FiltersProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void FiltersProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                     juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;

    // Resets the size of the buffer and sets all values to 0.f
    mFilterBuffer.resize(static_cast<unsigned long>(buffer.getNumChannels()), 0.f);

    const auto pi = juce::MathConstants<float>::pi;
    const auto sign = mHighpass ? -1.f : 1.f;

    // Calculating allpass coefficient
    const auto tan = std::tan(pi * mCutoff / getSampleRate());
    const auto a1 = (tan - 1.f) / (tan + 1.f);

    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto channelWritePtr = buffer.getWritePointer(channel);

        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample) {
            const auto inputSample = channelWritePtr[sample];

            // allpass filter
            const auto apfSample = a1 * inputSample + mFilterBuffer[channel];
            mFilterBuffer[channel] = inputSample - a1 * apfSample;

            // hpf or lpf applied - scaled by 0.5 to stay in [-1, 1]
            const auto outputSample = 0.5f * (inputSample + sign * apfSample);

            // assign to output
            channelWritePtr[sample] = outputSample;
        }
    }
}

//==============================================================================
bool FiltersProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FiltersProcessor::createEditor()
{
    return new FiltersEditor (*this);
}

//==============================================================================
void FiltersProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void FiltersProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FiltersProcessor();
}
