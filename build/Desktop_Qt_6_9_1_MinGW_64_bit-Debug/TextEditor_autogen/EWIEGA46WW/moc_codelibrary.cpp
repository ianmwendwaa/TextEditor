/****************************************************************************
** Meta object code from reading C++ file 'codelibrary.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../codelibrary.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'codelibrary.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
struct qt_meta_tag_ZN11CodeLibraryE_t {};
} // unnamed namespace

template <> constexpr inline auto CodeLibrary::qt_create_metaobjectdata<qt_meta_tag_ZN11CodeLibraryE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CodeLibrary",
        "new_document",
        "",
        "save_document",
        "save_document_as",
        "open_document",
        "show_info",
        "page_setup",
        "print_doc",
        "increase_font",
        "decrease_font",
        "toggle_bullets",
        "toggle_italics",
        "toggle_bold",
        "toggle_underline",
        "toggle_alignments",
        "Qt::Alignment",
        "alignment",
        "word_counter"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'new_document'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'save_document'
        QtMocHelpers::SlotData<bool()>(3, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'save_document_as'
        QtMocHelpers::SlotData<bool()>(4, 2, QMC::AccessPublic, QMetaType::Bool),
        // Slot 'open_document'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'show_info'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'page_setup'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'print_doc'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'increase_font'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'decrease_font'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'toggle_bullets'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'toggle_italics'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'toggle_bold'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'toggle_underline'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'toggle_alignments'
        QtMocHelpers::SlotData<void(Qt::Alignment)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Slot 'word_counter'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CodeLibrary, qt_meta_tag_ZN11CodeLibraryE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CodeLibrary::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11CodeLibraryE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11CodeLibraryE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11CodeLibraryE_t>.metaTypes,
    nullptr
} };

void CodeLibrary::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CodeLibrary *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->new_document(); break;
        case 1: { bool _r = _t->save_document();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->save_document_as();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->open_document(); break;
        case 4: _t->show_info(); break;
        case 5: _t->page_setup(); break;
        case 6: _t->print_doc(); break;
        case 7: _t->increase_font(); break;
        case 8: _t->decrease_font(); break;
        case 9: _t->toggle_bullets(); break;
        case 10: _t->toggle_italics(); break;
        case 11: _t->toggle_bold(); break;
        case 12: _t->toggle_underline(); break;
        case 13: _t->toggle_alignments((*reinterpret_cast< std::add_pointer_t<Qt::Alignment>>(_a[1]))); break;
        case 14: _t->word_counter(); break;
        default: ;
        }
    }
}

const QMetaObject *CodeLibrary::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CodeLibrary::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11CodeLibraryE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CodeLibrary::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
