#include <QThread>
#include <QDebug>
#include <QString>
#include <QtEndian>
#include <algorithm>
#include <cstdlib>
#include <QRandomGenerator>
#include <QApplication>
#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "rhsaccesssubthread.h"
#include "rhsaccess.h"
#include "mwaveview.h"
#include "csvfilesave.h"
#include "systemstate.h"

bool ControlWindow::isRunning = false;

ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
{

    ui->setupUi(this);

    impedanceRead.state.updateDeviceState(impedanceRead.deviceState);
    //impedanceRead.state.deviceStateinfo(impedanceRead.deviceState);
    impedanceRead.state.deviceReset();

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
    /*
    QAction *jumpToStartAction = new QAction(QIcon(":/images/tostarticon.png"), tr("Jump to Start"), this);
    toolbar->addAction(jumpToStartAction);
    //connect(jumpToStartAction, SIGNAL(triggered()), this, SLOT(jumpToStartSlot()));
    */
    //倒带键
    rewindAction = new QAction(QIcon(":/images/rewindicon.png"), tr("Rewind"), this);
    toolbar->addAction(rewindAction);
    rewindAction->setEnabled(true);
    //connect(rewindAction, SIGNAL(triggered()), this, SLOT(rewindSlot()));


    //开始键
    runAction = new QAction(QIcon(":/images/runicon.png"), tr("Run"), this);
    if(impedanceRead.deviceState == 01){
        connect(runAction, SIGNAL(triggered()), this, SLOT(startGraphAndTimer()));
    }else{
        connect(runAction, SIGNAL(triggered()), &impedanceRead.state.ra, SLOT(convertStart()));
        connect(runAction, SIGNAL(triggered()), this, SLOT(StartSubThread_ReadRHS()));
    }
    toolbar->addAction(runAction);

    //暂停键
    stopAction = new QAction(QIcon(":/images/stopicon.png"), tr("Stop"), this);
    if(impedanceRead.deviceState == 01){
        connect(stopAction, SIGNAL(triggered()), this, SLOT(stopGraphAndTimer()));
    }else{
        connect(stopAction, SIGNAL(triggered()), &impedanceRead.state.ra, SLOT(StopReading()));
        connect(stopAction, SIGNAL(triggered()), this, SLOT(stopRealGraphAndTimer()));
        connect(stopAction, SIGNAL(triggered()), &impedanceRead.state.ra, SLOT(convertStop()));
    }

    stopAction->setEnabled(false);
    toolbar->addAction(stopAction);


    QAction *fastPlaybackAction = new QAction(QIcon(":/images/fficon.png"), tr("Fast Forward"), this);
    toolbar->addAction(fastPlaybackAction);
    //connect(fastPlaybackAction, SIGNAL(triggered()), this, SLOT(fastPlaybackSlot()));

    //阻抗测试
    impedanceAction = new QAction(QIcon(":/images/impedance.jpg"), tr("Impedance"), this);
    if(impedanceRead.deviceState == 01){
        connect(impedanceAction, SIGNAL(triggered()), this, SLOT(startDemoImpedance()));
    }
    if(impedanceRead.deviceState == 02){
        connect(impedanceAction, SIGNAL(triggered()), this, SLOT(startMeasureImpedance()));
    }
    toolbar->addAction(impedanceAction);


    /*
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

    connect(sampleRateComboBox, QOverload<int>::of(&QComboBox::activated), &impedanceRead.state.ra, [this, sampleRateComboBox]() {
        QVariant sampleValue = sampleRateComboBox->currentData();
        if (sampleValue.isValid()) {
            impedanceRead.state.ra.SetSampleRate(sampleValue);
        }
    });
    */

    //各个模块按钮
    QString buttonNames[] = {"数据采集", "无线刺激", "测量工具", "数据处理", "分析报告", "数据共享"};
    for (int i = 0; i < 6; ++i) {
        QPushButton *button = new QPushButton(buttonNames[i], ui->centralwidget);
        button->setObjectName(buttonNames[i]);

        QString buttonStyle = "QPushButton#" + buttonNames[i] + " {"
                              "    background-color: RoyalBlue;"
                              "    border: none;"
                              "    color: white;"
                              "    padding: 60px 120px;"
                              "    text-align: center;"
                              "    text-decoration: none;"
                              "    font-size: 24px;"
                              "    margin: 4px 2px;"
                              "    border-radius: 8px;"
                              "}";

        button->setStyleSheet(buttonStyle);
        int x = 80 + i * 200;
        int y = 20;
        button->setGeometry(x, y, 120, 60);
    }

    //QVBoxLayout *verticalLayout = new QVBoxLayout(ui->centralwidget);
    for (int i = 0; i < 16; ++i) {
        QLabel *label = new QLabel(QString("A-%1").arg(15-i, 3, 10, QChar('0')), ui->centralwidget);
        label->setObjectName(QString("label_%1").arg(i));
        label->setFont(QFont("Arial", 12));
        label->setGeometry(10, 120 + i * 50, 120, 20);
        QPalette palette = label->palette();
        palette.setColor(QPalette::WindowText, QColor(65, 105, 225));
        label->setPalette(palette);
        //verticalLayout->addWidget(label);
    }

    wave = new MWaveView(ui->centralwidget);
    wave->setGeometry(130, 100, 1200, 800);

    // 定时器
    localWaveGetTimer = new QTimer(this);
    connect(localWaveGetTimer, SIGNAL(timeout()), this, SLOT(localWaveTime()));
    localWaveGetTimer->stop();

    realWaveGetTimer = new QTimer(this);
    connect(realWaveGetTimer, SIGNAL(timeout()), this, SLOT(realWaveTime()));
    realWaveGetTimer->stop();

    connect(this, SIGNAL(SIGNAL_StopReadContinuous()), &impedanceRead.state.ra, SLOT(StopReading()));

}


ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::StartSubThread_ReadRHS()
{
    RHSAccessSubThread* SubThread_ReadRHSContinuous = new RHSAccessSubThread(&impedanceRead.state.ra);
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
    static double virtualRealWaveY[16];
    static quint32 realWaveX = 0;
    static QPointF realWavePoint;
    static QPointF virtualRealWavePoint;
    QVector<QPointF> vectorXY;
    realWaveData = impedanceRead.state.ra.waveFormData;
    qDebug() << "realWaveTime::realWaveData"<< realWaveData.mid(0,256);
    for (int i = 0; i < 16; ++i) {

        realWaveY[i] = vc.getAmplifierData(realWaveData.mid(64 * realWaveX + 4 * i,4));
        realWavePoint.setY(realWaveY[i]);
        realWavePoint.setX(realWaveX);
        vectorXY.append(realWavePoint);

        virtualRealWaveY[i] = realWaveY[i] + 20 * i;
        virtualRealWavePoint.setY(virtualRealWaveY[i]);
        virtualRealWavePoint.setX(realWaveX);
        this->realWavePiontList[i].append(virtualRealWavePoint);

        if (this->realWavePiontList[i].size() > 200000)
        {
           this->realWavePiontList[i].removeFirst();
        }

        wave->addSeriesData((WAVE_CH)i,this->realWavePiontList[i]);

    }
    coordinatesArray.append(vectorXY);
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

        localWaveY[i] = vc.getAmplifierData(localWaveData.mid(64 * localWaveX + 4 * i,4));
        localWavePoint.setY(localWaveY[i]);
        localWavePoint.setX(localWaveX);
        vectorXY.append(localWavePoint);

        virtuallocalWaveY[i] = 20 * i + localWaveY[i];
        virtualLocalWavePoint.setY(virtuallocalWaveY[i]);
        virtualLocalWavePoint.setX(localWaveX);
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
    saveRecordData(coordinatesArray);
}

