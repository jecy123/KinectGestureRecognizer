/****************************************************************************
** Meta object code from reading C++ file 'gestureview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gestureview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestureview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GestureView_t {
    QByteArrayData data[16];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GestureView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GestureView_t qt_meta_stringdata_GestureView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GestureView"
QT_MOC_LITERAL(1, 12, 13), // "cursorCatched"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 1), // "x"
QT_MOC_LITERAL(4, 29, 1), // "y"
QT_MOC_LITERAL(5, 31, 2), // "dx"
QT_MOC_LITERAL(6, 34, 2), // "dy"
QT_MOC_LITERAL(7, 37, 2), // "vx"
QT_MOC_LITERAL(8, 40, 2), // "vy"
QT_MOC_LITERAL(9, 43, 2), // "vz"
QT_MOC_LITERAL(10, 46, 13), // "cursorPosMove"
QT_MOC_LITERAL(11, 60, 9), // "catchMove"
QT_MOC_LITERAL(12, 70, 10), // "paintEvent"
QT_MOC_LITERAL(13, 81, 12), // "QPaintEvent*"
QT_MOC_LITERAL(14, 94, 5), // "event"
QT_MOC_LITERAL(15, 100, 9) // "setCursor"

    },
    "GestureView\0cursorCatched\0\0x\0y\0dx\0dy\0"
    "vx\0vy\0vz\0cursorPosMove\0catchMove\0"
    "paintEvent\0QPaintEvent*\0event\0setCursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GestureView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    7,   39,    2, 0x0a /* Public */,
      10,    2,   54,    2, 0x0a /* Public */,
      11,    2,   59,    2, 0x0a /* Public */,
      12,    1,   64,    2, 0x0a /* Public */,
      15,    2,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

       0        // eod
};

void GestureView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GestureView *_t = static_cast<GestureView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cursorCatched((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7]))); break;
        case 1: _t->cursorPosMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->catchMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 4: _t->setCursor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject GestureView::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_GestureView.data,
      qt_meta_data_GestureView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GestureView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestureView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GestureView.stringdata0))
        return static_cast<void*>(const_cast< GestureView*>(this));
    if (!strcmp(_clname, "GestureCanvasEventHandler"))
        return static_cast< GestureCanvasEventHandler*>(const_cast< GestureView*>(this));
    return BaseWidget::qt_metacast(_clname);
}

int GestureView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
