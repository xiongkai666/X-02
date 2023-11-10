#include <QThread>
#include <QDebug>
#include <QString>
#include <QtEndian>
#include <algorithm>
#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "rhsaccesssubthread.h"
#include "rhsaccess.h"
#include "mwaveview.h"
#include "csvfilesave.h"
#include "systemstate.h"


ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
{

    ui->setupUi(this);
    state.updateDeviceState(deviceState);
    state.ra.setFPGAbit();
    state.ra.ResetFPGA();
    state.ra.InitializeRHS2116();
    state.ra.DebugFPGA();

    //菜单栏-文件菜单项
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = menuBar->addMenu(tr("文件(&F)"));

    QAction *openFileAction = new QAction(tr("打开\tCTRL+O"), this);
    openFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openWaveFile()));
    fileMenu->addAction(openFileAction);
    /*
    QAction *openimpedanceFileAction = new QAction(tr("打开阻抗文件\tCTRL+I"), this);
    connect(openimpedanceFileAction, SIGNAL(triggered()), this, SLOT(openImpedanceFile()));
    openimpedanceFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    fileMenu->addAction(openimpedanceFileAction);
    */
    QAction *newFileAction = new QAction(tr("新建\tCTRL+N"), this);
    newFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    fileMenu->addAction(newFileAction);

    //菜单栏-文件菜单项-最近打开文件子菜单
    QAction* leastFileAction = new QAction(tr("最近打开文件\tCTRL+L"), this);
    leastFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    fileMenu->addAction(leastFileAction);

    //创建菜单栏-工具菜单项
    QMenu *toolMenu = menuBar->addMenu(tr("工具项(&T)"));

    QAction *spikeScopeAction = new QAction(tr("尖峰示波器\tCTRL+C"), this);
    spikeScopeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    toolMenu->addAction(spikeScopeAction);

    QAction *probeMapAction = new QAction(tr("探测图\tCTRL+M"), this);
    probeMapAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    toolMenu->addAction(probeMapAction);

    //创建菜单栏-语言菜单项
    QMenu *languageMenu = menuBar->addMenu(tr("语言(&L)"));

    QAction *chineseAction = new QAction(tr("中文\tCTRL+C"), this);
    chineseAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    languageMenu->addAction(chineseAction);

    QAction *englishAction = new QAction(tr("English\tCTRL+E"), this);
    englishAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    languageMenu->addAction(englishAction);

    //创建菜单栏-帮助菜单项
    QMenu *helpMenu = menuBar->addMenu(tr("帮助(&H)"));

    QAction *pionwayAction = new QAction(tr("Pionway Website\tCTRL+P"), this);
    pionwayAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    helpMenu->addAction(pionwayAction);

    this->setMenuBar(menuBar);

    // 创建工具栏
    QToolBar *toolbar = addToolBar(tr("工具栏"));

    QAction *jumpToStartAction = new QAction(QIcon(":/images/tostarticon.png"), tr("Jump to Start"), this);
    toolbar->addAction(jumpToStartAction);
    //connect(jumpToStartAction, SIGNAL(triggered()), this, SLOT(jumpToStartSlot()));

    //倒带键
    rewindAction = new QAction(QIcon(":/images/rewindicon.png"), tr("Rewind"), this);
    toolbar->addAction(rewindAction);
    rewindAction->setEnabled(false);
    //connect(rewindAction, SIGNAL(triggered()), this, SLOT(rewindSlot()));

    //开始键
    runAction = new QAction(QIcon(":/images/runicon.png"), tr("Run"), this);
    if(deviceState == 01){
        connect(runAction, SIGNAL(triggered()), this, SLOT(startGraphAndTimer()));
    }
    if(deviceState == 02){
        connect(runAction, SIGNAL(triggered()), &state.ra, SLOT(convertStart()));
        connect(runAction, SIGNAL(triggered()), this, SLOT(StartSubThread_ReadRHS()));
    }
    toolbar->addAction(runAction);

    //暂停键
    stopAction = new QAction(QIcon(":/images/stopicon.png"), tr("Stop"), this);
    if(deviceState == 01){
        connect(stopAction, SIGNAL(triggered()), this, SLOT(stopGraphAndTimer()));
    }
    if(deviceState == 02){
        //connect(stopAction, SIGNAL(triggered()), this, SLOT(StopSubThread_ReadRHS()));
        connect(stopAction, SIGNAL(triggered()), &state.ra, SLOT(StopReading()));
        connect(stopAction, SIGNAL(triggered()), this, SLOT(stopRealGraphAndTimer()));
        connect(stopAction, SIGNAL(triggered()), &state.ra, SLOT(convertStop()));
    }

    stopAction->setEnabled(false);
    toolbar->addAction(stopAction);

    QAction *fastPlaybackAction = new QAction(QIcon(":/images/fficon.png"), tr("Fast Forward"), this);
    toolbar->addAction(fastPlaybackAction);
    //connect(fastPlaybackAction, SIGNAL(triggered()), this, SLOT(fastPlaybackSlot()));

    //设置采样率
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *label = new QLabel("设置采样率", this);
    QComboBox *sampleRateComboBox = new QComboBox(this);
    sampleRateComboBox->addItem("1 kHz", QVariant(1000));
    sampleRateComboBox->addItem("2 kHz", QVariant(2000));
    sampleRateComboBox->addItem("4 kHz", QVariant(4000));
    sampleRateComboBox->addItem("8 kHz", QVariant(8000));
    sampleRateComboBox->addItem("10 kHz", QVariant(10000));
    sampleRateComboBox->addItem("15 kHz", QVariant(15000));
    sampleRateComboBox->addItem("20 kHz", QVariant(20000));
    sampleRateComboBox->addItem("30 kHz", QVariant(30000));

    label->move(20, 200);
    sampleRateComboBox->move(120, 200);

    layout->addWidget(label);
    layout->addWidget(sampleRateComboBox);
    setLayout(layout);

    connect(sampleRateComboBox, QOverload<int>::of(&QComboBox::activated), &state.ra, [this, sampleRateComboBox]() {
        QVariant sampleValue = sampleRateComboBox->currentData();
        if (sampleValue.isValid()) {
            state.ra.SetSampleRate(sampleValue);
        }
    });

    //创建tab页面
    ui->tabWidget->setCurrentIndex(0);
    wave = new MWaveView(ui->waveForm);
    int newWaveX = ui->waveForm->geometry().left() + 65;
    int newWaveY = ui->waveForm->geometry().top() - 20;
    int newWaveWidth = ui->waveForm->width() + 400;
    int newWaveHeight = ui->waveForm->height() + 400;
    wave->setGeometry(newWaveX, newWaveY, newWaveWidth, newWaveHeight);
    //qDebug() << "label_2.width()" << label_2.width();

    impedance = new MWaveView(ui->impedanceForm);
    int newImpedanceX = ui->impedanceForm->geometry().left() + 160;
    int newImpedanceY = ui->impedanceForm->geometry().top() - 20;
    int newImpedanceWidth = ui->impedanceForm->width() + 400;
    int newImpedanceHeight = ui->impedanceForm->height() + 400;
    impedance->setGeometry(newImpedanceX, newImpedanceY, newImpedanceWidth, newImpedanceHeight);

    // 定时器
    localWaveGetTimer = new QTimer(this);
    connect(localWaveGetTimer, SIGNAL(timeout()), this, SLOT(localWaveTime()));
    localWaveGetTimer->stop();

    realWaveGetTimer = new QTimer(this);
    connect(realWaveGetTimer, SIGNAL(timeout()), this, SLOT(realWaveTime()));
    realWaveGetTimer->stop();

    realImpedanceGetTimer = new QTimer(this);
    connect(realImpedanceGetTimer, SIGNAL(timeout()), this, SLOT(realImpedanceTime()));
    realImpedanceGetTimer->stop();

    connect(this, SIGNAL(SIGNAL_StopReadContinuous()), &state.ra, SLOT(StopReading()));

}


ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::StartSubThread_ReadRHS()
{
    RHSAccessSubThread* SubThread_ReadRHSContinuous = new RHSAccessSubThread(&state.ra);
    SubThread_ReadRHSContinuous->start();
    realVoltageWaveform();
}

