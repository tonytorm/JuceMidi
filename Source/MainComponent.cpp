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
    
    addAndMakeVisible(midiLabel);
    midiLabel.setEditable(true);
    midiLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    midiLabel.setText ("YO", juce::dontSendNotification);
    midiLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    midiLabel.setJustificationType (juce::Justification::centred);
    midiLabel.setSize(getWidth(), getHeight());
    
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
    
}

void MainComponent::resized()
{
    
}

void MainComponent::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{
    DBG("Message received\n");
    String midiText;
    if (message.isNoteOnOrOff())
    {
        midiText << "NoteOnOrOff: Channel " << message.getChannel();
        midiText << " Note Number " << message.getNoteNumber();
        midiText << " Velocity " << message.getVelocity();
    }
    midiLabel.getTextValue() = midiText;
}


