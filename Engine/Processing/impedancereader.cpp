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
#include "impedancereader.h"
#include "rhsaccesssubthread.h"
#include "rhsaccess.h"

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
