/****************************************************************************
** Meta object code from reading C++ file 'PhoneBook.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../PhoneBook.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PhoneBook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PhoneBook_t {
    QByteArrayData data[15];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PhoneBook_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PhoneBook_t qt_meta_stringdata_PhoneBook = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PhoneBook"
QT_MOC_LITERAL(1, 10, 10), // "addContact"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "editContact"
QT_MOC_LITERAL(4, 34, 13), // "deleteContact"
QT_MOC_LITERAL(5, 48, 13), // "searchContact"
QT_MOC_LITERAL(6, 62, 12), // "loadFromFile"
QT_MOC_LITERAL(7, 75, 10), // "saveToFile"
QT_MOC_LITERAL(8, 86, 14), // "addPhoneNumber"
QT_MOC_LITERAL(9, 101, 14), // "saveToDatabase"
QT_MOC_LITERAL(10, 116, 7), // "Contact"
QT_MOC_LITERAL(11, 124, 7), // "contact"
QT_MOC_LITERAL(12, 132, 16), // "loadFromDatabase"
QT_MOC_LITERAL(13, 149, 18), // "deleteFromDatabase"
QT_MOC_LITERAL(14, 168, 10) // "contactKey"

    },
    "PhoneBook\0addContact\0\0editContact\0"
    "deleteContact\0searchContact\0loadFromFile\0"
    "saveToFile\0addPhoneNumber\0saveToDatabase\0"
    "Contact\0contact\0loadFromDatabase\0"
    "deleteFromDatabase\0contactKey"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PhoneBook[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      12,    0,   74,    2, 0x08 /* Private */,
      13,    1,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void PhoneBook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PhoneBook *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addContact(); break;
        case 1: _t->editContact(); break;
        case 2: _t->deleteContact(); break;
        case 3: _t->searchContact(); break;
        case 4: _t->loadFromFile(); break;
        case 5: _t->saveToFile(); break;
        case 6: _t->addPhoneNumber(); break;
        case 7: _t->saveToDatabase((*reinterpret_cast< const Contact(*)>(_a[1]))); break;
        case 8: _t->loadFromDatabase(); break;
        case 9: _t->deleteFromDatabase((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PhoneBook::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_PhoneBook.data,
    qt_meta_data_PhoneBook,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PhoneBook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PhoneBook::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PhoneBook.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PhoneBook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
