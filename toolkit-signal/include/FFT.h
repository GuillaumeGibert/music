#ifndef FFT_H
#define FFT_H

#include <QObject>
#include <QDebug>


#define _USE_MATH_DEFINES
#include <math.h>


class FFT: public QObject
{
    Q_OBJECT

public:
    FFT();
    ~FFT();

public:
    void setNbSignals(int);
    void setFps(float);
    std::vector<std::vector<float>> getPowerSpectrumValues();

public slots:
    void setBufferedSignalValues(std::vector<std::vector<float>> vBufferedSignalValues);

signals:
    void sigBroadcastPowerSpectrumValues(std::vector<std::vector<float>>);

private:
    void compute(std::vector<float> &vInputSignal, std::vector<float> &vFFTRealPart, std::vector<float> &vFFTImagPart);
    void transformRadix2(std::vector<float> &real, std::vector<float> &imag);
    std::size_t reverseBits(std::size_t x, unsigned int n);
    void powerSpectrum(std::vector<float> &vFFTRealPart, std::vector<float> &vFFTImagPart, std::vector<float> &vFFTPowerSpectrum);
    void phaseSpectrum(std::vector<float> &vFFTRealPart, std::vector<float> &vFFTImagPart, std::vector<float> &vFFTPowerSpectrum);
    void hannWindow(std::vector<float>& inSignal, std::vector<float>& outSignal);
    void pad(std::vector<float> &vInputSignal, std::vector<float> &vPaddedSignal);
    unsigned long findUpperPowerOfTwo(unsigned long v);

private:
    int m_i32InSignalLength; /**< padded signal (legnth=power of 2) to be processed */
    std::vector<double> m_vf64cosTable; /**< the cosine table  */
    std::vector<double> m_vf64sinTable; /**< the sine table  */
    bool m_bTrigoTablesComputed;/**<  a boolean to check if we need to compute the trigonometric tables  */

    int m_i32NbSignals;
    float m_fFps;

    std::vector<std::vector<float>> m_vPowerSpectrumValues;

};

#endif

