#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    auto midiInputDevices = MidiInput::getAvailableDevices();
    for (auto i = 0; i < midiInputDevices.size(); i++)
    {
        DBG("Input " << i << ": " << midiInputDevices[i].name << "\n");
    }
    
    audioDeviceManager.setMidiInputDeviceEnabled(midiInputDevices[1].identifier, true);
    audioDeviceManager.addMidiInputDeviceCallback("", this);
}

MainComponent::~MainComponent()
{
    audioDeviceManager.removeMidiInputDeviceCallback("", this);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{
    DBG("Message received\n");
}
