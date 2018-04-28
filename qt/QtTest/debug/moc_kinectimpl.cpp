/****************************************************************************
** Meta object code from reading C++ file 'kinectimpl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kinectimpl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kinectimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KinectImpl_t {
    QByteArrayData data[32];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KinectImpl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KinectImpl_t qt_meta_stringdata_KinectImpl = {
    {
QT_MOC_LITERAL(0, 0, 10), // "KinectImpl"
QT_MOC_LITERAL(1, 11, 10), // "fingerMove"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 2), // "dx"
QT_MOC_LITERAL(4, 26, 2), // "dy"
QT_MOC_LITERAL(5, 29, 13), // "fingerTouched"
QT_MOC_LITERAL(6, 43, 10), // "handPushed"
QT_MOC_LITERAL(7, 54, 8), // "handMove"
QT_MOC_LITERAL(8, 63, 8), // "fistMove"
QT_MOC_LITERAL(9, 72, 8), // "fistGrab"
QT_MOC_LITERAL(10, 81, 1), // "x"
QT_MOC_LITERAL(11, 83, 1), // "y"
QT_MOC_LITERAL(12, 85, 2), // "vx"
QT_MOC_LITERAL(13, 88, 2), // "vy"
QT_MOC_LITERAL(14, 91, 2), // "vz"
QT_MOC_LITERAL(15, 94, 11), // "fistRelease"
QT_MOC_LITERAL(16, 106, 11), // "handClicked"
QT_MOC_LITERAL(17, 118, 11), // "handTouched"
QT_MOC_LITERAL(18, 130, 14), // "handTouchMoved"
QT_MOC_LITERAL(19, 145, 13), // "handWavedLeft"
QT_MOC_LITERAL(20, 159, 14), // "handWavedRight"
QT_MOC_LITERAL(21, 174, 9), // "zoomBegin"
QT_MOC_LITERAL(22, 184, 6), // "zoomIn"
QT_MOC_LITERAL(23, 191, 6), // "offset"
QT_MOC_LITERAL(24, 198, 7), // "zoomOut"
QT_MOC_LITERAL(25, 206, 7), // "zoomEnd"
QT_MOC_LITERAL(26, 214, 8), // "rotateCW"
QT_MOC_LITERAL(27, 223, 10), // "rotateRate"
QT_MOC_LITERAL(28, 234, 9), // "rotateCCW"
QT_MOC_LITERAL(29, 244, 9), // "rotateEnd"
QT_MOC_LITERAL(30, 254, 5), // "start"
QT_MOC_LITERAL(31, 260, 4) // "stop"

    },
    "KinectImpl\0fingerMove\0\0dx\0dy\0fingerTouched\0"
    "handPushed\0handMove\0fistMove\0fistGrab\0"
    "x\0y\0vx\0vy\0vz\0fistRelease\0handClicked\0"
    "handTouched\0handTouchMoved\0handWavedLeft\0"
    "handWavedRight\0zoomBegin\0zoomIn\0offset\0"
    "zoomOut\0zoomEnd\0rotateCW\0rotateRate\0"
    "rotateCCW\0rotateEnd\0start\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KinectImpl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  119,    2, 0x06 /* Public */,
       5,    0,  124,    2, 0x06 /* Public */,
       6,    0,  125,    2, 0x06 /* Public */,
       7,    2,  126,    2, 0x06 /* Public */,
       8,    2,  131,    2, 0x06 /* Public */,
       9,    7,  136,    2, 0x06 /* Public */,
      15,    7,  151,    2, 0x06 /* Public */,
      16,    2,  166,    2, 0x06 /* Public */,
      17,    2,  171,    2, 0x06 /* Public */,
      18,    4,  176,    2, 0x06 /* Public */,
      19,    1,  185,    2, 0x06 /* Public */,
      20,    1,  188,    2, 0x06 /* Public */,
      21,    2,  191,    2, 0x06 /* Public */,
      22,    1,  196,    2, 0x06 /* Public */,
      24,    1,  199,    2, 0x06 /* Public */,
      25,    0,  202,    2, 0x06 /* Public */,
      26,    1,  203,    2, 0x06 /* Public */,
      28,    1,  206,    2, 0x06 /* Public */,
      29,    0,  209,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      30,    0,  210,    2, 0x0a /* Public */,
      31,    0,  211,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,    3,    4,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,    3,    4,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Float,   23,
    QMetaType::Void, QMetaType::Float,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KinectImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KinectImpl *_t = static_cast<KinectImpl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fingerMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->fingerTouched(); break;
        case 2: _t->handPushed(); break;
        case 3: _t->handMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->fistMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->fistGrab((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7]))); break;
        case 6: _t->fistRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7]))); break;
        case 7: _t->handClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->handTouched((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->handTouchMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->handWavedLeft((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->handWavedRight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->zoomBegin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->zoomIn((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->zoomOut((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->zoomEnd(); break;
        case 16: _t->rotateCW((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->rotateCCW((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->rotateEnd(); break;
        case 19: _t->start(); break;
        case 20: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KinectImpl::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::fingerMove)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::fingerTouched)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handPushed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handMove)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::fistMove)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int , int , int , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::fistGrab)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int , int , int , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::fistRelease)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handClicked)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handTouched)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handTouchMoved)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handWavedLeft)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::handWavedRight)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::zoomBegin)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::zoomIn)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::zoomOut)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::zoomEnd)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::rotateCW)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::rotateCCW)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (KinectImpl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KinectImpl::rotateEnd)) {
                *result = 18;
                return;
            }
        }
    }
}

const QMetaObject KinectImpl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KinectImpl.data,
      qt_meta_data_KinectImpl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KinectImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KinectImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KinectImpl.stringdata0))
        return static_cast<void*>(const_cast< KinectImpl*>(this));
    if (!strcmp(_clname, "GestureRecgnition"))
        return static_cast< GestureRecgnition*>(const_cast< KinectImpl*>(this));
    return QObject::qt_metacast(_clname);
}

int KinectImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void KinectImpl::fingerMove(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KinectImpl::fingerTouched()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void KinectImpl::handPushed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void KinectImpl::handMove(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void KinectImpl::fistMove(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void KinectImpl::fistGrab(int _t1, int _t2, int _t3, int _t4, float _t5, float _t6, float _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void KinectImpl::fistRelease(int _t1, int _t2, int _t3, int _t4, float _t5, float _t6, float _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void KinectImpl::handClicked(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void KinectImpl::handTouched(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void KinectImpl::handTouchMoved(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void KinectImpl::handWavedLeft(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void KinectImpl::handWavedRight(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void KinectImpl::zoomBegin(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void KinectImpl::zoomIn(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void KinectImpl::zoomOut(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void KinectImpl::zoomEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 15, Q_NULLPTR);
}

// SIGNAL 16
void KinectImpl::rotateCW(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void KinectImpl::rotateCCW(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void KinectImpl::rotateEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 18, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
