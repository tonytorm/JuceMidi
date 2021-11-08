#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public   Component,
                                MidiInputCallback
                                
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void handleIncomingMidiMessage (MidiInput*, const MidiMessage&) override;

private:
    //==============================================================================
    // Your private member variables go here...
    AudioDeviceManager audioDeviceManager;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
