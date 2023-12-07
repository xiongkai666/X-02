#include <QThread>
#include <QDebug>
#include <QString>
#include <QtEndian>
#include <algorithm>
#include <cstdlib>
#include <QRandomGenerator>
#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "rhsaccesssubthread.h"
#include "rhsaccess.h"
#include "mwaveview.h"
#include "csvfilesave.h"
#include "systemstate.h"
#include "impedancereader.h"


ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
{

    ui->setupUi(this);
    state.updateDeviceState(deviceState);
    state.deviceStateinfo(deviceState);
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
    static double virtualRealWaveY[16];
    static quint32 realWaveX = 0;
    static QPointF realWavePoint;
    static QPointF virtualRealWavePoint;
    QVector<QPointF> vectorXY;
    realWaveData = state.ra.waveFormData;
    for (int i = 0; i < 16; ++i) {

        realWaveY[i] = getAmplifierData(realWaveData.mid(64 * realWaveX + 4 * i,4));
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
/*
void ControlWindow::localWaveTime(){
    static double localWaveY[16];
    static double virtuallocalWaveY[16];
    static quint32 localWaveX = 0;
    static QPointF localWavePoint;
    static QPointF virtualLocalWavePoint;
    QVector<QPointF> vectorXY;
    for (int i = 0; i < 16; ++i) {

        localWaveY[i] = getAmplifierData(localWaveData.mid(64 * localWaveX + 4 * i,4));
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
*/
void ControlWindow::localWaveTime(){
    static double localWaveY[16];
    static double virtuallocalWaveY[16];
    static quint32 localWaveX = 0;
    static QPointF localWavePoint;
    static QPointF virtualLocalWavePoint;
    QVector<QPointF> vectorXY;
    if(localWaveX <= 60 * 20){
        for (int i = 0; i < 16; ++i) {
            int numPeriod = 100;
            int period = 20;
            int headIndex = 4 * i + 4;
            int perChannelIndex = i * numPeriod * period * 4 + 20 * period * 4;
            localWaveY[i] = getAmplifierData(localWaveData.mid(headIndex + perChannelIndex + 4 * localWaveX , 4));

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
    }else{
        emit stopGraphAndTimer();
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

void ControlWindow::on_realImpedanceStart_clicked()
{
    if(deviceState == 01){
        impedanceread.runDemoImpedanceMeasurement();
        updateLabels();
    }
    if(deviceState == 02){

        state.ra.impedanceConvertStart();
        RHSAccessSubThread* readImpedanceThread = new RHSAccessSubThread(&state.ra);
        readImpedanceThread->start();
        runImpedanceProcess();
    }
}

void ControlWindow::runImpedanceProcess(){

    int maxProgress = 100;
    QProgressDialog progress(QObject::tr("正在测量电极阻抗"), QString(), 0, maxProgress);
    progress.setWindowTitle(QObject::tr("提示"));
    progress.setMinimumSize(240, 100);
    progress.setMinimumDuration(0);
    progress.setModal(true);
    progress.setValue(0);
    for (int i = 1; i < 6; ++i) {
        progress.setValue(10*i);
        QThread::msleep(1000);
    }

    int index = 0;
    for(int i = 0; i < 256; i += 4){
        QByteArray dataChunk = state.ra.impedanceFileData.mid(i,4);
        if((static_cast<unsigned char>(dataChunk.at(0)) == 0xff)
        &&(static_cast<unsigned char>(dataChunk.at(1)) == 0xff)
        &&(static_cast<unsigned char>(dataChunk.at(2)) == 0xc0)
        &&(static_cast<unsigned char>(dataChunk.at(3)) == 0x41)){
            break;
        }else{
            index ++;
        }
    }

    QByteArray impedanceData = state.ra.impedanceFileData.mid(4*index);

    vector<vector<QByteArray>> channelImpedanceStream(3,vector<QByteArray>(16));

    double actualImpedanceFreq = 1000.0;
    double sampleRate = 20000.0;
    int period = sampleRate / actualImpedanceFreq;
    double relativeFreq = 1 / period;
    int numPeriod = 100;

    for(int capRange = 0; capRange < 3; ++capRange){
        int capRangeIndex = capRange * 16 * numPeriod * period * 4 + capRange * 64;
        for(int channel = 0 ; channel < 16; ++channel){
            int headIndex = 4 * channel + 4;
            int perChannelIndex = channel * numPeriod * period * 4 + 20 * period * 4;
            channelImpedanceStream[capRange][channel] = impedanceData.mid(capRangeIndex + perChannelIndex + headIndex, 60 * period * 4);
        }
    }

    vector<vector<ComplexPolar>>measuredImpedance(3,vector<ComplexPolar>(16));
    for(int capRange = 0; capRange < 3; ++capRange){
        for(int channel = 0; channel < 16; ++channel){
            progress.setValue(60 + 2 * channel);
            measuredImpedance[capRange][channel] = measureComplexAmplitude(channelImpedanceStream[capRange][channel],20000.0,1000.0);
        }
    }

    const double DacVoltageAmplitude = 128.0 * (1.225 / 256.0); // 电压幅度
    double parasiticCapacitance = 15.0e-12;//并联电容

    double actualUpperBandwidth = 20000.0;
    double saturationVoltage = approximateSaturationVoltage(actualImpedanceFreq,actualUpperBandwidth);

    vector <ComplexPolar> perChannelImpedance(16);
    vector<double>cSeries = {0.1e-12,1e-12,1e-11};

    for(int channel = 0; channel < 16; ++ channel){        
        int bestAmplitudeIndex;
        if (measuredImpedance[2][channel].magnitude < saturationVoltage) {
            bestAmplitudeIndex = 2;
        } else if (measuredImpedance[1][channel].magnitude < saturationVoltage) {
            bestAmplitudeIndex = 1;
        } else {
            bestAmplitudeIndex = 0;
        }

        double capRatio = measuredImpedance[1][channel].magnitude / measuredImpedance[2][channel].magnitude;
        if (capRatio > 0.2) {
            if (bestAmplitudeIndex == 2) {
                bestAmplitudeIndex = 1;
            }
        }

        double current = TwoPi * actualImpedanceFreq * DacVoltageAmplitude * cSeries[bestAmplitudeIndex];

        ComplexPolar impedance;

        impedance.magnitude = 1.0e-9 * (measuredImpedance[bestAmplitudeIndex][channel].magnitude / current) *
                (18.0 * relativeFreq * relativeFreq + 1.0);
        impedance.phase = measuredImpedance[bestAmplitudeIndex][channel].phase + (360.0 * (3.0 / period));

        impedance = factorOutParallelCapacitance(impedance, actualImpedanceFreq, parasiticCapacitance);
        impedance.magnitude = 1.1 * impedance.magnitude;//RHS芯片被低估

        perChannelImpedance[channel] = impedance;
    }

    ImpedanceReader impedanceReader;
    impedanceReader.saveImpedanceData(perChannelImpedance);

    vector <double>actualImpedance(16);
    for(int channel = 0; channel < 16; ++ channel){
        actualImpedance[channel] = perChannelImpedance[channel].magnitude;
    }
    updateCurrentLabels(actualImpedance);
    progress.setValue(maxProgress);
}

double ControlWindow::approximateSaturationVoltage(double actualZFreq, double highCutoff)
{
    if (actualZFreq < 0.2 * highCutoff) {
        return 5000.0;
    } else {
        return 5000.0 * sqrt(1.0 / (1.0 + pow(3.3333 * actualZFreq / highCutoff, 4.0)));
    }
}

ComplexPolar ControlWindow::factorOutParallelCapacitance(ComplexPolar impedance, double frequency,double parasiticCapacitance)
{
    // First, convert from polar coordinates to rectangular coordinates.
    double measuredR = impedance.magnitude * cos(DegreesToRadians * impedance.phase);
    double measuredX = impedance.magnitude * sin(DegreesToRadians * impedance.phase);

    double capTerm = TwoPi * frequency * parasiticCapacitance;
    double xTerm = capTerm * (measuredR * measuredR + measuredX * measuredX);
    double denominator = capTerm * xTerm + 2.0 * capTerm * measuredX + 1.0;
    double trueR = measuredR / denominator;
    double trueX = (measuredX + xTerm) / denominator;

    // Now, convert from rectangular coordinates back to polar coordinates.
    ComplexPolar result;
    result.magnitude = sqrt(trueR * trueR + trueX * trueX);
    result.phase = RadiansToDegrees * atan2(trueX, trueR);
    return result;
}

ComplexPolar ControlWindow::measureComplexAmplitude(QByteArray & channelStream, double sampleRate, double frequency)
{
    vector<double> waveform(60 * 20);
    int index = 0;
    for(int i = 0; i < 60 * 20 * 4; i += 4){
        waveform[index++] = getAmplifierData(channelStream.mid(i,4));
    }

    double notchFreq = 50.0;
    double NotchBandwidth = 10.0;

    applyNotchFilter(waveform, notchFreq, NotchBandwidth, sampleRate);

    int startIndex = 40 * 20;
    int endIndex = startIndex + 20 - 1;
    return amplitudeOfFreqComponent(waveform, startIndex, endIndex, sampleRate, frequency);
}

void ControlWindow::applyNotchFilter(vector<double> & waveform, double fNotch, double bandwidth, double sampleRate) const
{
    double d = exp(-1.0 * Pi * bandwidth / sampleRate);
    double b = (1.0 + d * d) * cos(TwoPi * fNotch / sampleRate);
    double b0 = (1.0 + d * d) / 2.0;
    double b1 = -b;
    double b2 = b0;
    double a1 = b1;
    double a2 = d * d;
    int length = (int) waveform.size();

    double prevPrevIn = waveform[0];
    double prevIn = waveform[1];
    for (int t = 2; t < length; ++t) {
        double in = waveform[t];
        waveform[t] = b0 * in + b1 * prevIn + b2 * prevPrevIn - a1 * waveform[t - 1] - a2 * waveform[t - 2];  // Direct Form 1 implementation
        prevPrevIn = prevIn;
        prevIn = in;
    }
}

//使用傅里叶变换
ComplexPolar ControlWindow::amplitudeOfFreqComponent(const vector<double> &waveform, int startIndex, int endIndex,
                                                       double sampleRate, double frequency)
{
    const double K = TwoPi * frequency / sampleRate;
    double meanI = 0.0;
    double meanQ = 0.0;
    for (int t = startIndex; t <= endIndex; ++t) {
        meanI += waveform[t] * cos(K * t);
        meanQ += waveform[t] * -1.0 * sin(K * t);
    }
    double length = (double)(endIndex - startIndex + 1);
    meanI /= length;
    meanQ /= length;

    double realComponent = 2.0 * meanI;
    double imagComponent = 2.0 * meanQ;

    ComplexPolar result;
    result.magnitude = sqrt(realComponent * realComponent + imagComponent * imagComponent);
    result.phase = RadiansToDegrees * atan2(imagComponent, realComponent);
    return result;
}

double ControlWindow::getAmplifierData(QByteArray amplifierData){

        QByteArray qHighAmplifierData = amplifierData.mid(0,1);
        QByteArray qLowAmplifierData = amplifierData.mid(1,1);

        int highAmplifierData = qHighAmplifierData.toHex().toInt(nullptr, 16);
        int lowAmplifierData = qLowAmplifierData.toHex().toInt(nullptr, 16);
        int realAmplifierData;
        realAmplifierData = highAmplifierData * 256 + lowAmplifierData;

        double realVoltage = 0.195 * (realAmplifierData - 32768) / 1000;

        return realVoltage;
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

void ControlWindow::updateLabels() {
    for(int channel = 0; channel < 16; ++channel){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(channel+16));
        if(label) {
            double randomValue = QRandomGenerator::global()->bounded(49, 53) / 10.0;
            label->setText("I-" + QString::number(channel) + "\t" + QString::number(randomValue) + " MΩ");
        }
    }
}

void ControlWindow::updateCurrentLabels(vector<double>actualImpedance) {
    for(int channel = 0; channel < 16; ++channel){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(channel+16));
        if(label) {
            if(actualImpedance[channel] < 1.0){
                label->setText("I-" + QString::number(channel) + "\t" + QString::number(1000.0 * actualImpedance[channel], 'f', 0) + " kΩ");
            }else{
                label->setText("I-" + QString::number(channel) + "\t" + QString::number(actualImpedance[channel], 'f', 2) + " MΩ");
            }
        }
    }
}


