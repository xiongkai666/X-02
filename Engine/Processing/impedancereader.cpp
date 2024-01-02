#include <QProgressDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include <deque>
#include <iostream>
#include <QTimer>
#include <QElapsedTimer>
#include <QDir>
#include <QDateTime>
#include <QThread>
#include <QApplication>
#include "impedancereader.h"
#include "rhsaccess.h"
#include "rhsaccesssubthread.h"

ImpedanceReader::ImpedanceReader(QObject *parent) : QObject(parent)
{

}

void ImpedanceReader::measureImpedances(){

    int maxProgress = 100;
    QProgressDialog progress(QObject::tr("正在测量电极阻抗"), QString(), 0, maxProgress);
    progress.setWindowTitle(QObject::tr("提示"));
    progress.setMinimumSize(240, 100);
    progress.setMinimumDuration(0);
    progress.setModal(true);
    progress.setValue(0);

    for (int i = 1; i < 6; ++i) {
        progress.setValue(10 * i);
        QThread::msleep(1000);
    }

    qDebug() << "measureImpedances::impedanceFileData.mid(0,256)" << state.ra.impedanceFileData.mid(0,256);

    int index = 0;
    for(int i = 0; i < 256; i += 4){
        QByteArray dataChunk = state.ra.impedanceFileData.mid(i,4);
        if((static_cast<unsigned char>(dataChunk.at(0)) == 0xff)
        &&(static_cast<unsigned char>(dataChunk.at(1)) == 0xff)
        &&(static_cast<unsigned char>(dataChunk.at(2)) == 0xc0)
        &&(static_cast<unsigned char>(dataChunk.at(3)) == 0x41)){
            break;
        }else{
            index ++;
        }
    }
    QByteArray impedanceData = state.ra.impedanceFileData.mid(4*index);

    vector<QByteArray> channelImpedanceStream(16);
    int loop = 100;
    for(int i = 0 ; i < 16; i++){
        channelImpedanceStream[i] = impedanceData.mid(20 * 20 * 4 + i * loop * 20 * 4 + 4 * i + 4, 60 * 20 * 4);
    }

    vector<vector<ComplexPolar>> measuredImpedance(16, vector<ComplexPolar>(60 * 20));

    for(int channel = 0; channel < 16; ++ channel){
        progress.setValue(60 + 2 * channel);
        for (int stream = 0; stream < 60 * 20; ++stream) {
            measuredImpedance[channel][stream]=
                    measureComplexAmplitude(channelImpedanceStream[channel],20000,1000.0);
        }
    }
    vector <ComplexPolar> perChannelImpedance(16);
    for(int channel = 0; channel < 16; ++ channel){
        for (int stream = 0; stream < 60 * 20; ++stream) {
            const double DacVoltageAmplitude = 128.0 * (1.225 / 256.0); // 电压幅度
            double parasiticCapacitance = 15.0e-12;//并联电容
            double relativeFreq = 1 / 20.0;
            double cSeries = 0.1e-12;
            double actualImpedanceFreq = 1000.0;
            double sampleRate = 20000;
            double period = sampleRate / actualImpedanceFreq;
            double current = TwoPi * actualImpedanceFreq * DacVoltageAmplitude * cSeries;

            ComplexPolar impedance;

            impedance.magnitude = 1.0e-9 * (measuredImpedance[channel][stream].magnitude / current) *
                    (18.0 * relativeFreq * relativeFreq + 1.0);
            impedance.phase = measuredImpedance[channel][stream].phase + (360.0 * (3.0 / period));

            impedance = factorOutParallelCapacitance(impedance, actualImpedanceFreq, parasiticCapacitance);

            impedance.magnitude = 1.1 * impedance.magnitude;//RHS芯片被低估

            perChannelImpedance[channel] = impedance;
        }
    }

    //double saturationVoltage = approximateSaturationVoltage(actualImpedanceFreq,actualUpperBandwidth);

    ImpedanceReader impedanceReader;
    impedanceReader.saveImpedanceData(perChannelImpedance);
    actualImpedance.resize(16);
    for(int channel = 0; channel < 16; ++ channel){
        actualImpedance[channel] = perChannelImpedance[channel].magnitude;
    }
    progress.setValue(maxProgress);
}
/*
double ImpedanceReader::approximateSaturationVoltage(double actualZFreq, double highCutoff)
{
    if (actualZFreq < 0.2 * highCutoff) {
        return 5000.0;
    } else {
        return 5000.0 * sqrt(1.0 / (1.0 + pow(3.3333 * actualZFreq / highCutoff, 4.0)));
    }
}
*/
ComplexPolar ImpedanceReader::factorOutParallelCapacitance(ComplexPolar impedance, double frequency,double parasiticCapacitance)
{
    // First, convert from polar coordinates to rectangular coordinates.
    double measuredR = impedance.magnitude * cos(DegreesToRadians * impedance.phase);
    double measuredX = impedance.magnitude * sin(DegreesToRadians * impedance.phase);

    double capTerm = TwoPi * frequency * parasiticCapacitance;
    double xTerm = capTerm * (measuredR * measuredR + measuredX * measuredX);
    double denominator = capTerm * xTerm + 2.0 * capTerm * measuredX + 1.0;
    double trueR = measuredR / denominator;
    double trueX = (measuredX + xTerm) / denominator;

    // Now, convert from rectangular coordinates back to polar coordinates.
    ComplexPolar result;
    result.magnitude = sqrt(trueR * trueR + trueX * trueX);
    result.phase = RadiansToDegrees * atan2(trueX, trueR);
    return result;
}

