#include "PluginEditor.h"
#include "PluginProcessor.h"

//===== Component Initializers =====

void A2StarterAudioProcessorEditor::initTimeIntervalSlider() {
    timeIntervalLabel.setText("Time Interval", juce::dontSendNotification);
    timeIntervalLabel.setJustificationType(juce::Justification::centredLeft);
    timeIntervalLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    timeIntervalUnitLabel.setText("[ s ]", juce::dontSendNotification);
    timeIntervalUnitLabel.setJustificationType(juce::Justification::centredLeft);
    timeIntervalUnitLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    timeIntervalSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    timeIntervalSlider.setRange(0, 3, 0.01);
    timeIntervalSlider.setPopupDisplayEnabled(true, false, this);
    timeIntervalSlider.setValue(0);

    timeIntervalSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    timeIntervalSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    timeIntervalSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    timeIntervalSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&timeIntervalLabel);
    addAndMakeVisible(&timeIntervalUnitLabel);
    addAndMakeVisible(&timeIntervalSlider);

    timeIntervalAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "TIME_INTERVAL", timeIntervalSlider);
}

void A2StarterAudioProcessorEditor::initFeedbackSlider() {
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centredLeft);
    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    feedbackUnitLabel.setText("[ % ]", juce::dontSendNotification);
    feedbackUnitLabel.setJustificationType(juce::Justification::centredLeft);
    feedbackUnitLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    feedbackSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    feedbackSlider.setRange(0, 100, 1);
    feedbackSlider.setPopupDisplayEnabled(true, false, this);
    feedbackSlider.setValue(0);

    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    feedbackSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    feedbackSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    feedbackSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&feedbackLabel);
    addAndMakeVisible(&feedbackUnitLabel);
    addAndMakeVisible(&feedbackSlider);

    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "FEEDBACK", feedbackSlider);
}

void A2StarterAudioProcessorEditor::initDrySlider() {
    dryLabel.setText("Dry Level", juce::dontSendNotification);
    dryLabel.setJustificationType(juce::Justification::centredLeft);
    dryLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    dryUnitLabel.setText("[ % ]", juce::dontSendNotification);
    dryUnitLabel.setJustificationType(juce::Justification::centredLeft);
    dryUnitLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    drySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    drySlider.setRange(0, 100, 1);
    drySlider.setPopupDisplayEnabled(true, false, this);
    drySlider.setValue(0);

    drySlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    drySlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    drySlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    drySlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&dryLabel);
    addAndMakeVisible(&dryUnitLabel);
    addAndMakeVisible(&drySlider);

    dryAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRY", drySlider);
}

void A2StarterAudioProcessorEditor::initWetSlider() {
    wetLabel.setText("Wet Level", juce::dontSendNotification);
    wetLabel.setJustificationType(juce::Justification::centredLeft);
    wetLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    wetUnitLabel.setText("[ % ]", juce::dontSendNotification);
    wetUnitLabel.setJustificationType(juce::Justification::centredLeft);
    wetUnitLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    wetSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    wetSlider.setRange(0, 100, 1);
    wetSlider.setPopupDisplayEnabled(true, false, this);
    wetSlider.setValue(0);

    wetSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    wetSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    wetSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    wetSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&wetLabel);
    addAndMakeVisible(&wetUnitLabel);
    addAndMakeVisible(&wetSlider);

    wetAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WET", wetSlider);
}

void A2StarterAudioProcessorEditor::initPingPongFreqSlider() {
    pingPongFreqLabel.setText("Ping-Pong Frequency", juce::dontSendNotification);
    pingPongFreqLabel.setJustificationType(juce::Justification::centredLeft);
    pingPongFreqLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    pingPongFreqUnitLabel.setText("[ Hz ]", juce::dontSendNotification);
    pingPongFreqUnitLabel.setJustificationType(juce::Justification::centredLeft);
    pingPongFreqUnitLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    pingPongFreqSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    pingPongFreqSlider.setRange(0, 100, 1);
    pingPongFreqSlider.setPopupDisplayEnabled(true, false, this);
    pingPongFreqSlider.setValue(0);

    pingPongFreqSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    pingPongFreqSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    pingPongFreqSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    pingPongFreqSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&pingPongFreqLabel);
    addAndMakeVisible(&pingPongFreqUnitLabel);
    addAndMakeVisible(&pingPongFreqSlider);

    pingPongFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "PING_PONG_FREQ", pingPongFreqSlider);
}

void A2StarterAudioProcessorEditor::initZenoToggle() {
    zenoToggle.setButtonText("Zeno Mode\n[ OFF ]");
    zenoToggle.setClickingTogglesState(true);
    zenoToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    zenoToggle.setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    zenoToggle.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::grey);
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
    pingPongToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    pingPongToggle.setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    pingPongToggle.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::grey);
    pingPongToggle.onClick = [this]() {
        pingPongToggle.setButtonText(pingPongToggle.getToggleState() ? "Ping-Pong Mode\n[ ON ]"
                                                                     : "Ping-Pong Mode\n[ OFF ]");
    };

    addAndMakeVisible(&pingPongToggle);

    pingPongAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        audioProcessor.apvts, "PING_PONG", pingPongToggle);
}

//===== Constructor & Destructor =====

A2StarterAudioProcessorEditor::A2StarterAudioProcessorEditor(A2StarterAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    setSize(1200, 400);

    initTimeIntervalSlider();
    initFeedbackSlider();
    initDrySlider();
    initWetSlider();
    initZenoToggle();
    initPingPongToggle();
    initPingPongFreqSlider();
}

A2StarterAudioProcessorEditor::~A2StarterAudioProcessorEditor() {}

void A2StarterAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::black);
    g.setFont(24.0f);
    g.drawFittedText("Digital Delay", 0, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void A2StarterAudioProcessorEditor::resized() {
    timeIntervalLabel.setBounds(30, 60, 220, 30);
    timeIntervalUnitLabel.setBounds(250, 90, 220, 20);
    timeIntervalLabel.setJustificationType(juce::Justification::left);
    timeIntervalSlider.setBounds(30, 90, 220, 20);

    feedbackLabel.setBounds(30, 140, 220, 30);
    feedbackUnitLabel.setBounds(250, 170, 220, 20);
    feedbackLabel.setJustificationType(juce::Justification::left);
    feedbackSlider.setBounds(30, 170, 220, 20);

    dryLabel.setBounds(360, 60, 220, 30);
    dryUnitLabel.setBounds(580, 90, 220, 20);
    dryLabel.setJustificationType(juce::Justification::left);
    drySlider.setBounds(360, 90, 220, 20);

    wetLabel.setBounds(360, 140, 220, 30);
    wetUnitLabel.setBounds(580, 170, 220, 20);
    wetLabel.setJustificationType(juce::Justification::left);
    wetSlider.setBounds(360, 170, 220, 20);

    pingPongFreqLabel.setBounds(360, 220, 220, 30);
    pingPongFreqUnitLabel.setBounds(580, 250, 220, 20);
    pingPongFreqLabel.setJustificationType(juce::Justification::left);
    pingPongFreqSlider.setBounds(360, 250, 220, 20);

    zenoToggle.setBounds(30, 220, 150, 60);

    pingPongToggle.setBounds(195, 220, 150, 60);
}

void A2StarterAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    audioProcessor.volumeBoost = volumeSlider.getValue();
}
