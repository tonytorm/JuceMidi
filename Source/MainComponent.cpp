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
    
    auto midiOutputDevices = MidiOutput::getAvailableDevices();
    for (auto i = 0; i < midiOutputDevices.size(); i++)
    {
        DBG("Output " << i << ": " << midiOutputDevices[i].name << "\n");
    }
    audioDeviceManager.setDefaultMidiOutputDevice (midiOutputDevices[1].identifier);
    
    audioDeviceManager.setMidiInputDeviceEnabled(midiInputDevices[2].identifier, true);
    audioDeviceManager.addMidiInputDeviceCallback("", this);
    
    
    addAndMakeVisible(midiLabel);
    midiLabel.setEditable(true);
    midiLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    midiLabel.setText ("YO", juce::dontSendNotification);
    midiLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    midiLabel.setJustificationType (juce::Justification::centred);
    midiLabel.setSize(getWidth()/4, getHeight()/4);
    
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
    audioDeviceManager.getDefaultMidiOutput()->sendMessageNow (message);
    String midiText;
    if (message.isNoteOnOrOff())
    {
        midiText << "NoteOnOrOff: Channel " << message.getChannel();
        midiText << " Note Number " << message.getNoteNumber();
        midiText << " Velocity " << message.getVelocity();
    }
    midiLabel.getTextValue() = midiText;
    
}


