#include "rhsaccesssubthread.h"
#include "rhsaccess.h"
#include <QDebug>
#include <QThread>

RHSAccessSubThread::RHSAccessSubThread(RHSAccess* pRHSAccess, QObject *parent) : QThread(parent)
{
    l_pRHSAccess = pRHSAccess;
}

void RHSAccessSubThread::run()
{
    l_pRHSAccess->ReadFromRHSContinuous();
}


