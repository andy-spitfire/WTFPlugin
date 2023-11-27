#include "MainComponent.h"

#include <wtf/CPUTime.h>
#include <wtf/NumberOfCores.h>
#include <wtf/RAMSize.h>
#include <wtf/URL.h>

#include <JavaScriptCore/JSExportMacros.h>
#include <JavaScriptCore/JavaScriptCore.h>

#include "cmakeconfig.h"
#include <PlatformExportMacros.h>
#include <css/parser/CSSParserContext.h>
#include <css/parser/CSSParser.h>
#include <CommonAtomStrings.h>
#include <ProcessWarming.h>
#include <HTMLNames.h>
#include <Settings.h>

//==============================================================================
MainComponent::MainComponent()
{
    const auto a = WTF::CPUTime::get();
    DBG(WTF::numberOfProcessorCores());
    DBG(WTF::numberOfPhysicalProcessorCores());
    DBG(WTF::ramSize());

    auto g = JSContextGroupCreate();
    auto c = JSGlobalContextCreateInGroup(g, nullptr);

    auto script = JSStringCreateWithUTF8CString("32 + 3");
    auto result = JSEvaluateScript(c, script, nullptr, nullptr, 0, nullptr);

    auto resstring = JSValueToStringCopy(c, result, nullptr);
    char output[40];
    JSStringGetUTF8CString(resstring, output, 40);
    DBG(juce::String(output));

    // WebCore::Settings s (nullptr);
    // WebCore::Document d = WebCore::Document::create(s, {});
    WebCore::ProcessWarming::prewarmGlobally();

    WebCore::CSSParserContext ctx (WebCore::CSSParserMode::HTMLStandardMode, {});
    WebCore::CSSParser p (ctx);

    auto cnt = WebCore::StyleSheetContents::create();

    WTF::String str (WTF::ASCIILiteral::fromLiteralUnsafe(R"(/* Modified from:  https://www.w3schools.com/cssref/css_default_values.asp */

@font-face {
    font-family: "proxima-nova";
    src: url(ProximaNova-Regular.otf) format("opentype");
}
@font-face {
    font-family: "oxygen-mono";
    src: url(OxygenMono-Regular.ttf) format("truetype");
}
@font-face {
    font-family: "proxima-nova-ex-con-bold";
    src: url(ProximaNovaExCn-Bold.ttf) format("truetype");
}
@font-face {
    font-family: "proxima-nova-bold";
    src: url(ProximaNova-Bold.otf) format("opentype");
}
@font-face {
    font-family: "proxima-nova-semibold";
    src: url(ProximaNova-Semibold.otf) format("opentype");
}

/* Non-html components / classes */

.slider {
    width: 200px;
    height: 40px;
    thumb-radius: 6;
    stroke-width: 3;
    fill-color: #6495ED55;
    track-color: #6495ED;
    thumb-color: #6495ED;
    thumb-color-stroke: black;
    max: 1;
}

/* Flex formatting shorthand */

.row {
    display: flex;
    flex: 0 1 auto;
    flex-direction: row;
    flex-wrap: wrap;
}

.col {
    display: flex;
    flex-direction: column;
    flex: 0 1 auto;
}

.row.reverse {
    flex-direction: row-reverse;
}

.col.reverse {
    flex-direction: column-reverse;
}

/* General CSS defaults... */

* {
    box-sizing: border-box;
    display: block;
}

p, h1, h2, h3, h4, h5, h6, label, button {
    color:  white;
}

address {
    display: block;
    font-style: italic;
}

body {
    display: block;
    /* this happens in browsers but seems needless to force
    margin: 8px;
    */
}

cite {
    font-style: italic;
}

code {
    font-family: monospace;
}

col {
    display: table-column;
}

colgroup {
    display: table-column-group
}

div {
    display: block;
}

dl {
    display: block;
    margin-top: 1em;
    margin-bottom: 1em;
    margin-left: 0;
    margin-right: 0;
}

dt {
    display: block;
}

em {
    font-style: italic;
}

h1 {
    display: block;
    font-size: 2em;
    margin-top: 0.67em;
    margin-bottom: 0.67em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

h2 {
    display: block;
    font-size: 1.5em;
    margin-top: 0.83em;
    margin-bottom: 0.83em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

h3 {
    display: block;
    font-size: 1.17em;
    margin-top: 1em;
    margin-bottom: 1em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

h4 {
    display: block;
    margin-top: 1.33em;
    margin-bottom: 1.33em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

h5 {
    display: block;
    font-size: .83em;
    margin-top: 1.67em;
    margin-bottom: 1.67em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

h6 {
    display: block;
    font-size: .67em;
    margin-top: 2.33em;
    margin-bottom: 2.33em;
    margin-left: 0;
    margin-right: 0;
    font-weight: bold;
}

head {
    display: none;
}

header {
    display: block;
}

hr {
    margin-top: 0.5em;
    margin-bottom: 0.5em;
    margin-left: auto;
    margin-right: auto;
    border-style: inset;
    border-width: 1px;
}

html {
    display: block;
}

i, em {
    font-style: italic;
}

img {
    display: inline-block;
}

ins {
    text-decoration: underline;
}

kbd {
    font-family: monospace;
}

li {
    display: list-item;
}

mark {
    background-color: yellow;
    color: black;
}

output {
    display: inline;
}

p {
    display: block;
    margin-top: 1em;
    margin-bottom: 1em;
    margin-left: 0;
    margin-right: 0;
}

q {
    display: inline;
}

strike {
    text-decoration: line-through;
}

b, strong {
    font-weight: bold;
}

var {
    font-style: italic;
}

/* Input fields */

button {
    display: inline-block;
    border-style: solid;
}

text_editor {
    display: inline-block;
    width: 10em;
    caret-color: white;
}

checkbox {
    min-width: 1.5em;
    min-height: 1.5em;
}

select {
    font-size: 0.84em;
    padding-top: 4px;
    padding-bottom: 1px;
    color:  white;
}
)"));
    const auto res = cnt->parseString(str);
    jassert(res);
    DBG(juce::String (cnt->ruleCount()));
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
