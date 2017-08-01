/****************************************************************************
** Meta object code from reading C++ file 'SearchBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FAQsBrowser/SearchBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SearchBar_t {
    QByteArrayData data[14];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchBar_t qt_meta_stringdata_SearchBar = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SearchBar"
QT_MOC_LITERAL(1, 10, 6), // "search"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "target"
QT_MOC_LITERAL(4, 25, 7), // "forward"
QT_MOC_LITERAL(5, 33, 9), // "matchCase"
QT_MOC_LITERAL(6, 43, 9), // "highlight"
QT_MOC_LITERAL(7, 53, 6), // "hideMe"
QT_MOC_LITERAL(8, 60, 8), // "onEdited"
QT_MOC_LITERAL(9, 69, 4), // "text"
QT_MOC_LITERAL(10, 74, 10), // "onFindPrev"
QT_MOC_LITERAL(11, 85, 10), // "onFindNext"
QT_MOC_LITERAL(12, 96, 11), // "onHighlight"
QT_MOC_LITERAL(13, 108, 6) // "enable"

    },
    "SearchBar\0search\0\0target\0forward\0"
    "matchCase\0highlight\0hideMe\0onEdited\0"
    "text\0onFindPrev\0onFindNext\0onHighlight\0"
    "enable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       6,    3,   56,    2, 0x06 /* Public */,
       7,    0,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   64,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,    3,    6,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void SearchBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchBar *_t = static_cast<SearchBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->search((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->highlight((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->hideMe(); break;
        case 3: _t->onEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onFindPrev(); break;
        case 5: _t->onFindNext(); break;
        case 6: _t->onHighlight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SearchBar::*_t)(const QString & , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchBar::search)) {
                *result = 0;
            }
        }
        {
            typedef void (SearchBar::*_t)(const QString & , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchBar::highlight)) {
                *result = 1;
            }
        }
        {
            typedef void (SearchBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchBar::hideMe)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SearchBar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_SearchBar.data,
      qt_meta_data_SearchBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchBar.stringdata0))
        return static_cast<void*>(const_cast< SearchBar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int SearchBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SearchBar::search(const QString & _t1, bool _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SearchBar::highlight(const QString & _t1, bool _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SearchBar::hideMe()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