ComplexPolar ImpedanceReader::measureComplexAmplitude(QByteArray & channelStream, double sampleRate, double frequency)
{

    vector<double> waveform(60 * 20);
    int index = 0;
    for(int i = 0; i < 60 * 20 * 4; i += 4){
        waveform[index++] = vc.getAmplifierData(channelStream.mid(i,4));
    }

    double notchFreq = 50.0;
    double NotchBandwidth = 10.0;

    applyNotchFilter(waveform, notchFreq, NotchBandwidth, sampleRate);

    int startIndex = 59 * 20;
    int endIndex = startIndex + 20 - 1;

    return amplitudeOfFreqComponent(waveform, startIndex, endIndex, sampleRate, frequency);

}

void ImpedanceReader::applyNotchFilter(vector<double> & waveform, double fNotch, double bandwidth, double sampleRate) const
{
    double d = exp(-1.0 * Pi * bandwidth / sampleRate);
    double b = (1.0 + d * d) * cos(TwoPi * fNotch / sampleRate);
    double b0 = (1.0 + d * d) / 2.0;
    double b1 = -b;
    double b2 = b0;
    double a1 = b1;
    double a2 = d * d;
    int length = (int) waveform.size();

    double prevPrevIn = waveform[0];
    double prevIn = waveform[1];
    for (int t = 2; t < length; ++t) {
        double in = waveform[t];
        waveform[t] = b0 * in + b1 * prevIn + b2 * prevPrevIn - a1 * waveform[t - 1] - a2 * waveform[t - 2];  // Direct Form 1 implementation
        prevPrevIn = prevIn;
        prevIn = in;
    }
}

//使用傅里叶变换
ComplexPolar ImpedanceReader::amplitudeOfFreqComponent(const vector<double> &waveform, int startIndex, int endIndex,
                                                       double sampleRate, double frequency)
{
    const double K = TwoPi * frequency / sampleRate;
    double meanI = 0.0;
    double meanQ = 0.0;
    for (int t = startIndex; t <= endIndex; ++t) {
        meanI += waveform[t] * cos(K * t);
        meanQ += waveform[t] * -1.0 * sin(K * t);
    }
    double length = (double)(endIndex - startIndex + 1);
    meanI /= length;
    meanQ /= length;

    double realComponent = 2.0 * meanI;
    double imagComponent = 2.0 * meanQ;

    ComplexPolar result;
    result.magnitude = sqrt(realComponent * realComponent + imagComponent * imagComponent);
    result.phase = RadiansToDegrees * atan2(imagComponent, realComponent);
    return result;
}

void ImpedanceReader::saveImpedanceData(vector<ComplexPolar> & imdepanceDate) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString folderName = "impedance" + currentDateTime.toString("yyyyMMdd_hhmmss");
    QDir().mkpath("../RecordingData");
    QDir().mkpath("../RecordingData/" + folderName);
    QFile csvFile("../RecordingData/" + folderName + "/impedance.csv");

    if (csvFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&csvFile);

        out << "Channel Name,";
        out << "Impedance Magnitude at 1000 Hz (ohms),";
        out << "Impedance Phase at 1000 Hz (degrees)"<< "\n";

        for (int channel = 0; channel < 16; ++channel) {
            out << "I-" << channel <<",";
            out << imdepanceDate[channel].magnitude << ",";
            out << imdepanceDate[channel].phase << "\n";
        }
    }
    csvFile.close();
}

void ImpedanceReader::runDemoImpedanceMeasurement()
{
    int maxProgress = 50;
    QProgressDialog progress(QObject::tr("正在测量电极阻抗"), QString(), 0, maxProgress);
    progress.setWindowTitle(QObject::tr("演示"));
    progress.setMinimumSize(240, 100);
    progress.setMinimumDuration(0);
    progress.setModal(true);
    progress.setValue(0);

    QElapsedTimer timer;
    timer.start();
    for (int i = 1; i < maxProgress; ++i) {
        progress.setValue(i);
        while (timer.nsecsElapsed() < qint64(50000000)) {
            qApp->processEvents();
        }
        timer.restart();
    }
    progress.setValue(maxProgress);
}
