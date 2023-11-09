/****************************************************************************
** Meta object code from reading C++ file 'controlwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../GUI/Windows/controlwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlWindow_t {
    QByteArrayData data[23];
    char stringdata0[470];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlWindow_t qt_meta_stringdata_ControlWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ControlWindow"
QT_MOC_LITERAL(1, 14, 27), // "SIGNAL_CONVERTStart_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 26), // "SIGNAL_CONVERTStop_clicked"
QT_MOC_LITERAL(4, 70, 25), // "SIGNAL_StopReadContinuous"
QT_MOC_LITERAL(5, 96, 30), // "SIGNAL_DebugFPGAButton_clicked"
QT_MOC_LITERAL(6, 127, 22), // "StartSubThread_ReadRHS"
QT_MOC_LITERAL(7, 150, 21), // "StopSubThread_ReadRHS"
QT_MOC_LITERAL(8, 172, 12), // "realWaveTime"
QT_MOC_LITERAL(9, 185, 13), // "localWaveTime"
QT_MOC_LITERAL(10, 199, 17), // "realImpedanceTime"
QT_MOC_LITERAL(11, 217, 20), // "localVoltageWaveform"
QT_MOC_LITERAL(12, 238, 19), // "realVoltageWaveform"
QT_MOC_LITERAL(13, 258, 21), // "realImpedanceWaveform"
QT_MOC_LITERAL(14, 280, 12), // "openWaveFile"
QT_MOC_LITERAL(15, 293, 18), // "startGraphAndTimer"
QT_MOC_LITERAL(16, 312, 17), // "stopGraphAndTimer"
QT_MOC_LITERAL(17, 330, 22), // "startRealGraphAndTimer"
QT_MOC_LITERAL(18, 353, 21), // "stopRealGraphAndTimer"
QT_MOC_LITERAL(19, 375, 26), // "on_widthSlider_sliderMoved"
QT_MOC_LITERAL(20, 402, 8), // "position"
QT_MOC_LITERAL(21, 411, 29), // "on_realImpedanceStart_clicked"
QT_MOC_LITERAL(22, 441, 28) // "on_realImpedanceStop_clicked"

    },
    "ControlWindow\0SIGNAL_CONVERTStart_clicked\0"
    "\0SIGNAL_CONVERTStop_clicked\0"
    "SIGNAL_StopReadContinuous\0"
    "SIGNAL_DebugFPGAButton_clicked\0"
    "StartSubThread_ReadRHS\0StopSubThread_ReadRHS\0"
    "realWaveTime\0localWaveTime\0realImpedanceTime\0"
    "localVoltageWaveform\0realVoltageWaveform\0"
    "realImpedanceWaveform\0openWaveFile\0"
    "startGraphAndTimer\0stopGraphAndTimer\0"
    "startRealGraphAndTimer\0stopRealGraphAndTimer\0"
    "on_widthSlider_sliderMoved\0position\0"
    "on_realImpedanceStart_clicked\0"
    "on_realImpedanceStop_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    0,  115,    2, 0x06 /* Public */,
       4,    0,  116,    2, 0x06 /* Public */,
       5,    0,  117,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  118,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x0a /* Public */,
       8,    0,  120,    2, 0x0a /* Public */,
       9,    0,  121,    2, 0x0a /* Public */,
      10,    0,  122,    2, 0x0a /* Public */,
      11,    0,  123,    2, 0x0a /* Public */,
      12,    0,  124,    2, 0x0a /* Public */,
      13,    0,  125,    2, 0x0a /* Public */,
      14,    0,  126,    2, 0x08 /* Private */,
      15,    0,  127,    2, 0x08 /* Private */,
      16,    0,  128,    2, 0x08 /* Private */,
      17,    0,  129,    2, 0x08 /* Private */,
      18,    0,  130,    2, 0x08 /* Private */,
      19,    1,  131,    2, 0x08 /* Private */,
      21,    0,  134,    2, 0x08 /* Private */,
      22,    0,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ControlWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_CONVERTStart_clicked(); break;
        case 1: _t->SIGNAL_CONVERTStop_clicked(); break;
        case 2: _t->SIGNAL_StopReadContinuous(); break;
        case 3: _t->SIGNAL_DebugFPGAButton_clicked(); break;
        case 4: _t->StartSubThread_ReadRHS(); break;
        case 5: _t->StopSubThread_ReadRHS(); break;
        case 6: _t->realWaveTime(); break;
        case 7: _t->localWaveTime(); break;
        case 8: _t->realImpedanceTime(); break;
        case 9: _t->localVoltageWaveform(); break;
        case 10: _t->realVoltageWaveform(); break;
        case 11: _t->realImpedanceWaveform(); break;
        case 12: _t->openWaveFile(); break;
        case 13: _t->startGraphAndTimer(); break;
        case 14: _t->stopGraphAndTimer(); break;
        case 15: _t->startRealGraphAndTimer(); break;
        case 16: _t->stopRealGraphAndTimer(); break;
        case 17: _t->on_widthSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_realImpedanceStart_clicked(); break;
        case 19: _t->on_realImpedanceStop_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControlWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWindow::SIGNAL_CONVERTStart_clicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControlWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWindow::SIGNAL_CONVERTStop_clicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControlWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWindow::SIGNAL_StopReadContinuous)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControlWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlWindow::SIGNAL_DebugFPGAButton_clicked)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControlWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ControlWindow.data,
    qt_meta_data_ControlWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControlWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ControlWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void ControlWindow::SIGNAL_CONVERTStart_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ControlWindow::SIGNAL_CONVERTStop_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ControlWindow::SIGNAL_StopReadContinuous()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ControlWindow::SIGNAL_DebugFPGAButton_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
