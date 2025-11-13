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
    struct ColorPalette {
        juce::Colour background  = juce::Colour(0xff1e1e1e);
        juce::Colour text        = juce::Colour(0xfff0f0f0);
        juce::Colour accent      = juce::Colour(0xff4aa3df);
        juce::Colour buttonOff   = juce::Colour(0xff3a3a3a);
        juce::Colour buttonOn    = juce::Colour(0xff4aa3df);
        juce::Colour sliderTrack = juce::Colour(0xFF606080);
        juce::Colour sliderThumb = juce::Colour(0xFF6AC1FF);
    };

    ColorPalette colors;

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
    juce::Label timeIntervalUnitLabel;

    juce::Slider                                                          timeIntervalSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeIntervalAttachment;

    void initTimeIntervalSlider();

    //===== Feedback Slider ======

    juce::Label feedbackLabel;
    juce::Label feedbackUnitLabel;

    juce::Slider                                                          feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    void initFeedbackSlider();

    //===== Dry Slider ======

    juce::Label dryLabel;
    juce::Label dryUnitLabel;

    juce::Slider                                                          drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryAttachment;

    void initDrySlider();

    //===== Wet Slider ======

    juce::Label wetLabel;
    juce::Label wetUnitLabel;

    juce::Slider                                                          wetSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;

    void initWetSlider();

    //===== Zeno Toggle ======

    juce::TextButton                                                      zenoToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> zenoAttachment;

    void initZenoToggle();

    //===== Ping-Pong Toggle ======

    juce::TextButton                                                      pingPongToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> pingPongAttachment;

    void initPingPongToggle();

    //===== Ping-Pong Frequency Slider ======

    juce::Label pingPongFreqLabel;
    juce::Label pingPongFreqUnitLabel;

    juce::Slider                                                          pingPongFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pingPongFreqAttachment;

    void initPingPongFreqSlider();

    //===== Clear Buffer Button ======

    juce::TextButton clearButton;

    void initClearButton();

    //===== Macros =====

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(A2StarterAudioProcessorEditor)
};
