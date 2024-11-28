/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[21];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 21), // "downloadSuccess_music"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 21), // "downloadSuccess_lyric"
QT_MOC_LITERAL(4, 52, 21), // "downloadSuccess_cover"
QT_MOC_LITERAL(5, 74, 21), // "playListDoubleClicked"
QT_MOC_LITERAL(6, 96, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 113, 4), // "item"
QT_MOC_LITERAL(8, 118, 14), // "handlePrevSlot"
QT_MOC_LITERAL(9, 133, 14), // "handlePlaySlot"
QT_MOC_LITERAL(10, 148, 14), // "handleNextSlot"
QT_MOC_LITERAL(11, 163, 14), // "handleModeSlot"
QT_MOC_LITERAL(12, 178, 18), // "handleDurationSlot"
QT_MOC_LITERAL(13, 197, 8), // "duration"
QT_MOC_LITERAL(14, 206, 18), // "handlePositionSlot"
QT_MOC_LITERAL(15, 225, 8), // "position"
QT_MOC_LITERAL(16, 234, 17), // "handleTimeoutSlot"
QT_MOC_LITERAL(17, 252, 21), // "handleDoubleClickList"
QT_MOC_LITERAL(18, 274, 16), // "handlePlayFinish"
QT_MOC_LITERAL(19, 291, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(20, 317, 6) // "status"

    },
    "Widget\0downloadSuccess_music\0\0"
    "downloadSuccess_lyric\0downloadSuccess_cover\0"
    "playListDoubleClicked\0QListWidgetItem*\0"
    "item\0handlePrevSlot\0handlePlaySlot\0"
    "handleNextSlot\0handleModeSlot\0"
    "handleDurationSlot\0duration\0"
    "handlePositionSlot\0position\0"
    "handleTimeoutSlot\0handleDoubleClickList\0"
    "handlePlayFinish\0QMediaPlayer::MediaStatus\0"
    "status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    1,   89,    2, 0x0a /* Public */,
      14,    1,   92,    2, 0x0a /* Public */,
      16,    0,   95,    2, 0x0a /* Public */,
      17,    0,   96,    2, 0x0a /* Public */,
      18,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   13,
    QMetaType::Void, QMetaType::LongLong,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadSuccess_music(); break;
        case 1: _t->downloadSuccess_lyric(); break;
        case 2: _t->downloadSuccess_cover(); break;
        case 3: _t->playListDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->handlePrevSlot(); break;
        case 5: _t->handlePlaySlot(); break;
        case 6: _t->handleNextSlot(); break;
        case 7: _t->handleModeSlot(); break;
        case 8: _t->handleDurationSlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 9: _t->handlePositionSlot((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: _t->handleTimeoutSlot(); break;
        case 11: _t->handleDoubleClickList(); break;
        case 12: _t->handlePlayFinish((*reinterpret_cast< QMediaPlayer::MediaStatus(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::MediaStatus >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::downloadSuccess_music)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::downloadSuccess_lyric)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::downloadSuccess_cover)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Widget::*)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::playListDoubleClicked)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Widget::downloadSuccess_music()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Widget::downloadSuccess_lyric()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Widget::downloadSuccess_cover()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Widget::playListDoubleClicked(QListWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
