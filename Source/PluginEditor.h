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

    //===== Time Interval Slider ======

    juce::Label timeIntervalLabel;

    juce::Slider                                                          timeIntervalSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeIntervalAttachment;

    void initTimeIntervalSlider();

    //===== Feedback Slider ======

    juce::Label feedbackLabel;

    juce::Slider                                                          feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    void initFeedbackSlider();

    //===== Dry Slider ======

    juce::Label dryLabel;

    juce::Slider                                                          drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryAttachment;

    void initDrySlider();

    //===== Wet Slider ======

    juce::Label wetLabel;

    juce::Slider                                                          wetSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;

    void initWetSlider();

    //===== Zeno Toggle ======

    juce::ToggleButton                                                    zenoToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> zenoAttachment;

    void initZenoToggle();

    //===== Ping Pong Toggle ======

    juce::ToggleButton                                                    pingPongToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> pingPongAttachment;

    void initPingPongToggle();

    //===== Macros =====

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(A2StarterAudioProcessorEditor)
};