void ControlWindow::StopSubThread_ReadRHS()
{
    emit SIGNAL_StopReadContinuous();
}

void ControlWindow::realVoltageWaveform(){
    startRealGraphAndTimer();
}
void ControlWindow::realWaveTime(){
    static double realWaveY[16];
    static quint32 realWaveX = 0;
    static QPointF realWavePoint;
    realWaveData = state.ra.waveFormData.mid(256);
    for (int i = 0; i < 16; ++i) {

        QByteArray qHighRealWaveData = realWaveData.mid(64*realWaveX+4*i+0,1);
        QByteArray qLowRealWaveData = realWaveData.mid(64*realWaveX+4*i+1,1);

        int highRealWaveData = qHighRealWaveData.toHex().toInt(nullptr, 16);
        int lowRealWaveData = qLowRealWaveData.toHex().toInt(nullptr, 16);

        int totalRealWaveData;
        totalRealWaveData= highRealWaveData * 256 + lowRealWaveData;

        realWaveY[i] = 0.195 * (totalRealWaveData - 32768)/1000.0;

        realWaveY[i] += 20 * i;

        realWavePoint.setY(realWaveY[i]);
        realWavePoint.setX(realWaveX);

        this->realWavePiontList[i].append(realWavePoint);

        if (this->realWavePiontList[i].size() > 200000)
        {
           this->realWavePiontList[i].removeFirst();
        }

        wave->addSeriesData((WAVE_CH)i,this->realWavePiontList[i]);

    }
    realWaveX++;
}

