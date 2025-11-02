#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

class A2StarterAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Slider::Listener {
public:
    A2StarterAudioProcessorEditor(A2StarterAudioProcessor &);
    ~A2StarterAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider *slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A2StarterAudioProcessor &audioProcessor;

    //===== Volume Slider ======

    juce::Label volumeLabel;

    juce::Slider                                                          volumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    void initVolumeSlider();

    //===== Time Interval Knob ======

    juce::Label timeIntervalLabel;

    juce::Slider                                                          timeIntervalKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeIntervalAttachment;

    void initTimeIntervalKnob();

    //===== Feedback Knob ======

    juce::Label feedbackLabel;

    juce::Slider                                                          feedbackKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    void initFeedbackKnob();

    //===== Dry Knob ======

    juce::Label dryLabel;

    juce::Slider                                                          dryKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryAttachment;

    void initDryKnob();

    //===== Wet Knob ======

    juce::Label wetLabel;

    juce::Slider                                                          wetKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;

    void initWetKnob();

    //===== Macros =====

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(A2StarterAudioProcessorEditor)
};
