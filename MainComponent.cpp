#include "MainComponent.h"

#include <wtf/CPUTime.h>
#include <wtf/NumberOfCores.h>
#include <wtf/RAMSize.h>
#include <wtf/URL.h>

#include <JavaScriptCore/JavaScriptCore.h>

//==============================================================================
MainComponent::MainComponent()
{
    const auto a = WTF::CPUTime::get();
    DBG(WTF::numberOfProcessorCores());
    DBG(WTF::numberOfPhysicalProcessorCores());
    DBG(WTF::ramSize());

    auto g = JSContextGroupCreate();
    auto c = JSGlobalContextCreateInGroup(g, nullptr);

    auto script = JSStringCreateWithUTF8CString("3 + 3");
    auto result = JSEvaluateScript(c, script, nullptr, nullptr, 0, nullptr);

    auto resstring = JSValueToStringCopy(c, result, nullptr);
    char output[40];
    JSStringGetUTF8CString(resstring, output, 40);
    DBG(juce::String(output));

    setSize (600, 400);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    const auto b = std::string("https://www.youtube.com/watch?v=fLWlE28chls");
    const auto u = WTF::URL(WTF::String (b.data(), b.size()));

    g.drawText ((const char*) u.path().rawCharacters(), getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
