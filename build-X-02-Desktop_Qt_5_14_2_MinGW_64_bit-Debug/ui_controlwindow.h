/********************************************************************************
** Form generated from reading UI file 'controlwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLWINDOW_H
#define UI_CONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlWindow
{
public:
    QAction *action_N;
    QAction *actiondakia;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *waveForm;
    QLabel *label_15;
    QLabel *label_14;
    QLabel *label_13;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_09;
    QLabel *label_08;
    QLabel *label_07;
    QLabel *label_06;
    QLabel *label_05;
    QLabel *label_04;
    QLabel *label_03;
    QLabel *label_02;
    QLabel *label_01;
    QLabel *label_00;
    QWidget *impedanceForm;
    QPushButton *realimpedance;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QPushButton *realImpedanceStart;
    QSlider *widthSlider;
    QLabel *label;
    QPushButton *realImpedanceStop;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ControlWindow)
    {
        if (ControlWindow->objectName().isEmpty())
            ControlWindow->setObjectName(QString::fromUtf8("ControlWindow"));
        ControlWindow->resize(1333, 996);
        ControlWindow->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,1)"));
        action_N = new QAction(ControlWindow);
        action_N->setObjectName(QString::fromUtf8("action_N"));
        actiondakia = new QAction(ControlWindow);
        actiondakia->setObjectName(QString::fromUtf8("actiondakia"));
        centralwidget = new QWidget(ControlWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(240, 32, 1090, 881));
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        waveForm = new QWidget();
        waveForm->setObjectName(QString::fromUtf8("waveForm"));
        label_15 = new QLabel(waveForm);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(0, 30, 66, 18));
        label_14 = new QLabel(waveForm);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(0, 80, 81, 18));
        label_13 = new QLabel(waveForm);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(0, 130, 81, 18));
        label_12 = new QLabel(waveForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 180, 81, 18));
        label_11 = new QLabel(waveForm);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 230, 81, 18));
        label_10 = new QLabel(waveForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 280, 81, 18));
        label_09 = new QLabel(waveForm);
        label_09->setObjectName(QString::fromUtf8("label_09"));
        label_09->setGeometry(QRect(0, 330, 81, 18));
        label_08 = new QLabel(waveForm);
        label_08->setObjectName(QString::fromUtf8("label_08"));
        label_08->setGeometry(QRect(0, 380, 81, 18));
        label_07 = new QLabel(waveForm);
        label_07->setObjectName(QString::fromUtf8("label_07"));
        label_07->setGeometry(QRect(0, 430, 81, 18));
        label_06 = new QLabel(waveForm);
        label_06->setObjectName(QString::fromUtf8("label_06"));
        label_06->setGeometry(QRect(0, 480, 81, 18));
        label_05 = new QLabel(waveForm);
        label_05->setObjectName(QString::fromUtf8("label_05"));
        label_05->setGeometry(QRect(0, 530, 81, 18));
        label_04 = new QLabel(waveForm);
        label_04->setObjectName(QString::fromUtf8("label_04"));
        label_04->setGeometry(QRect(0, 580, 81, 18));
        label_03 = new QLabel(waveForm);
        label_03->setObjectName(QString::fromUtf8("label_03"));
        label_03->setGeometry(QRect(0, 630, 81, 18));
        label_02 = new QLabel(waveForm);
        label_02->setObjectName(QString::fromUtf8("label_02"));
        label_02->setGeometry(QRect(0, 680, 81, 18));
        label_01 = new QLabel(waveForm);
        label_01->setObjectName(QString::fromUtf8("label_01"));
        label_01->setGeometry(QRect(0, 730, 81, 18));
        label_00 = new QLabel(waveForm);
        label_00->setObjectName(QString::fromUtf8("label_00"));
        label_00->setGeometry(QRect(0, 780, 81, 18));
        tabWidget->addTab(waveForm, QString());
        impedanceForm = new QWidget();
        impedanceForm->setObjectName(QString::fromUtf8("impedanceForm"));
        realimpedance = new QPushButton(impedanceForm);
        realimpedance->setObjectName(QString::fromUtf8("realimpedance"));
        realimpedance->setGeometry(QRect(30, 920, 119, 34));
        label_16 = new QLabel(impedanceForm);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(0, 780, 160, 18));
        label_17 = new QLabel(impedanceForm);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(0, 730, 160, 18));
        label_18 = new QLabel(impedanceForm);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(0, 680, 160, 18));
        label_19 = new QLabel(impedanceForm);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(0, 630, 160, 18));
        label_20 = new QLabel(impedanceForm);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(0, 580, 160, 18));
        label_21 = new QLabel(impedanceForm);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(0, 530, 160, 18));
        label_22 = new QLabel(impedanceForm);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(0, 480, 160, 18));
        label_23 = new QLabel(impedanceForm);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(0, 430, 160, 18));
        label_24 = new QLabel(impedanceForm);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(0, 380, 160, 18));
        label_25 = new QLabel(impedanceForm);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(0, 330, 160, 18));
        label_26 = new QLabel(impedanceForm);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(0, 280, 160, 18));
        label_27 = new QLabel(impedanceForm);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(0, 230, 160, 18));
        label_28 = new QLabel(impedanceForm);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(0, 180, 160, 18));
        label_29 = new QLabel(impedanceForm);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(0, 130, 160, 18));
        label_30 = new QLabel(impedanceForm);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(0, 80, 160, 18));
        label_31 = new QLabel(impedanceForm);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(0, 30, 160, 18));
        tabWidget->addTab(impedanceForm, QString());
        tabWidget->setTabText(tabWidget->indexOf(impedanceForm), QString::fromUtf8("\346\265\213\351\207\217\351\230\273\346\212\227"));
        realImpedanceStart = new QPushButton(centralwidget);
        realImpedanceStart->setObjectName(QString::fromUtf8("realImpedanceStart"));
        realImpedanceStart->setGeometry(QRect(0, 30, 112, 34));
        widthSlider = new QSlider(centralwidget);
        widthSlider->setObjectName(QString::fromUtf8("widthSlider"));
        widthSlider->setGeometry(QRect(20, 690, 22, 160));
        widthSlider->setOrientation(Qt::Vertical);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 860, 71, 20));
        realImpedanceStop = new QPushButton(centralwidget);
        realImpedanceStop->setObjectName(QString::fromUtf8("realImpedanceStop"));
        realImpedanceStop->setGeometry(QRect(120, 30, 112, 34));
        ControlWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ControlWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ControlWindow->setStatusBar(statusbar);

        retranslateUi(ControlWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ControlWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ControlWindow)
    {
        ControlWindow->setWindowTitle(QCoreApplication::translate("ControlWindow", "ControlWindow", nullptr));
        action_N->setText(QCoreApplication::translate("ControlWindow", "\346\226\260\345\273\272(&N)", nullptr));
        actiondakia->setText(QCoreApplication::translate("ControlWindow", "dakia", nullptr));
        label_15->setText(QCoreApplication::translate("ControlWindow", "V-15 mV", nullptr));
        label_14->setText(QCoreApplication::translate("ControlWindow", "V-14 mV", nullptr));
        label_13->setText(QCoreApplication::translate("ControlWindow", "V-13 mV", nullptr));
        label_12->setText(QCoreApplication::translate("ControlWindow", "V-12 mV", nullptr));
        label_11->setText(QCoreApplication::translate("ControlWindow", "V-11 mV", nullptr));
        label_10->setText(QCoreApplication::translate("ControlWindow", "V-10 mV", nullptr));
        label_09->setText(QCoreApplication::translate("ControlWindow", "V-09 mV", nullptr));
        label_08->setText(QCoreApplication::translate("ControlWindow", "V-08 mV", nullptr));
        label_07->setText(QCoreApplication::translate("ControlWindow", "V-07 mV", nullptr));
        label_06->setText(QCoreApplication::translate("ControlWindow", "V-06 mV", nullptr));
        label_05->setText(QCoreApplication::translate("ControlWindow", "V-05 mV", nullptr));
        label_04->setText(QCoreApplication::translate("ControlWindow", "V-04 mV", nullptr));
        label_03->setText(QCoreApplication::translate("ControlWindow", "V-03 mV", nullptr));
        label_02->setText(QCoreApplication::translate("ControlWindow", "V-02 mV", nullptr));
        label_01->setText(QCoreApplication::translate("ControlWindow", "V-01 mV", nullptr));
        label_00->setText(QCoreApplication::translate("ControlWindow", "V-00 mV", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(waveForm), QCoreApplication::translate("ControlWindow", "\347\224\265\345\216\213\346\263\242\345\275\242", nullptr));
        realimpedance->setText(QCoreApplication::translate("ControlWindow", "\346\265\213\351\207\217\351\230\273\346\212\227\345\274\200\345\247\213", nullptr));
        label_16->setText(QCoreApplication::translate("ControlWindow", "I-00 M\316\251", nullptr));
        label_17->setText(QCoreApplication::translate("ControlWindow", "I-01 M\316\251", nullptr));
        label_18->setText(QCoreApplication::translate("ControlWindow", "I-02 M\316\251", nullptr));
        label_19->setText(QCoreApplication::translate("ControlWindow", "I-03 M\316\251", nullptr));
        label_20->setText(QCoreApplication::translate("ControlWindow", "I-04 M\316\251", nullptr));
        label_21->setText(QCoreApplication::translate("ControlWindow", "I-05 M\316\251", nullptr));
        label_22->setText(QCoreApplication::translate("ControlWindow", "I-06 M\316\251", nullptr));
        label_23->setText(QCoreApplication::translate("ControlWindow", "I-07 M\316\251", nullptr));
        label_24->setText(QCoreApplication::translate("ControlWindow", "I-08 M\316\251", nullptr));
        label_25->setText(QCoreApplication::translate("ControlWindow", "I-09 M\316\251", nullptr));
        label_26->setText(QCoreApplication::translate("ControlWindow", "I-10 M\316\251", nullptr));
        label_27->setText(QCoreApplication::translate("ControlWindow", "I-11 M\316\251", nullptr));
        label_28->setText(QCoreApplication::translate("ControlWindow", "I-12 M\316\251", nullptr));
        label_29->setText(QCoreApplication::translate("ControlWindow", "I-13 M\316\251", nullptr));
        label_30->setText(QCoreApplication::translate("ControlWindow", "I-14 M\316\251", nullptr));
        label_31->setText(QCoreApplication::translate("ControlWindow", "I-15 M\316\251", nullptr));
        realImpedanceStart->setText(QCoreApplication::translate("ControlWindow", "\346\265\213\351\207\217\351\230\273\346\212\227", nullptr));
        label->setText(QCoreApplication::translate("ControlWindow", "\346\214\257  \345\271\205", nullptr));
        realImpedanceStop->setText(QCoreApplication::translate("ControlWindow", "\346\265\213\351\207\217\347\273\223\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlWindow: public Ui_ControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLWINDOW_H
