/****************************************************************************
** Meta object code from reading C++ file 'gesturecanvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gesturecanvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gesturecanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GestureCanvas_t {
    QByteArrayData data[8];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GestureCanvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GestureCanvas_t qt_meta_stringdata_GestureCanvas = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GestureCanvas"
QT_MOC_LITERAL(1, 14, 19), // "onGestureTrackBegin"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "onGestureTracking"
QT_MOC_LITERAL(4, 53, 17), // "onGestureTrackEnd"
QT_MOC_LITERAL(5, 71, 10), // "paintEvent"
QT_MOC_LITERAL(6, 82, 12), // "QPaintEvent*"
QT_MOC_LITERAL(7, 95, 1) // "e"

    },
    "GestureCanvas\0onGestureTrackBegin\0\0"
    "onGestureTracking\0onGestureTrackEnd\0"
    "paintEvent\0QPaintEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GestureCanvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void GestureCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GestureCanvas *_t = static_cast<GestureCanvas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onGestureTrackBegin(); break;
        case 1: _t->onGestureTracking(); break;
        case 2: _t->onGestureTrackEnd(); break;
        case 3: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GestureCanvas::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_GestureCanvas.data,
      qt_meta_data_GestureCanvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GestureCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestureCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GestureCanvas.stringdata0))
        return static_cast<void*>(const_cast< GestureCanvas*>(this));
    return QLabel::qt_metacast(_clname);
}

int GestureCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
