#include <QProgressDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include <deque>
#include <iostream>
#include "impedancereader.h"
#include "controlwindow.h"

ImpedanceReader::ImpedanceReader(QObject *parent) : QObject(parent)
{

}
void ImpedanceReader::runDemoImpedanceMeasurement()
{

    int deviceState = 0;
    imState.updateDeviceState(deviceState);
    // Create a progress bar to let user know how long this will take.
    int maxProgress = (deviceState == 02) ? 50 : 98;
    QProgressDialog progress(QObject::tr("Measuring Electrode Impedances"), QString(), 0, maxProgress);
    progress.setWindowTitle(QObject::tr("Progress"));
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

    for(int i = 0; i < 16; ++i){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(i+16));
        if(label) {
            label->setText("I-" + QString::number(i) +"\t" + "6.4 MΩ");
        }
    }
}
