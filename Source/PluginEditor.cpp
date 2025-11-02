#include "PluginEditor.h"
#include "PluginProcessor.h"

//===== Component Initializers =====

void A2StarterAudioProcessorEditor::initTimeIntervalKnob() {
    timeIntervalLabel.setText("Time Interval", juce::dontSendNotification);
    timeIntervalLabel.setJustificationType(juce::Justification::centredLeft);
    timeIntervalLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    timeIntervalKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    timeIntervalKnob.setRange(0, 3, 0.01);
    timeIntervalKnob.setPopupDisplayEnabled(true, false, this);
    timeIntervalKnob.setValue(0);

    timeIntervalKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    timeIntervalKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    timeIntervalKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    timeIntervalKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&timeIntervalLabel);
    addAndMakeVisible(&timeIntervalKnob);
}

void A2StarterAudioProcessorEditor::initFeedbackKnob() {
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centredLeft);
    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    feedbackKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    feedbackKnob.setRange(0, 100, 1);
    feedbackKnob.setPopupDisplayEnabled(true, false, this);
    feedbackKnob.setValue(0);

    feedbackKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    feedbackKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    feedbackKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    feedbackKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&feedbackLabel);
    addAndMakeVisible(&feedbackKnob);
}

void A2StarterAudioProcessorEditor::initDryKnob() {
    dryLabel.setText("Dry", juce::dontSendNotification);
    dryLabel.setJustificationType(juce::Justification::centredLeft);
    dryLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    dryKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    dryKnob.setRange(0, 100, 1);
    dryKnob.setPopupDisplayEnabled(true, false, this);
    dryKnob.setValue(0);

    dryKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    dryKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    dryKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    dryKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&dryLabel);
    addAndMakeVisible(&dryKnob);
}

void A2StarterAudioProcessorEditor::initWetKnob() {
    wetLabel.setText("Wet", juce::dontSendNotification);
    wetLabel.setJustificationType(juce::Justification::centredLeft);
    wetLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    wetKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    wetKnob.setRange(0, 100, 1);
    wetKnob.setPopupDisplayEnabled(true, false, this);
    wetKnob.setValue(0);

    wetKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    wetKnob.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    wetKnob.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    wetKnob.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);

    addAndMakeVisible(&wetLabel);
    addAndMakeVisible(&wetKnob);
}

//===== Constructor & Destructor =====

A2StarterAudioProcessorEditor::A2StarterAudioProcessorEditor(A2StarterAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    setSize(1200, 400);

    initTimeIntervalKnob();
    initFeedbackKnob();
    initDryKnob();
    initWetKnob();
}

A2StarterAudioProcessorEditor::~A2StarterAudioProcessorEditor() {}

void A2StarterAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::black);
    g.setFont(24.0f);
    g.drawFittedText("Digital Delay", 0, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void A2StarterAudioProcessorEditor::resized() {
    timeIntervalLabel.setBounds(30, 60, 100, 30);
    timeIntervalLabel.setJustificationType(juce::Justification::centred);
    timeIntervalKnob.setBounds(140, 60, 180, 40);

    feedbackLabel.setBounds(360, 60, 100, 30);
    feedbackLabel.setJustificationType(juce::Justification::centred);
    feedbackKnob.setBounds(470, 60, 180, 40);

    dryLabel.setBounds(30, 140, 100, 30);
    dryLabel.setJustificationType(juce::Justification::centred);
    dryKnob.setBounds(140, 140, 180, 40);

    wetLabel.setBounds(360, 140, 100, 30);
    wetLabel.setJustificationType(juce::Justification::centred);
    wetKnob.setBounds(470, 140, 180, 40);
}

void A2StarterAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    audioProcessor.volumeBoost = volumeSlider.getValue();
}
