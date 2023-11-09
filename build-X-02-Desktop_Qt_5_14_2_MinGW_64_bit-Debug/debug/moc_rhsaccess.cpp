/****************************************************************************
** Meta object code from reading C++ file 'rhsaccess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Engine/Processing/rhsaccess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rhsaccess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RHSAccess_t {
    QByteArrayData data[23];
    char stringdata0[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RHSAccess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RHSAccess_t qt_meta_stringdata_RHSAccess = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RHSAccess"
QT_MOC_LITERAL(1, 10, 11), // "ReadRHSData"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 17), // "CONVERTStartState"
QT_MOC_LITERAL(4, 41, 21), // "ReadRHSDataContinuous"
QT_MOC_LITERAL(5, 63, 17), // "InitializeXMS6302"
QT_MOC_LITERAL(6, 81, 4), // "int&"
QT_MOC_LITERAL(7, 86, 11), // "DeviceCount"
QT_MOC_LITERAL(8, 98, 8), // "QString&"
QT_MOC_LITERAL(9, 107, 3), // "qID"
QT_MOC_LITERAL(10, 111, 5), // "bool&"
QT_MOC_LITERAL(11, 117, 14), // "isSerialOpened"
QT_MOC_LITERAL(12, 132, 13), // "SetSampleRate"
QT_MOC_LITERAL(13, 146, 10), // "setFPGAbit"
QT_MOC_LITERAL(14, 157, 9), // "ResetFPGA"
QT_MOC_LITERAL(15, 167, 17), // "InitializeRHS2116"
QT_MOC_LITERAL(16, 185, 12), // "convertStart"
QT_MOC_LITERAL(17, 198, 11), // "convertStop"
QT_MOC_LITERAL(18, 210, 21), // "impedanceConvertStart"
QT_MOC_LITERAL(19, 232, 20), // "impedanceConvertStop"
QT_MOC_LITERAL(20, 253, 21), // "ReadFromRHSContinuous"
QT_MOC_LITERAL(21, 275, 11), // "StopReading"
QT_MOC_LITERAL(22, 287, 9) // "DebugFPGA"

    },
    "RHSAccess\0ReadRHSData\0\0CONVERTStartState\0"
    "ReadRHSDataContinuous\0InitializeXMS6302\0"
    "int&\0DeviceCount\0QString&\0qID\0bool&\0"
    "isSerialOpened\0SetSampleRate\0setFPGAbit\0"
    "ResetFPGA\0InitializeRHS2116\0convertStart\0"
    "convertStop\0impedanceConvertStart\0"
    "impedanceConvertStop\0ReadFromRHSContinuous\0"
    "StopReading\0DebugFPGA"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RHSAccess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    1,   92,    2, 0x06 /* Public */,
       4,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   98,    2, 0x0a /* Public */,
      12,    1,  105,    2, 0x0a /* Public */,
      13,    0,  108,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      16,    0,  111,    2, 0x0a /* Public */,
      17,    0,  112,    2, 0x0a /* Public */,
      18,    0,  113,    2, 0x0a /* Public */,
      19,    0,  114,    2, 0x0a /* Public */,
      20,    0,  115,    2, 0x0a /* Public */,
      21,    0,  116,    2, 0x0a /* Public */,
      22,    0,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 10,    7,    9,   11,
    QMetaType::Void, QMetaType::QVariant,    2,
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

       0        // eod
};

void RHSAccess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RHSAccess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ReadRHSData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->CONVERTStartState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ReadRHSDataContinuous((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->InitializeXMS6302((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->SetSampleRate((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->setFPGAbit(); break;
        case 6: _t->ResetFPGA(); break;
        case 7: _t->InitializeRHS2116(); break;
        case 8: _t->convertStart(); break;
        case 9: _t->convertStop(); break;
        case 10: _t->impedanceConvertStart(); break;
        case 11: _t->impedanceConvertStop(); break;
        case 12: _t->ReadFromRHSContinuous(); break;
        case 13: _t->StopReading(); break;
        case 14: _t->DebugFPGA(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RHSAccess::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RHSAccess::ReadRHSData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RHSAccess::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RHSAccess::CONVERTStartState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RHSAccess::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RHSAccess::ReadRHSDataContinuous)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RHSAccess::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RHSAccess.data,
    qt_meta_data_RHSAccess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RHSAccess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RHSAccess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RHSAccess.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CPionway"))
        return static_cast< CPionway*>(this);
    return QObject::qt_metacast(_clname);
}

int RHSAccess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void RHSAccess::ReadRHSData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RHSAccess::CONVERTStartState(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RHSAccess::ReadRHSDataContinuous(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
