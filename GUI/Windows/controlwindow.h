#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QThread>
#include <QProcess>
#include "rhsaccess.h"
#include "mwaveview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWindow; }
QT_END_NAMESPACE

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

signals:

    void SIGNAL_CONVERTStart_clicked();

    void SIGNAL_CONVERTStop_clicked();

    void SIGNAL_StopReadContinuous();

    void SIGNAL_DebugFPGAButton_clicked();

public slots:

    void StartSubThread_ReadRHS();

    void StopSubThread_ReadRHS();

    void realWaveTime();

    void localWaveTime();

    void localImpedanceTime();

    void realImpedanceTime();

    void localVoltageWaveform();

    void realVoltageWaveform();

    void realImpedanceWaveform();

    void localImpedanceWaveform();

private slots:

    void on_checkBox_0_stateChanged(int arg1);

    void on_checkBox_1_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_7_stateChanged(int arg1);

    void on_checkBox_8_stateChanged(int arg1);

    void on_checkBox_9_stateChanged(int arg1);

    void on_checkBox_10_stateChanged(int arg1);

    void on_checkBox_11_stateChanged(int arg1);

    void on_checkBox_12_stateChanged(int arg1);

    void on_checkBox_13_stateChanged(int arg1);

    void on_checkBox_14_stateChanged(int arg1);

    void on_checkBox_15_stateChanged(int arg1);

    void openWaveFile();

    void openImpedanceFile();

    void startGraphAndTimer();

    void stopGraphAndTimer();

    void startRealGraphAndTimer();

    void stopRealGraphAndTimer();

    void on_localimpedance_start_clicked();

    void on_realimpedance_start_clicked();

    void on_realimpedance_pause_clicked();

    void on_localimpedance_pause_clicked();

    void on_checkBox_16_stateChanged(int arg1);

    void on_checkBox_17_stateChanged(int arg1);

    void on_checkBox_18_stateChanged(int arg1);

    void on_checkBox_19_stateChanged(int arg1);

    void on_checkBox_20_stateChanged(int arg1);

    void on_checkBox_21_stateChanged(int arg1);

    void on_checkBox_22_stateChanged(int arg1);

    void on_checkBox_23_stateChanged(int arg1);

    void on_checkBox_24_stateChanged(int arg1);

    void on_checkBox_25_stateChanged(int arg1);

    void on_checkBox_26_stateChanged(int arg1);

    void on_checkBox_27_stateChanged(int arg1);

    void on_checkBox_28_stateChanged(int arg1);

    void on_checkBox_29_stateChanged(int arg1);

    void on_checkBox_30_stateChanged(int arg1);

    void on_checkBox_31_stateChanged(int arg1);

    void on_widthSlider_sliderMoved(int position);

private:
    Ui::ControlWindow *ui;
    QString RHSCMD_R1;QString RHSCMD_R2;QString RHSCMD_R3;QString RHSCMD_R4;
    QString RHSCMD_D1;QString RHSCMD_D2;QString RHSCMD_D3;QString RHSCMD_D4;
    QString RHSCMD_WR1;QString RHSCMD_WR2;QString RHSCMD_WR3;QString RHSCMD_WR4;
    QString RHSCMD_UMDH1;QString RHSCMD_UMDH2;QString RHSCMD_UMDH3;QString RHSCMD_UMDH4;
    QString RHSCMD_WRUMDH1;QString RHSCMD_WRUMDH2;QString RHSCMD_WRUMDH3;QString RHSCMD_WRUMDH4;
    QString M;QString D;
    RHSAccess ra;
    QTimer*  localWaveGetTimer;
    QTimer*  realWaveGetTimer;
    QTimer*  localImpedanceGetTimer;
    QTimer*  realImpedanceGetTimer;
    MWaveView *wave;
    MWaveView *impedance;

    QVector<QVector<QPointF>> coordinatesArray;
    QList<QPointF> localWavePiontList[16];
    QList<QPointF> realWavePiontList[16];
    QList<QPointF> localImpedancePiontList[16];
    QList<QPointF> realImpedancePiontList[16];
    QChartView *wave_charts[16];
    double maxVoltage[16];
    double electrodeImpedance[16];

    int deviceState = 0;

    QByteArray localFileWaveData;
    QByteArray localWaveData;
    QByteArray realWaveData;
    QByteArray localFileImpedanceData;
    QByteArray localImpedanceData;
    QByteArray realImpedanceData;

    QAction *runAction;
    QAction *stopAction;
    QAction *rewindAction;

};
#endif // CONTROLWINDOW_H

