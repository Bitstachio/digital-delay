#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "DelayParams.h"

//===== Component Initializers =====

void A2StarterAudioProcessorEditor::initSlider(
    juce::Component &parent, juce::Label &mainLabel, juce::Label &unitLabel, juce::Slider &slider,
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
    juce::AudioProcessorValueTreeState &apvts, const juce::String &paramId, const juce::String &labelText,
    const juce::String &unitText, double minValue, double maxValue, double step,
    const A2StarterAudioProcessorEditor::ColourPalette &palette) {
    mainLabel.setText(labelText, juce::dontSendNotification);
    mainLabel.setJustificationType(juce::Justification::centredLeft);
    mainLabel.setColour(juce::Label::textColourId, palette.text);

    unitLabel.setText(unitText, juce::dontSendNotification);
    unitLabel.setJustificationType(juce::Justification::centredRight);
    unitLabel.setColour(juce::Label::textColourId, palette.text);

    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(minValue, maxValue, step);
    slider.setPopupDisplayEnabled(false, false, nullptr);
    slider.setValue(minValue);

    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    slider.setColour(juce::Slider::backgroundColourId, palette.sliderBackground);
    slider.setColour(juce::Slider::trackColourId, palette.sliderTrack);
    slider.setColour(juce::Slider::thumbColourId, palette.sliderThumb);
    slider.setColour(juce::Slider::textBoxTextColourId, palette.text);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, palette.background);
    slider.setColour(juce::Slider::textBoxOutlineColourId, palette.accent);

    parent.addAndMakeVisible(mainLabel);
    parent.addAndMakeVisible(unitLabel);
    parent.addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
}

void A2StarterAudioProcessorEditor::initToggleButton(
    juce::TextButton &button, std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> &attachment,
    const juce::String &paramId, const juce::String &labelText, const juce::Colour &offColour,
    const juce::Colour &onColour, const juce::Colour &textColour) {
    button.setButtonText(labelText + "\n[ OFF ]");
    button.setClickingTogglesState(true);
    button.setColour(juce::TextButton::buttonColourId, offColour);
    button.setColour(juce::TextButton::buttonOnColourId, onColour);
    button.setColour(juce::TextButton::textColourOffId, textColour);

    button.onClick = [this, &button, labelText]() {
        button.setButtonText(button.getToggleState() ? labelText + "\n[ ON ]" : labelText + "\n[ OFF ]");
    };

    addAndMakeVisible(&button);

    attachment =
        std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, paramId, button);
}

void A2StarterAudioProcessorEditor::initButton(juce::TextButton &button, const juce::String &labelText,
                                               const juce::Colour &offColour, const juce::Colour &onColour,
                                               const juce::Colour &textColour, std::function<void()> onClickHandler) {
    button.setButtonText(labelText);
    button.setColour(juce::TextButton::buttonColourId, offColour);
    button.setColour(juce::TextButton::buttonOnColourId, onColour);
    button.setColour(juce::TextButton::textColourOffId, textColour);

    if (onClickHandler)
        button.onClick = std::move(onClickHandler);

    addAndMakeVisible(&button);
}

//===== Constructor & Destructor =====

A2StarterAudioProcessorEditor::A2StarterAudioProcessorEditor(A2StarterAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    setSize(670, 380);

    initSlider(*this, timeIntervalLabel, timeIntervalUnitLabel, timeIntervalSlider, timeIntervalAttachment,
               audioProcessor.apvts, "TIME_INTERVAL", "Time Interval", "[ s ]", DelayParams::INTERVAL_MIN,
               DelayParams::INTERVAL_MAX, DelayParams::INTERVAL_STEP, palette);
    initSlider(*this, feedbackLabel, feedbackUnitLabel, feedbackSlider, feedbackAttachment, audioProcessor.apvts,
               "FEEDBACK", "Feedback", "[ % ]", DelayParams::FEEDBACK_MIN, DelayParams::FEEDBACK_MAX,
               DelayParams::FEEDBACK_STEP, palette);
    initSlider(*this, dryLabel, dryUnitLabel, drySlider, dryAttachment, audioProcessor.apvts, "DRY", "Dry Level",
               "[ % ]", DelayParams::DRY_MIN, DelayParams::DRY_MAX, DelayParams::DRY_STEP, palette);
    initSlider(*this, wetLabel, wetUnitLabel, wetSlider, wetAttachment, audioProcessor.apvts, "WET", "Wet Level",
               "[ % ]", DelayParams::WET_MIN, DelayParams::WET_MAX, DelayParams::WET_STEP, palette);
    initSlider(*this, pingPongFreqLabel, pingPongFreqUnitLabel, pingPongFreqSlider, pingPongFreqAttachment,
               audioProcessor.apvts, "PING_PONG_FREQ", "Ping-Pong Frequency", "[ Hz ]", DelayParams::PING_PONG_FREQ_MIN,
               DelayParams::PING_PONG_FREQ_MAX, DelayParams::PING_PONG_FREQ_STEP, palette);

    initToggleButton(zenoToggle, zenoAttachment, "ZENO", "Zeno Mode", palette.buttonOff, palette.buttonOn,
                     palette.text);
    initToggleButton(pingPongToggle, pingPongAttachment, "PING_PONG", "Ping-Pong Mode", palette.buttonOff,
                     palette.buttonOn, palette.text);

    initButton(clearButton, "Clear Buffer", palette.buttonOff, palette.buttonOn, palette.text,
               [this]() { audioProcessor.clearDelayBuffer(); });
}

A2StarterAudioProcessorEditor::~A2StarterAudioProcessorEditor() {}

void A2StarterAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(palette.background);
    g.setColour(palette.text);
    g.setFont(24.0f);
    g.drawFittedText("Digital Delay Plugin", 0, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void A2StarterAudioProcessorEditor::resized() {
    timeIntervalLabel.setBounds(30, 60, 250, 30);
    timeIntervalSlider.setBounds(30, 90, 250, 20);
    timeIntervalUnitLabel.setBounds(280, 90, 40, 20);

    feedbackLabel.setBounds(30, 140, 250, 30);
    feedbackSlider.setBounds(30, 170, 250, 20);
    feedbackUnitLabel.setBounds(280, 170, 40, 20);

    dryLabel.setBounds(350, 60, 250, 30);
    drySlider.setBounds(350, 90, 250, 20);
    dryUnitLabel.setBounds(600, 90, 40, 20);

    wetLabel.setBounds(350, 140, 250, 30);
    wetSlider.setBounds(350, 170, 250, 20);
    wetUnitLabel.setBounds(600, 170, 40, 20);

    pingPongFreqLabel.setBounds(350, 220, 250, 30);
    pingPongFreqSlider.setBounds(350, 250, 250, 20);
    pingPongFreqUnitLabel.setBounds(600, 250, 40, 20);

    zenoToggle.setBounds(30, 220, 140, 60);

    pingPongToggle.setBounds(180, 220, 140, 60);

    clearButton.setBounds(30, 320, 610, 30);
}
