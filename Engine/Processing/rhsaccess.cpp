#include <QMessageBox>
#include <string>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <chrono>
#include <QDateTime>
#include <QDir>
#include "rhsaccess.h"


RHSAccess::RHSAccess(QObject *parent) : QObject(parent)
{

}

void RHSAccess::InitializeXMS6302(int &DeviceCount, QString &qID, bool &isSerialOpened)
{

    this->GetDeviceCount(&DeviceCount);
    ID = this->GetDeviceListSerial(DeviceCount - 1);
    qID = QString::fromStdString(ID);

    isEndPiontEnabled = this->IsPionwayEnabled();
    qisEndPiontEnabled = QString::number(isEndPiontEnabled);

    this->OpenBySerial(ID);
    isSerialOpened = this->IsOpen();

}

void RHSAccess::setFPGAbit()
{
    this->ConfigureFPGA("../FPGA-bitfiles/test_01.bit");
}
void RHSAccess::ResetFPGA()
{

    int Trigger_Reset = 31;
    ActivateTriggerIn(epAddr_trigIn40, Trigger_Reset);
}

void RHSAccess::InitializeRHS2116()
{
    int epAddr_bpic0 = 0xc0;
    long length = 256;
    long wrcount = 0;
    int writeState;
    QByteArray qbdatabuf; QString qsdatabuf, qswriteState;

    this->OpenBySerial(ID);
    isSerialOpened = this->IsOpen();

    writeState = this->WriteToBlockPipeIn(epAddr_bpic0, 256, length, rhscmd_initialize, &wrcount);

    if (writeState == 0)
    {
        qbdatabuf = QByteArray((char *)rhscmd_initialize, sizeof(rhscmd_initialize));
        qsdatabuf = qbdatabuf.toHex();
        qDebug() << "qsdatabuf"<<qsdatabuf;
        qswriteState.setNum(writeState);

        //emit WriteRHSData(qsdatabuf);
    }
}

void RHSAccess::SetSampleRate(QVariant sampleValue)
{
    int epAddr_wi01 = 0x01;
    UINT32 sampleRate ;

    if (sampleValue.isValid())
    {
        sampleRate = sampleValue.toUInt();
    }
    this->SetWireInValue(epAddr_wi01, sampleRate);
    this->UpdateWireIns();

    int Trigger_DCM_prog = 31;
    this->ActivateTriggerIn(epAddr_trigIn41, Trigger_DCM_prog);

    UINT32 DCMProgState;
    this->UpdateWireOuts();
    this->GetWireOutValue(epAddr_wireOut20, &DCMProgState);
}

void RHSAccess::RHSCMDGen(QString RHSCMD_R1,QString RHSCMD_R2,QString RHSCMD_R3,QString RHSCMD_R4,
                          QString RHSCMD_D1,QString RHSCMD_D2,QString RHSCMD_D3,QString RHSCMD_D4,
                          QString RHSCMD_WRUMDH1, QString RHSCMD_WRUMDH2, QString RHSCMD_WRUMDH3,QString RHSCMD_WRUMDH4)
{
    RHSAccess::QSTring2HEX(RHSCMD_R1, &rhscmd_r1);
    RHSAccess::QSTring2HEX(RHSCMD_R2, &rhscmd_r2);
    RHSAccess::QSTring2HEX(RHSCMD_R3, &rhscmd_r3);
    RHSAccess::QSTring2HEX(RHSCMD_R4, &rhscmd_r4);
    RHSAccess::QSTring2HEX(RHSCMD_D1, rhscmd_d1);
    RHSAccess::QSTring2HEX(RHSCMD_D2, rhscmd_d2);
    RHSAccess::QSTring2HEX(RHSCMD_D3, rhscmd_d3);
    RHSAccess::QSTring2HEX(RHSCMD_D4, rhscmd_d4);
    RHSAccess::QSTring2HEX(RHSCMD_WRUMDH1, &rhscmd_wrumdh1);
    RHSAccess::QSTring2HEX(RHSCMD_WRUMDH2, &rhscmd_wrumdh2);
    RHSAccess::QSTring2HEX(RHSCMD_WRUMDH3, &rhscmd_wrumdh3);
    RHSAccess::QSTring2HEX(RHSCMD_WRUMDH4, &rhscmd_wrumdh4);
    rhscmd[3] = rhscmd_wrumdh1;   rhscmd[2] = rhscmd_r1;  rhscmd[1] = rhscmd_d1[0];   rhscmd[0] = rhscmd_d1[1];
    rhscmd[7] = rhscmd_wrumdh2;   rhscmd[6] = rhscmd_r2;  rhscmd[5] = rhscmd_d2[0];   rhscmd[4] = rhscmd_d2[1];
    rhscmd[11] = rhscmd_wrumdh3;   rhscmd[10] = rhscmd_r3;  rhscmd[9] = rhscmd_d3[0];  rhscmd[8] = rhscmd_d3[1];
    rhscmd[15] = rhscmd_wrumdh4;   rhscmd[14] = rhscmd_r4; rhscmd[13] = rhscmd_d4[0];  rhscmd[12] = rhscmd_d4[1];

}

