#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

class A2StarterAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    A2StarterAudioProcessorEditor(A2StarterAudioProcessor &);
    ~A2StarterAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    A2StarterAudioProcessor &audioProcessor;

    struct ColorPalette {
        juce::Colour background  = juce::Colour(0xff1e1e1e);
        juce::Colour text        = juce::Colour(0xfff0f0f0);
        juce::Colour accent      = juce::Colour(0xff4aa3df);
        juce::Colour buttonOff   = juce::Colour(0xff3a3a3a);
        juce::Colour buttonOn    = juce::Colour(0xff4aa3df);
        juce::Colour sliderTrack = juce::Colour(0xFF606080);
        juce::Colour sliderThumb = juce::Colour(0xFF6AC1FF);
    } palette;

    //===== Component Initializers =====

    void initSlider(juce::Component &parent, juce::Label &mainLabel, juce::Label &unitLabel, juce::Slider &slider,
                    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
                    juce::AudioProcessorValueTreeState &apvts, const juce::String &paramId,
                    const juce::String &labelText, const juce::String &unitText, double minValue, double maxValue,
                    double step, const ColorPalette &palette);

    void initToggleButton(juce::TextButton                                                      &button,
                          std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> &attachment,
                          const juce::String &paramId, const juce::String &labelText, const juce::Colour &offColour,
                          const juce::Colour &onColour, const juce::Colour &textColour);

    void initButton(juce::TextButton &button, const juce::String &labelText, const juce::Colour &offColour,
                    const juce::Colour &onColour, const juce::Colour &textColour, std::function<void()> onClickHandler);

    //===== Delay Parameter Components ======

    // Volume (*)
    juce::Label                                                           volumeLabel;
    juce::Slider                                                          volumeSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    // Time Interval
    juce::Label                                                           timeIntervalLabel;
    juce::Label                                                           timeIntervalUnitLabel;
    juce::Slider                                                          timeIntervalSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeIntervalAttachment;

    // Feedback
    juce::Label                                                           feedbackLabel;
    juce::Label                                                           feedbackUnitLabel;
    juce::Slider                                                          feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    // Dry Level
    juce::Label                                                           dryLabel;
    juce::Label                                                           dryUnitLabel;
    juce::Slider                                                          drySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryAttachment;

    // Wet Level
    juce::Label                                                           wetLabel;
    juce::Label                                                           wetUnitLabel;
    juce::Slider                                                          wetSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;

    // Zeno Mode
    juce::TextButton                                                      zenoToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> zenoAttachment;

    // Ping-Pong Mode
    juce::TextButton                                                      pingPongToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> pingPongAttachment;

    // Ping-Pong Frequency
    juce::Label                                                           pingPongFreqLabel;
    juce::Label                                                           pingPongFreqUnitLabel;
    juce::Slider                                                          pingPongFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pingPongFreqAttachment;

    // Clear Buffer
    juce::TextButton clearButton;

    //===== Macros =====

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(A2StarterAudioProcessorEditor)
};
