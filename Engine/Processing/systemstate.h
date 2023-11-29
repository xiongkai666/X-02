#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <QString>
#include "rhsaccess.h"

class SystemState
{
public:
    void updateDeviceState(int& deviceState);
    void deviceStateinfo(int deviceState);
    RHSAccess ra;
};

#endif // SYSTEMSTATE_H
