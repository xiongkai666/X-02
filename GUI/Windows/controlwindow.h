#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QThread>
#include <QProcess>
#include "rhsaccess.h"
#include "mwaveview.h"
#include "systemstate.h"
#include "PionwayDLL.h"

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

    void realImpedanceTime();

    void localVoltageWaveform();

    void realVoltageWaveform();

    void realImpedanceWaveform();

private slots:

    void openWaveFile();

    void startGraphAndTimer();

    void stopGraphAndTimer();

    void startRealGraphAndTimer();

    void stopRealGraphAndTimer();

    void on_widthSlider_sliderMoved(int position);

    void on_realImpedanceStart_clicked();

    void on_realImpedanceStop_clicked();

private:
    Ui::ControlWindow *ui;
    QString RHSCMD_R1;QString RHSCMD_R2;QString RHSCMD_R3;QString RHSCMD_R4;
    QString RHSCMD_D1;QString RHSCMD_D2;QString RHSCMD_D3;QString RHSCMD_D4;
    QString RHSCMD_WR1;QString RHSCMD_WR2;QString RHSCMD_WR3;QString RHSCMD_WR4;
    QString RHSCMD_UMDH1;QString RHSCMD_UMDH2;QString RHSCMD_UMDH3;QString RHSCMD_UMDH4;
    QString RHSCMD_WRUMDH1;QString RHSCMD_WRUMDH2;QString RHSCMD_WRUMDH3;QString RHSCMD_WRUMDH4;
    QString M;QString D;

    SystemState state;

    QTimer*  localWaveGetTimer;
    QTimer*  realWaveGetTimer;
    QTimer*  realImpedanceGetTimer;
    MWaveView *wave;
    MWaveView *impedance;

    QVector<QVector<QPointF>> coordinatesArray;
    QList<QPointF> localWavePiontList[16];
    QList<QPointF> realWavePiontList[16];
    QList<QPointF> realImpedancePiontList[16];
    QChartView *wave_charts[16];
    double electrodeImpedance[16];

    int deviceState = 0;

    QByteArray localFileWaveData;
    QByteArray localWaveData;
    QByteArray realWaveData;
    QByteArray realImpedanceData;

    QAction *runAction;
    QAction *stopAction;
    QAction *rewindAction;

};
#endif // CONTROLWINDOW_H

