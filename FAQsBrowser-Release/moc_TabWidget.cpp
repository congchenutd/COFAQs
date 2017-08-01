/****************************************************************************
** Meta object code from reading C++ file 'TabWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FAQsBrowser/TabWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TabWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TabWidget_t {
    QByteArrayData data[22];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TabWidget_t qt_meta_stringdata_TabWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TabWidget"
QT_MOC_LITERAL(1, 10, 19), // "currentTitleChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "title"
QT_MOC_LITERAL(4, 37, 11), // "linkHovered"
QT_MOC_LITERAL(5, 49, 4), // "link"
QT_MOC_LITERAL(6, 54, 12), // "loadProgress"
QT_MOC_LITERAL(7, 67, 8), // "progress"
QT_MOC_LITERAL(8, 76, 14), // "historyChanged"
QT_MOC_LITERAL(9, 91, 8), // "closeTab"
QT_MOC_LITERAL(10, 100, 5), // "index"
QT_MOC_LITERAL(11, 106, 14), // "onCloseAllTabs"
QT_MOC_LITERAL(12, 121, 16), // "onCloseOtherTabs"
QT_MOC_LITERAL(13, 138, 11), // "onReloadTab"
QT_MOC_LITERAL(14, 150, 15), // "onReloadAllTabs"
QT_MOC_LITERAL(15, 166, 11), // "onAPISearch"
QT_MOC_LITERAL(16, 178, 3), // "API"
QT_MOC_LITERAL(17, 182, 3), // "api"
QT_MOC_LITERAL(18, 186, 16), // "onCurrentChanged"
QT_MOC_LITERAL(19, 203, 20), // "onWebViewLoadStarted"
QT_MOC_LITERAL(20, 224, 20), // "onWebViewIconChanged"
QT_MOC_LITERAL(21, 245, 21) // "onWebViewTitleChanged"

    },
    "TabWidget\0currentTitleChanged\0\0title\0"
    "linkHovered\0link\0loadProgress\0progress\0"
    "historyChanged\0closeTab\0index\0"
    "onCloseAllTabs\0onCloseOtherTabs\0"
    "onReloadTab\0onReloadAllTabs\0onAPISearch\0"
    "API\0api\0onCurrentChanged\0onWebViewLoadStarted\0"
    "onWebViewIconChanged\0onWebViewTitleChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       8,    0,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  104,    2, 0x0a /* Public */,
       9,    0,  107,    2, 0x2a /* Public | MethodCloned */,
      11,    0,  108,    2, 0x0a /* Public */,
      12,    1,  109,    2, 0x08 /* Private */,
      13,    1,  112,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x28 /* Private | MethodCloned */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    1,  117,    2, 0x08 /* Private */,
      18,    1,  120,    2, 0x08 /* Private */,
      19,    0,  123,    2, 0x08 /* Private */,
      20,    0,  124,    2, 0x08 /* Private */,
      21,    1,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void TabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TabWidget *_t = static_cast<TabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentTitleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->linkHovered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->loadProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->historyChanged(); break;
        case 4: _t->closeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->closeTab(); break;
        case 6: _t->onCloseAllTabs(); break;
        case 7: _t->onCloseOtherTabs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onReloadTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onReloadTab(); break;
        case 10: _t->onReloadAllTabs(); break;
        case 11: _t->onAPISearch((*reinterpret_cast< const API(*)>(_a[1]))); break;
        case 12: _t->onCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onWebViewLoadStarted(); break;
        case 14: _t->onWebViewIconChanged(); break;
        case 15: _t->onWebViewTitleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TabWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::currentTitleChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (TabWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::linkHovered)) {
                *result = 1;
            }
        }
        {
            typedef void (TabWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::loadProgress)) {
                *result = 2;
            }
        }
        {
            typedef void (TabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TabWidget::historyChanged)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject TabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_TabWidget.data,
      qt_meta_data_TabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TabWidget.stringdata0))
        return static_cast<void*>(const_cast< TabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int TabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void TabWidget::currentTitleChanged(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TabWidget::linkHovered(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TabWidget::loadProgress(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TabWidget::historyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
