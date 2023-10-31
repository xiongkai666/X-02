#ifndef XLSFILESAVE_H
#define XLSFILESAVE_H

#include <QPointF>

void saveDataToCSV(const QVector<QVector<QPointF>>& channelData, const QString& filePath);

#endif // XLSFILESAVE_H
