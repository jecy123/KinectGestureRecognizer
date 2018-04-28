/****************************************************************************
** Meta object code from reading C++ file 'menuwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../menuwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MenuWidget_t {
    QByteArrayData data[11];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuWidget_t qt_meta_stringdata_MenuWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MenuWidget"
QT_MOC_LITERAL(1, 11, 13), // "cursorPosMove"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "dx"
QT_MOC_LITERAL(4, 29, 2), // "dy"
QT_MOC_LITERAL(5, 32, 13), // "cursorTouched"
QT_MOC_LITERAL(6, 46, 1), // "x"
QT_MOC_LITERAL(7, 48, 1), // "y"
QT_MOC_LITERAL(8, 50, 9), // "clickedAt"
QT_MOC_LITERAL(9, 60, 18), // "onBtnPicturePushed"
QT_MOC_LITERAL(10, 79, 18) // "onBtnGesturePushed"

    },
    "MenuWidget\0cursorPosMove\0\0dx\0dy\0"
    "cursorTouched\0x\0y\0clickedAt\0"
    "onBtnPicturePushed\0onBtnGesturePushed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuWidget[] = {

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
       1,    2,   39,    2, 0x0a /* Public */,
       5,    2,   44,    2, 0x0a /* Public */,
       8,    2,   49,    2, 0x0a /* Public */,
       9,    0,   54,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MenuWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuWidget *_t = static_cast<MenuWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cursorPosMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->cursorTouched((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->clickedAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onBtnPicturePushed(); break;
        case 4: _t->onBtnGesturePushed(); break;
        default: ;
        }
    }
}

const QMetaObject MenuWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_MenuWidget.data,
      qt_meta_data_MenuWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MenuWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MenuWidget.stringdata0))
        return static_cast<void*>(const_cast< MenuWidget*>(this));
    return BaseWidget::qt_metacast(_clname);
}

int MenuWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
