#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>
#include <QDateTime>
#include <QDir>
#include "csvfilesave.h"

void saveRecordData(const QVector<QVector<QPointF>>& coordinatesArray) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString folderName = "coordinate" + currentDateTime.toString("yyyyMMdd_hhmmss");
    QDir().mkpath("../RecordingData");
    QDir().mkpath("../RecordingData/" + folderName);
    QFile file("../RecordingData/" + folderName + "/XY.csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for(int channel = 0; channel < 16; ++channel){
            out << "V-" << channel <<":" << "X,Y;";
        }
        out << "\n";
        for (int i = 0; i < coordinatesArray.size(); ++i) {
            QVector<QPointF> data = coordinatesArray[i];
            for (int j = 0; j < data.size(); ++j) {
                out << qSetFieldWidth(1) << data[j].x() << "," << data[j].y() << ";";
            }
            out << "\n";
        }
        file.close();
    }
}



