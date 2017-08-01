/****************************************************************************
** Meta object code from reading C++ file 'WebView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FAQsBrowser/WebView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WebView_t {
    QByteArrayData data[14];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebView_t qt_meta_stringdata_WebView = {
    {
QT_MOC_LITERAL(0, 0, 7), // "WebView"
QT_MOC_LITERAL(1, 8, 9), // "apiSearch"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "API"
QT_MOC_LITERAL(4, 23, 3), // "api"
QT_MOC_LITERAL(5, 27, 18), // "onOpenLinkInNewTab"
QT_MOC_LITERAL(6, 46, 11), // "onSearchAPI"
QT_MOC_LITERAL(7, 58, 10), // "onProgress"
QT_MOC_LITERAL(8, 69, 8), // "progress"
QT_MOC_LITERAL(9, 78, 14), // "onTitleChanged"
QT_MOC_LITERAL(10, 93, 5), // "title"
QT_MOC_LITERAL(11, 99, 8), // "onLoaded"
QT_MOC_LITERAL(12, 108, 12), // "onQueryReply"
QT_MOC_LITERAL(13, 121, 9) // "joDocPage"

    },
    "WebView\0apiSearch\0\0API\0api\0"
    "onOpenLinkInNewTab\0onSearchAPI\0"
    "onProgress\0progress\0onTitleChanged\0"
    "title\0onLoaded\0onQueryReply\0joDocPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    1,   57,    2, 0x08 /* Private */,
      11,    0,   60,    2, 0x08 /* Private */,
      12,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   13,

       0        // eod
};

void WebView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WebView *_t = static_cast<WebView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->apiSearch((*reinterpret_cast< const API(*)>(_a[1]))); break;
        case 1: _t->onOpenLinkInNewTab(); break;
        case 2: _t->onSearchAPI(); break;
        case 3: _t->onProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onTitleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onLoaded(); break;
        case 6: _t->onQueryReply((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WebView::*_t)(const API & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WebView::apiSearch)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject WebView::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata_WebView.data,
      qt_meta_data_WebView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WebView.stringdata0))
        return static_cast<void*>(const_cast< WebView*>(this));
    return QWebView::qt_metacast(_clname);
}

int WebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
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
void WebView::apiSearch(const API & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
