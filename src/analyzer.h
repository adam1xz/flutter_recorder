#ifndef ANALYZER_H
#define ANALYZER_H

#include "common.h"

class Analyzer {
public:
    // Modified constructor to include sample rate
    Analyzer(int windowSize, float sampleRate = 44100.0f);
    ~Analyzer();

    // float *calcFFT(float *waveData);
    float *calcFFT(float *waveData, float minFrequency = 20.0f, float maxFrequency = 16000.0f);
    void setWindowsSize(int fftWindowSize);
    void setSmoothing(float smooth);

private:
    /// @brief elaborate FFT data with the Blackman windowing algorithm
    void blackmanWindow(float *samples, const float *waveData) const;

    /// @brief elaborate FFT data with the hanning windowing algorithm
    void hanningWindow(float* samples, const float *waveData) const;

    /// @brief elaborate FFT data with the hamm windowing algorithm
    void hammingWindow(float* samples, const float *waveData) const;

    void gaussWindow(float *samples, const float *waveData) const;

    /// array used by filling it with audio samples and calculate FFT
    float temp[8192];  // Increased from 1024 to 8192 for higher resolution FFT

    /// contains latest calulated FFT
    float FFTData[256];

    /// window size used by windowing algorithms.
    /// The size is optained when the player has been initialized
    /// and is given by the backend buffer size
    /// over its number of channels (maybe@#`#@`#!!)
    int mWindowSize;

    /// parameters for the Blackman windowing algorithm
    float alpha;
    float a0;
    float a1;
    float a2;
    float fftSmoothing;

    float sampleRate;
    float getBinFrequency(int binIndex) const;

    float minFreq;    // Minimum frequency to analyze
    float maxFreq;    // Maximum frequency to analyze
    int minBin;       // Minimum FFT bin corresponding to minFreq
    int maxBin;       // Maximum FFT bin corresponding to maxFreq

    int freqToBin(float frequency) const;
    int mapFrequencyToFFTDataIndex(float freq) const;
    float mapFFTDataIndexToFrequency(int index) const;
};

#endif // ANALYZER_H
