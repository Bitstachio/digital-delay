#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DelayParams.h"

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

    // Multiply sample rate by 3 to accommodate the max delay of 3 seconds
    // Multiple sample rate by 2 to accommodate for echos in Zeno mode
    delayBufferLength = static_cast<int>(sampleRate * 6);

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

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples             = buffer.getNumSamples();

    // Clear extra output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    float interval = apvts.getRawParameterValue("TIME_INTERVAL")->load();
    float feedback = apvts.getRawParameterValue("FEEDBACK")->load() / 100;
    float dryLevel = apvts.getRawParameterValue("DRY")->load() / 100;
    float wetLevel = apvts.getRawParameterValue("WET")->load() / 100;

    bool isZenoMode     = apvts.getRawParameterValue("ZENO")->load();
    bool isPingPongMode = apvts.getRawParameterValue("PING_PONG")->load();

    float pingPongFreq = 100;

    phase += 2.0f * juce::MathConstants<float>::pi * pingPongFreq / rate;
    if (phase > 2.0f * juce::MathConstants<float>::pi)
        phase -= 2.0f * juce::MathConstants<float>::pi;

    float gainLeft  = 0.5f * (1.0f + std::sin(phase));
    float gainRight = 0.5f * (1.0f - std::sin(phase));

    // Normalize dry/wet if > 1.0
    float mixSum = dryLevel + wetLevel;
    if (mixSum > 1.0f) {
        dryLevel /= mixSum;
        wetLevel /= mixSum;
    }

    // Ensure per-channel delay indices
    if (delayBufferIndices.size() != totalNumInputChannels)
        delayBufferIndices.resize(totalNumInputChannels, 0);

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        float *channelData = buffer.getWritePointer(channel);
        float *delayData   = delayBuffer.getWritePointer(channel);
        int   &index       = delayBufferIndices[channel];

        for (int i = 0; i < numSamples; i++) {
            float inputSample = channelData[i];

            /* Clear buffer position after reading the delayed sample.
             * Delayed samples are added rather than replaced.
             * If not cleared, leftover values persist and keep accumulating,
             * even when no new input is present. */
            float delayedSample = delayData[index];
            delayData[index]    = 0;

            // Output with dry/wet mix, clipped
            float outSample = dryLevel * inputSample + wetLevel * delayedSample;

            if (isPingPongMode) {
                if (channel == 0) {
                    outSample *= gainLeft;
                } else if (channel == 1) {
                    outSample *= gainRight;
                }
            }

            channelData[i] = juce::jlimit(-1.0f, 1.0f, outSample);

            /* Use addition instead of replacement to support Zeno mode.
             * In Zeno mode, echoes are scheduled in the future, so multiple delayed
             * samples may overlap in the buffer. Adding ensures that upcoming echoes
             * aren't overwritten by zeros from earlier, empty samples. */
            float offset = interval * rate; // Set to float to accommodate Zeno mode
            if (isZenoMode) {
                float gain = offset / 2.0f;
                for (int i = 0;; i++, offset += gain, gain /= 2) {
                    int   echoIndex = static_cast<int>(index + offset) % delayBufferLength;
                    float echo      = inputSample * pow(feedback, i + 1);

                    if (std::fabs(echo) < 0.0001)
                        break;
                    delayData[echoIndex] += echo;
                }
            } else {
                int echoIndex        = static_cast<int>(index + offset) % delayBufferLength;
                delayData[echoIndex] = inputSample + delayedSample * feedback;
            }

            // Increment delay buffer index (wrap around)
            index = (index + 1) % delayBufferLength;
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

void A2StarterAudioProcessor::clearDelayBuffer() {
    delayBuffer.clear();
}

juce::AudioProcessorValueTreeState::ParameterLayout A2StarterAudioProcessor::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("TIME_INTERVAL", "Time Interval",
                                                                 DelayParams::INTERVAL_MIN, DelayParams::INTERVAL_MAX,
                                                                 DelayParams::INTERVAL_DEFAULT));
    params.push_back(std::make_unique<juce::AudioParameterInt>(
        "FEEDBACK", "Feedback", DelayParams::FEEDBACK_MIN, DelayParams::FEEDBACK_MAX, DelayParams::FEEDBACK_DEFAULT));
    params.push_back(std::make_unique<juce::AudioParameterInt>("DRY", "Dry", DelayParams::DRY_MIN, DelayParams::DRY_MAX,
                                                               DelayParams::DRY_DEFAULT));
    params.push_back(std::make_unique<juce::AudioParameterInt>("WET", "Wet", DelayParams::WET_MIN, DelayParams::WET_MAX,
                                                               DelayParams::WET_DEFAULT));
    params.push_back(std::make_unique<juce::AudioParameterBool>("ZENO", "Zeno", DelayParams::IS_ZENO_MODE_DEFAULT));
    params.push_back(
        std::make_unique<juce::AudioParameterBool>("PING_PONG", "Ping Pong", DelayParams::IS_PING_PONG_DEFAULT));

    return {params.begin(), params.end()};
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new A2StarterAudioProcessor();
}