void ControlWindow::startRealGraphAndTimer()
{
    wave->startGraph();
    realWaveGetTimer->start(40);
    runAction->setEnabled(false);
    stopAction->setEnabled(true);
}


void ControlWindow::stopRealGraphAndTimer()
{
    wave->pauseGraph();
    realWaveGetTimer->stop();
    runAction->setEnabled(true);
    stopAction->setEnabled(false);
    saveRecordData(coordinatesArray);
}

void ControlWindow::startDemoImpedance(){
    impedanceRead.runDemoImpedanceMeasurement();
    updateLabels();
}

void ControlWindow::startMeasureImpedance(){
    impedanceRead.state.ra.impedanceConvertStart();
    RHSAccessSubThread* readImpedanceThread = new RHSAccessSubThread(&impedanceRead.state.ra);
    readImpedanceThread->start();
    impedanceRead.measureImpedances();
    updateCurrentLabels(impedanceRead.actualImpedance);
}

void ControlWindow::updateLabels() {
    for(int i = 0; i < 16; ++i){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(i));
        if(label) {
            double randomValue = QRandomGenerator::global()->bounded(49, 53) / 10.0;
            label->setText("I-" + QString::number(i) + " " + QString::number(randomValue) + " MΩ");
        }
    }
}

void ControlWindow::updateCurrentLabels(vector<double>actualImpedance) {
    for(int i = 0; i < 16; ++i){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(i));
        if(label) {
            label->setText("I-" + QString::number(i) + " " + QString::number(actualImpedance[i], 'f', 1) + " MΩ");
        }
    }
}