void ControlWindow::openWaveFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "文本文件 (*.bin);;所有文件 (*)");

    if (!filePath.isEmpty()) {
        QFile waveFile(filePath);
        if (waveFile.open(QIODevice::ReadOnly | QIODevice::Truncate)) {
            localFileWaveData = waveFile.readAll();
            waveFile.close();
        } else {
            qDebug() << "无法打开文件：" << waveFile.errorString();
        }
    } else {
        qDebug() << "未选择任何文件";
    }
    localVoltageWaveform();
}

void ControlWindow::localVoltageWaveform(){

    localWaveData = localFileWaveData.mid(256);
}

void ControlWindow::localWaveTime(){
    static double localWaveY[16];
    static double virtuallocalWaveY[16];
    static quint32 localWaveX = 0;
    static QPointF localWavePoint;
    static QPointF virtualLocalWavePoint;
    QVector<QPointF> vectorXY;
    for (int i = 0; i < 16; ++i) {

        QByteArray qHighLocalWaveData = localWaveData.mid(64*(localWaveX-1) + 4 * i + 0,1);
        QByteArray qLowLocalWaveData = localWaveData.mid(64*(localWaveX-1)+ 4 * i + 1,1);

        int highLocalWaveData = qHighLocalWaveData.toHex().toInt(nullptr, 16);
        int lowLocalWaveData = qLowLocalWaveData.toHex().toInt(nullptr, 16);

        int totalLocalWaveData;
        totalLocalWaveData= highLocalWaveData * 256 + lowLocalWaveData;

        localWaveY[i] = 0.195 * (totalLocalWaveData - 32768)/1000.0;

        virtuallocalWaveY[i] = 20 * i + localWaveY[i];

        localWavePoint.setY(localWaveY[i]);
        localWavePoint.setX(localWaveX);

        virtualLocalWavePoint.setY(virtuallocalWaveY[i]);
        virtualLocalWavePoint.setX(localWaveX);

        vectorXY.append(localWavePoint);

        this->localWavePiontList[i].append(virtualLocalWavePoint);

        if (this->localWavePiontList[i].size() > 200000)
        {
           this->localWavePiontList[i].removeFirst();
        }

        wave->addSeriesData((WAVE_CH)i,this->localWavePiontList[i]);

    }
    coordinatesArray.append(vectorXY);
    localWaveX++;
}

