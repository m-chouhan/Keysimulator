/****************************************************************************
** Meta object code from reading C++ file 'KeyListenerServer.h'
**
** Created: Tue Nov 12 07:45:07 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../KeyListenerServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KeyListenerServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KeyListenerServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      33,   18,   18,   18, 0x0a,
      44,   18,   18,   18, 0x0a,
      61,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KeyListenerServer[] = {
    "KeyListenerServer\0\0OnConnected()\0"
    "readData()\0OnDisconnected()\0readRawData()\0"
};

void KeyListenerServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KeyListenerServer *_t = static_cast<KeyListenerServer *>(_o);
        switch (_id) {
        case 0: _t->OnConnected(); break;
        case 1: _t->readData(); break;
        case 2: _t->OnDisconnected(); break;
        case 3: _t->readRawData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData KeyListenerServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KeyListenerServer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KeyListenerServer,
      qt_meta_data_KeyListenerServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KeyListenerServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KeyListenerServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KeyListenerServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KeyListenerServer))
        return static_cast<void*>(const_cast< KeyListenerServer*>(this));
    return QDialog::qt_metacast(_clname);
}

int KeyListenerServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
