#ifndef IMPEDANCEREADER_H
#define IMPEDANCEREADER_H

#include <vector>
#include <deque>
#include "systemstate.h"
#include "voltagecalculation.h"

using namespace std;

const double Pi = 3.14159265359;
const double TwoPi = 6.28318530718;
const double DegreesToRadians = 0.0174532925199;
const double RadiansToDegrees = 57.2957795132;

struct ComplexPolar {
    double magnitude;
    double phase;
};

class ImpedanceReader:public QObject
{
    Q_OBJECT
public:
    ImpedanceReader(QObject *parent = nullptr);

    void measureImpedances();
    static double approximateSaturationVoltage(double actualZFreq, double highCutoff);
    ComplexPolar factorOutParallelCapacitance(ComplexPolar impedance, double frequency, double parasiticCapacitance);
    ComplexPolar measureComplexAmplitude(QByteArray & channelStream, double sampleRate,double frequency);
    void applyNotchFilter(vector<double> &waveform, double fNotch, double bandwidth, double sampleRate) const;
    static ComplexPolar amplitudeOfFreqComponent(const vector<double> &waveform, int startIndex, int endIndex,
                                                double sampleRate, double frequency);

    void saveImpedanceData(vector<ComplexPolar> & imdepanceDate);
    void runDemoImpedanceMeasurement();

    SystemState state;
    int deviceState = 0;
    VoltageCalculation vc;

    vector<double>actualImpedance;

};

#endif // IMPEDANCEREADER_H
