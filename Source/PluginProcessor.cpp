#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A2StarterAudioProcessor::A2StarterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
#endif
      apvts(*this, nullptr, "Parameters", createParameterLayout()) {
}

A2StarterAudioProcessor::~A2StarterAudioProcessor() {}

//==============================================================================
const juce::String A2StarterAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool A2StarterAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool A2StarterAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool A2StarterAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double A2StarterAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int A2StarterAudioProcessor::getNumPrograms() {
    return 1; // NB: some hosts don't cope very well if you tell them there are 0
              // programs, so this should be at least 1, even if you're not really
              // implementing programs.
}

int A2StarterAudioProcessor::getCurrentProgram() {
    return 0;
}

void A2StarterAudioProcessor::setCurrentProgram(int index) {}

const juce::String A2StarterAudioProcessor::getProgramName(int index) {
    return {};
}

void A2StarterAudioProcessor::changeProgramName(int index, const juce::String &newName) {}

//==============================================================================
void A2StarterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    rate        = static_cast<float>(sampleRate);
    volumeBoost = 1.0;

    delayBufferLength = static_cast<int>(sampleRate * 3.0f);

    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();
}

void A2StarterAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool A2StarterAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void A2StarterAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto                    totalNumInputChannels  = getTotalNumInputChannels();
    auto                    totalNumOutputChannels = getTotalNumOutputChannels();
    auto                    numSamples             = buffer.getNumSamples();

    // Clear extra output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    float interval = apvts.getRawParameterValue("TIME_INTERVAL")->load();
    float feedback = apvts.getRawParameterValue("FEEDBACK")->load() / 100;
    float dryLevel = apvts.getRawParameterValue("DRY")->load() / 100;
    float wetLevel = apvts.getRawParameterValue("WET")->load() / 100;

    // Normalize dry/wet if > 1.0
    float mixSum = dryLevel + wetLevel;
    if (mixSum > 1.0f) {
        dryLevel /= mixSum;
        wetLevel /= mixSum;
    }

    int usedDelayBufferLength = static_cast<int>(rate * interval + 0.5f);

    // Ensure per-channel delay indices
    if (delayBufferIndices.size() != totalNumInputChannels)
        delayBufferIndices.resize(totalNumInputChannels, 0);

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        float *channelData = buffer.getWritePointer(channel);
        float *delayData   = delayBuffer.getWritePointer(channel);
        int   &index       = delayBufferIndices[channel];

        for (int i = 0; i < numSamples; i++) {
            float inputSample   = channelData[i];
            float delayedSample = delayData[index];

            // Output with dry/wet mix, clipped
            float outSample = dryLevel * inputSample + wetLevel * delayedSample;
            channelData[i]  = juce::jlimit(-1.0f, 1.0f, outSample);

            // Feedback: store into delay buffer without clipping
            delayData[index] = inputSample + delayedSample * feedback;

            // Increment delay buffer index (wrap around)
            index = (index + 1) % usedDelayBufferLength;
        }
    }
}

//==============================================================================
bool A2StarterAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *A2StarterAudioProcessor::createEditor() {
    return new A2StarterAudioProcessorEditor(*this);
}

//==============================================================================
void A2StarterAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void A2StarterAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
}

juce::AudioProcessorValueTreeState::ParameterLayout A2StarterAudioProcessor::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("TIME_INTERVAL", "Time Interval", 0.0f, 3.0f, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("FEEDBACK", "Feedback", 0, 100, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRY", "Dry", 0, 100, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("WET", "Wet", 0, 100, 0));
    params.push_back(std::make_unique<juce::AudioParameterBool>("ZENO", "Zeno", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("PING_PONG", "Ping Pong", false));

    return {params.begin(), params.end()};
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new A2StarterAudioProcessor();
}
