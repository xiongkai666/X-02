#include <QMessageBox>
#include "systemstate.h"

void SystemState::updateDeviceState(int& deviceState)
{
    QString qID;
    bool isSerialOpened;
    int deviceCount;
    int bitConfig;

    ra.InitializeXMS6302(deviceCount,qID,isSerialOpened);
    ra.setFPGAbit(bitConfig);

    if(!qID.isEmpty() && isSerialOpened && bitConfig == 0 ) {
        deviceState = 02;
    } else {
        deviceState = 01;
    }
}

void SystemState::deviceStateinfo(int deviceState)
{

    if(deviceState == 01) {
        QMessageBox::information(NULL, "提示", "未连接设备，只能使用本地演示功能","继续");
    }
    if(deviceState == 02) {
        QMessageBox::information(NULL, "提示", "成功连接并配置设备，可以使用在线功能","继续");
    }
}

void SystemState::deviceReset()
{
    ra.ResetFPGA();
    ra.InitializeRHS2116();
    ra.DebugFPGA();
}

