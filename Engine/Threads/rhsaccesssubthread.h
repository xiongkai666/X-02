#ifndef RHSACCESSSUBTHREAD_H
#define RHSACCESSSUBTHREAD_H

#include <QThread>
#include "PionwayDLL.h"
#include "rhsaccess.h"

class RHSAccessSubThread : public QThread, public CPionway
{
    Q_OBJECT
public:
    explicit RHSAccessSubThread(RHSAccess* pRHSAccess, QObject *parent = nullptr);

    RHSAccess* l_pRHSAccess;

    bool StopFlag;
    int DeviceCount;
    std::string ID;
    bool isOpened;
    int Closecode;

    void run() override;


signals:
    void ReadRHSDataContinuous(QString);

public slots:

};

#endif
