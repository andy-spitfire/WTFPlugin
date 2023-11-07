#include "MainComponent.h"

#include <wtf/CPUTime.h>
#include <wtf/NumberOfCores.h>
#include <wtf/RAMSize.h>
#include <wtf/URL.h>

//==============================================================================
MainComponent::MainComponent()
{
    const auto a = WTF::CPUTime::get();
    DBG(WTF::numberOfProcessorCores());
    DBG(WTF::numberOfPhysicalProcessorCores());
    DBG(WTF::ramSize());

    const auto b = std::string("https://www.youtube.com/watch?v=fLWlE28chls");
    const auto u = WTF::URL(WTF::String (b.data(), b.size()));

    DBG((u.protocolIsInFTPFamily()? "1" : "0"));
    DBG((u.protocolIsInHTTPFamily()? "1" : "0"));
    DBG((const char*) u.path().rawCharacters());

    setSize (600, 400);
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
