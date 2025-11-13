#include "PluginEditor.h"
#include "PluginProcessor.h"

//===== Component Initializers =====

void A2StarterAudioProcessorEditor::initSlider(
    juce::Component &parent, juce::Label &mainLabel, juce::Label &unitLabel, juce::Slider &slider,
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
    juce::AudioProcessorValueTreeState &apvts, const juce::String &paramId, const juce::String &labelText,
    const juce::String &unitText, double minValue, double maxValue, double step,
    const A2StarterAudioProcessorEditor::ColorPalette &palette) {
    mainLabel.setText(labelText, juce::dontSendNotification);
    mainLabel.setJustificationType(juce::Justification::centredLeft);
    mainLabel.setColour(juce::Label::textColourId, palette.text);

    unitLabel.setText(unitText, juce::dontSendNotification);
    unitLabel.setJustificationType(juce::Justification::centredRight);
    unitLabel.setColour(juce::Label::textColourId, palette.text);

    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(minValue, maxValue, step);
    slider.setPopupDisplayEnabled(true, false, nullptr);
    slider.setValue(minValue);

    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
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

void A2StarterAudioProcessorEditor::initZenoToggle() {
    zenoToggle.setButtonText("Zeno Mode\n[ OFF ]");
    zenoToggle.setClickingTogglesState(true);
    zenoToggle.setColour(juce::TextButton::buttonColourId, palette.buttonOff);
    zenoToggle.setColour(juce::TextButton::buttonOnColourId, palette.buttonOn);
    zenoToggle.setColour(juce::TextButton::textColourOffId, palette.text);
    zenoToggle.onClick = [this]() {
        zenoToggle.setButtonText(zenoToggle.getToggleState() ? "Zeno Mode\n[ ON ]" : "Zeno Mode\n[ OFF ]");
    };

    addAndMakeVisible(&zenoToggle);

    zenoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts,
                                                                                            "ZENO", zenoToggle);
}

void A2StarterAudioProcessorEditor::initPingPongToggle() {
    pingPongToggle.setButtonText("Ping-Pong Mode\n[ OFF ]");
    pingPongToggle.setClickingTogglesState(true);
    pingPongToggle.setColour(juce::TextButton::buttonColourId, palette.buttonOff);
    pingPongToggle.setColour(juce::TextButton::buttonOnColourId, palette.buttonOn);
    pingPongToggle.setColour(juce::TextButton::textColourOffId, palette.text);
    pingPongToggle.onClick = [this]() {
        pingPongToggle.setButtonText(pingPongToggle.getToggleState() ? "Ping-Pong Mode\n[ ON ]"
                                                                     : "Ping-Pong Mode\n[ OFF ]");
    };

    addAndMakeVisible(&pingPongToggle);

    pingPongAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        audioProcessor.apvts, "PING_PONG", pingPongToggle);
}

void A2StarterAudioProcessorEditor::initClearButton() {
    clearButton.setButtonText("Clear Buffer");
    clearButton.setColour(juce::TextButton::buttonColourId, palette.buttonOff);
    clearButton.setColour(juce::TextButton::buttonOnColourId, palette.buttonOn);
    clearButton.setColour(juce::TextButton::textColourOffId, palette.text);

    addAndMakeVisible(&clearButton);
}

//===== Constructor & Destructor =====

A2StarterAudioProcessorEditor::A2StarterAudioProcessorEditor(A2StarterAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    setSize(670, 380);

    initSlider(*this, timeIntervalLabel, timeIntervalUnitLabel, timeIntervalSlider, timeIntervalAttachment,
               audioProcessor.apvts, "TIME_INTERVAL", "Time Interval", "[ s ]", 0.0, 3.0, 0.01, palette);
    initSlider(*this, feedbackLabel, feedbackUnitLabel, feedbackSlider, feedbackAttachment, audioProcessor.apvts,
               "FEEDBACK", "Feedback", "[ % ]", 0.0, 100.0, 1.0, palette);
    initSlider(*this, dryLabel, dryUnitLabel, drySlider, dryAttachment, audioProcessor.apvts, "DRY", "Dry Level",
               "[ % ]", 0.0, 100.0, 1.0, palette);
    initSlider(*this, wetLabel, wetUnitLabel, wetSlider, wetAttachment, audioProcessor.apvts, "WET", "Wet Level",
               "[ % ]", 0.0, 100.0, 1.0, palette);
    initSlider(*this, pingPongFreqLabel, pingPongFreqUnitLabel, pingPongFreqSlider, pingPongFreqAttachment,
               audioProcessor.apvts, "PING_PONG_FREQ", "Ping-Pong Frequency", "[ Hz ]", 0.0, 100.0, 1.0, palette);

    initZenoToggle();
    initPingPongToggle();
    initClearButton();
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

void A2StarterAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    audioProcessor.volumeBoost = volumeSlider.getValue();
}
