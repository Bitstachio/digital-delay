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

    void initSlider(juce::Component &parent, juce::Label &mainLabel, juce::Label &unitLabel, juce::Slider &slider,
                    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
                    juce::AudioProcessorValueTreeState &apvts, const juce::String &paramId,
                    const juce::String &labelText, const juce::String &unitText, double minValue, double maxValue,
                    double step, const ColorPalette &colors);

    void sliderValueChanged(juce::Slider *slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A2StarterAudioProcessor &audioProcessor;

    //===== Volume Slider ======

    juce::Label volumeLabel;

    juce::Slider                                                          volumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    //===== Time Interval Slider ======

    juce::Label timeIntervalLabel;
    juce::Label timeIntervalUnitLabel;

    juce::Slider                                                          timeIntervalSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeIntervalAttachment;

    //===== Feedback Slider ======

    juce::Label feedbackLabel;
    juce::Label feedbackUnitLabel;

    juce::Slider                                                          feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    //===== Dry Slider ======

    juce::Label dryLabel;
    juce::Label dryUnitLabel;

    juce::Slider                                                          drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryAttachment;

    //===== Wet Slider ======

    juce::Label wetLabel;
    juce::Label wetUnitLabel;

    juce::Slider                                                          wetSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;

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

    //===== Clear Buffer Button ======

    juce::TextButton clearButton;

    void initClearButton();

    //===== Macros =====

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(A2StarterAudioProcessorEditor)
};
