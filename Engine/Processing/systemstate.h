#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <QString>
#include "rhsaccess.h"

class SystemState
{
public:
    void updateDeviceState(int& deviceState);
    RHSAccess raState;
};

#endif // SYSTEMSTATE_H
