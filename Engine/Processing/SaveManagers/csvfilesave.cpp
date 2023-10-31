#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtGlobal>
#include "csvfilesave.h"

void saveDataToCSV(const QVector<QVector<QPointF>>& coordinatesArray, const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < coordinatesArray.size(); ++i) {
            QVector<QPointF> data = coordinatesArray[i];
            for (int j = 0; j < data.size(); ++j) {
                out << qSetFieldWidth(1) << data[j].x() << "," << data[j].y() << ";";
            }
            out << "\n";
        }
        file.close();
        qDebug() << "Data saved to" << filePath;
    } else {
        qDebug() << "Error opening file:" << file.errorString();
    }
}