void ControlWindow::startGraphAndTimer()
{
    wave->startGraph();
    localWaveGetTimer->start(10);
    runAction->setEnabled(false);
    stopAction->setEnabled(true);
    rewindAction->setEnabled(true);

}
void ControlWindow::stopGraphAndTimer()
{
    wave->pauseGraph();
    localWaveGetTimer->stop();
    runAction->setEnabled(true);
    stopAction->setEnabled(false);
    saveDataToCSV(coordinatesArray, "C:/Users/xiongkai/Desktop/X-02/recordXY.csv");
}

void ControlWindow::startRealGraphAndTimer()
{
    wave->startGraph();
    realWaveGetTimer->start(20);
    runAction->setEnabled(false);
    stopAction->setEnabled(true);
}


void ControlWindow::stopRealGraphAndTimer()
{
    wave->pauseGraph();
    realWaveGetTimer->stop();
    runAction->setEnabled(true);
    stopAction->setEnabled(false);
}

void ControlWindow::on_realImpedanceStart_clicked()
{
    state.ra.impedanceConvertStart();
    RHSAccessSubThread* readImpedanceThread = new RHSAccessSubThread(&state.ra);
    readImpedanceThread->start();
    emit realImpedanceWaveform();
}

void ControlWindow::realImpedanceWaveform(){

    realImpedanceGetTimer->start(50);
    impedance->startGraph();
}

void ControlWindow::realImpedanceTime(){
    static double realImpedanceY[16];
    static quint32 realImpedanceX = 0;
    static double maxVoltage[16] = {0.0};

    for (int i = 0; i < 16; ++i) {
        realImpedanceData = state.ra.waveFormData.mid(256);
        QByteArray qHighRealImpedanceData = realImpedanceData.mid(64*realImpedanceX+4*i+0,1);
        QByteArray qLowRealImpedanceData = realImpedanceData.mid(64*realImpedanceX+4*i+1,1);

        int highRealImpedanceData = qHighRealImpedanceData.toHex().toInt(nullptr, 16);
        int lowRealImpedanceData = qLowRealImpedanceData.toHex().toInt(nullptr, 16);

        int totalRealImpedanceData;
        totalRealImpedanceData = highRealImpedanceData * 256 + lowRealImpedanceData;

        realImpedanceY[i] = 0.195 * (totalRealImpedanceData - 32768)/1000.0;
        //realImpedanceY[i] = (realImpedanceY[i]>0?realImpedanceY[i]:-realImpedanceY[i]);
        qDebug() << "realImpedanceY[i]" << realImpedanceY[i];
        maxVoltage[i] = std::max(maxVoltage[i],realImpedanceY[i]);

        QLabel *label = findChild<QLabel*>("label_" + QString::number(i+16));
        if(label) {
            label->setText("I-" + QString::number(i) +"\t"+ QString::number(maxVoltage[i], 'f', 1) + "MΩ");
        }
    }
    realImpedanceX++;
}

void ControlWindow::on_realImpedanceStop_clicked()
{
    state.ra.StopReading();
    realImpedanceGetTimer->stop();
    state.ra.impedanceConvertStop();
}
void ControlWindow::on_widthSlider_sliderMoved(int position)
{

    static int last_position = 0;

    if (position > last_position) {
        wave->ZoomY();
    } else if (position < last_position) {
        wave->ZoomOutY();
    }
    last_position = position;

}

