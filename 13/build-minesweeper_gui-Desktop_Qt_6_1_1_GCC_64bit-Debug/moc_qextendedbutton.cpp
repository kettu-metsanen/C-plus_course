/****************************************************************************
** Meta object code from reading C++ file 'qextendedbutton.hh'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../minesweeper_gui/qextendedbutton.hh"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qextendedbutton.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QExtendedButton_t {
    const uint offsetsAndSize[8];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QExtendedButton_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QExtendedButton_t qt_meta_stringdata_QExtendedButton = {
    {
QT_MOC_LITERAL(0, 15), // "QExtendedButton"
QT_MOC_LITERAL(16, 12), // "rightClicked"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 11) // "leftClicked"

    },
    "QExtendedButton\0rightClicked\0\0leftClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QExtendedButton[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    0 /* Public */,
       3,    0,   27,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QExtendedButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QExtendedButton *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rightClicked(); break;
        case 1: _t->leftClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QExtendedButton::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QExtendedButton::rightClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QExtendedButton::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QExtendedButton::leftClicked)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject QExtendedButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_meta_stringdata_QExtendedButton.offsetsAndSize,
    qt_meta_data_QExtendedButton,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QExtendedButton_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *QExtendedButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QExtendedButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QExtendedButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int QExtendedButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QExtendedButton::rightClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QExtendedButton::leftClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE