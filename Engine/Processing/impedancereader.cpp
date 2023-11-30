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
#include <QApplication>
#include <QDir>
#include <QDateTime>
#include "impedancereader.h"

ImpedanceReader::ImpedanceReader(QObject *parent) : QObject(parent)
{

}

void ImpedanceReader::measureImpedances(){
    int maxProgress = 50;
    qDebug() << "measureImpedances is running";
    QProgressDialog progress(QObject::tr("Measuring Electrode Impedances"), QString(), 0, maxProgress);
    progress.setWindowTitle(QObject::tr("Progress"));
    progress.setMinimumDuration(0);
    progress.setModal(true);
    progress.setValue(20);
    progress.setValue(maxProgress);

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
