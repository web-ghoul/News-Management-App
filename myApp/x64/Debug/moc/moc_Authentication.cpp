/****************************************************************************
** Meta object code from reading C++ file 'Authentication.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Authentication.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Authentication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_Authentication_t {
    uint offsetsAndSizes[16];
    char stringdata0[15];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[32];
    char stringdata5[35];
    char stringdata6[34];
    char stringdata7[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Authentication_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Authentication_t qt_meta_stringdata_Authentication = {
    {
        QT_MOC_LITERAL(0, 14),  // "Authentication"
        QT_MOC_LITERAL(15, 20),  // "on_btn_login_clicked"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 23),  // "on_btn_register_clicked"
        QT_MOC_LITERAL(61, 31),  // "on_eye_pass_reg_toolBtn_clicked"
        QT_MOC_LITERAL(93, 34),  // "on_eye_conPass_reg_toolBtn_cl..."
        QT_MOC_LITERAL(128, 33),  // "on_eye_pass_login_toolBtn_cli..."
        QT_MOC_LITERAL(162, 26)   // "on_forgot_pass_btn_clicked"
    },
    "Authentication",
    "on_btn_login_clicked",
    "",
    "on_btn_register_clicked",
    "on_eye_pass_reg_toolBtn_clicked",
    "on_eye_conPass_reg_toolBtn_clicked",
    "on_eye_pass_login_toolBtn_clicked",
    "on_forgot_pass_btn_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Authentication[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Authentication::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Authentication.offsetsAndSizes,
    qt_meta_data_Authentication,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Authentication_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Authentication, std::true_type>,
        // method 'on_btn_login_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_register_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_eye_pass_reg_toolBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_eye_conPass_reg_toolBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_eye_pass_login_toolBtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_forgot_pass_btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Authentication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Authentication *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btn_login_clicked(); break;
        case 1: _t->on_btn_register_clicked(); break;
        case 2: _t->on_eye_pass_reg_toolBtn_clicked(); break;
        case 3: _t->on_eye_conPass_reg_toolBtn_clicked(); break;
        case 4: _t->on_eye_pass_login_toolBtn_clicked(); break;
        case 5: _t->on_forgot_pass_btn_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Authentication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Authentication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Authentication.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Authentication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
