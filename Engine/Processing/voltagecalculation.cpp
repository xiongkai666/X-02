
#include "voltagecalculation.h"

double VoltageCalculation::getAmplifierData(QByteArray amplifierData){

        QByteArray qHighAmplifierData = amplifierData.mid(0,1);
        QByteArray qLowAmplifierData = amplifierData.mid(1,1);

        int highAmplifierData = qHighAmplifierData.toHex().toInt(nullptr, 16);
        int lowAmplifierData = qLowAmplifierData.toHex().toInt(nullptr, 16);
        int realAmplifierData;
        realAmplifierData = highAmplifierData * 256 + lowAmplifierData;

        double realVoltage = 0.195 * (realAmplifierData - 32768) / 1000;

        return realVoltage;
}
