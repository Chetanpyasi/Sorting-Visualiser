/****************************************************************************
** Meta object code from reading C++ file 'sortingvisualizer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../sortingvisualizer.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sortingvisualizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSortingVisualizerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSortingVisualizerENDCLASS = QtMocHelpers::stringData(
    "SortingVisualizer",
    "visualizeAlgorithm",
    "",
    "algorithm",
    "input",
    "updateVisualization",
    "play",
    "pause",
    "resetVisualization"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSortingVisualizerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x08,    1 /* Private */,
       5,    0,   49,    2, 0x08,    4 /* Private */,
       6,    0,   50,    2, 0x08,    5 /* Private */,
       7,    0,   51,    2, 0x08,    6 /* Private */,
       8,    0,   52,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SortingVisualizer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSSortingVisualizerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSortingVisualizerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSortingVisualizerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SortingVisualizer, std::true_type>,
        // method 'visualizeAlgorithm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateVisualization'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'play'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetVisualization'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SortingVisualizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SortingVisualizer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->visualizeAlgorithm((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->updateVisualization(); break;
        case 2: _t->play(); break;
        case 3: _t->pause(); break;
        case 4: _t->resetVisualization(); break;
        default: ;
        }
    }
}

const QMetaObject *SortingVisualizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SortingVisualizer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSortingVisualizerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SortingVisualizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