void RHSAccess::QSTring2HEX(QString src, unsigned char *des)
{
    int bytesize = src.size()/2;bool ok;
    for (int i = 0; i < bytesize; i++)
    {
        QString hex = ("0x" + src.mid(i*2,2));
        des[i] = hex.toUInt(&ok, 16);
    }
}

void RHSAccess::convertStart()
{
    int epAddr_wi00 = 0x00;
    int CONVERTStartWireSig = 0x00000001;
    int Convertstate;
    Convertstate = this->SetWireInValue(epAddr_wi00, CONVERTStartWireSig);
    qDebug() << "Convertstate" << Convertstate;
    this->UpdateWireIns();
}

void RHSAccess::impedanceConvertStart()
{
    int epAddr_wi02 = 0x02;
    int CONVERTStartWireSig = 0x00000001;
    int impedanceConvertstate;
    impedanceConvertstate = this->SetWireInValue(epAddr_wi02, CONVERTStartWireSig);
    qDebug() << "impedanceConvertstate" << impedanceConvertstate;
    this->UpdateWireIns();
}

void RHSAccess::convertStop()
{
    int epAddr_wi00 = 0x00;
    int CONVERTStopWireSig = 0x00000000;
    this->SetWireInValue(epAddr_wi00, CONVERTStopWireSig);
    this->UpdateWireIns();
}
void RHSAccess::impedanceConvertStop()
{
    int epAddr_wi02 = 0x02;
    int CONVERTStopWireSig = 0x00000000;
    this->SetWireInValue(epAddr_wi02, CONVERTStopWireSig);
    this->UpdateWireIns();
}

void RHSAccess::ReadFromRHSContinuous()
{
    int epAddr_bpoe0 = 0xe0;
    long lengthc = 8192;
    int Blocksize = 8192;
    long rdcount = 0;
    int readStatec;
    int rddatabufsizec = 8192;
    rddatabufc = new unsigned char[rddatabufsizec];
    QByteArray qbrddatabufc;

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString folderName = "Record" + currentDateTime.toString("yyyyMMdd_hhmmss");
    QDir().mkpath("../RecordingData");
    QDir().mkpath("../RecordingData/" + folderName);
    QFile file("../RecordingData/" + folderName + "/Data.bin");
    QFile file_TransCycle_duration("../RecordingData/" + folderName + "/TransCycle_duration_record.bin");
    QFile file_chip_0("../RecordingData/" + folderName + "/Chip_0.bin");

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file_TransCycle_duration.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file_chip_0.open(QIODevice::WriteOnly | QIODevice::Truncate);

    for(int i = 0; i < 16; i ++){
        QString filePath = QString("%1/channel_%2.bin").arg("../RecordingData/" + folderName).arg(i);
        file_channel[i].setFileName(filePath);
        file_channel[i].open(QIODevice::WriteOnly | QIODevice::Truncate);
    }

    QByteArray data;
    QDataStream TransCycle_duration_record(&file_TransCycle_duration);

    StopFlag = false;
    while (true){

        auto start = std::chrono::high_resolution_clock::now();
        readStatec = this->ReadFromBlockPipeOut(epAddr_bpoe0, Blocksize, lengthc, rddatabufc, &rdcount);
        //qDebug() << "readStatec" << readStatec;

        if (readStatec == 0)
        {
            qbrddatabufc = QByteArray((char *)rddatabufc, rddatabufsizec);
            data.append(qbrddatabufc);

            for (int i = 0; i<(rddatabufsizec/32); i ++){
                waveFormData.append(qbrddatabufc.mid((32*i+0),4));
                file_chip_0.write(qbrddatabufc.mid((32*i+0),4));
            }

            auto end2 = std::chrono::high_resolution_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start).count();
            TransCycle_duration_record << duration2;
        }

        if (StopFlag){
            qDebug() <<"总结读取的字节数为"<<data.size();
            file.write(data);
            file.close();
            file_TransCycle_duration.close();
            file_chip_0.close();
            file_chip_0.open(QIODevice::ReadOnly);
            QByteArray data_seperate = file_chip_0.readAll();
            for (int i = 0; i < (data_seperate.size() / 64); i++) {
                for (int j = 0; j < 16; j++) {
                    file_channel[j].write(data_seperate.mid((64 * i + 4 * j),4));
                }
            }
            for (int i = 0; i < 16; i++) {
                file_channel[i].close();
            }
            file_chip_0.close();
            return;
        }
    }
}

void RHSAccess::StopReading()
{
    StopFlag = true;
}

void RHSAccess::DebugFPGA()
{
    UINT32 DebugWire;
    this->UpdateWireOuts();
    this->GetWireOutValue(epAddr_wireOut21, &DebugWire);
}
