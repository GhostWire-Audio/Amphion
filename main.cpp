#include <iostream>
#include <cmath>
#include "portaudio.h"

struct AudioData {
    float phase;
    float frequency;
    float sampleRate;
    int numChannels;
};

int audioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    const unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    auto* out = static_cast<float*>(outputBuffer);
    auto data = static_cast<AudioData*>(userData);

    const float phaseIncrement = (2.0f * static_cast<float>(M_PI) * data->frequency) / data->sampleRate;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        for (int j = 0; j < data->numChannels; j++) {
            out[i * data->numChannels + j] = std::sin(data->phase);
        }
        data->phase += phaseIncrement;
        if (data->phase >= 2.0f * static_cast<float>(M_PI)) { data->phase -= 2.0f * static_cast<float>(M_PI); }
    }

    return paContinue;
}

int main() {
    Pa_Initialize();

    if (Pa_GetDefaultOutputDevice() == paNoDevice) {
        std::cerr << "No output device found" << std::endl;
        return 1;
    }

    PaStream* stream;
    AudioData data{0.0f, 440.0f, 44100.0f, 2};

    PaStreamParameters outputParams;
    outputParams.device = Pa_GetDefaultOutputDevice();
    outputParams.channelCount = data.numChannels;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = nullptr;

    PaError err = Pa_OpenStream(&stream, nullptr, &outputParams,
        data.sampleRate, 512, paClipOff, audioCallback, &data);
    if (err != paNoError) {
        std::cerr << "Pa_OpenStream failed: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Pa_StartStream failed: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    Pa_Sleep(3000);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}