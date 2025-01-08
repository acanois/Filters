//
// Created by David Richter on 12/31/24.
//

#include "PluginEditor.h"

FiltersEditor::FiltersEditor (FiltersProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused(processorRef);

    setSize(400, 300);
}

FiltersEditor::~FiltersEditor() = default;

void FiltersEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    auto area = getLocalBounds();
    g.drawText("Filters Plugin - HPF 1", area.removeFromTop(150), juce::Justification::centred, false);
}

void FiltersEditor::resized()
{
}