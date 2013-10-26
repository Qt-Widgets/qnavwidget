TEMPLATE = lib
DESTDIR = dist
TARGET = $$qtLibraryTarget(qnavwidgetplugin)
CONFIG -= debug_and_release
CONFIG += dll plugin release warn_on
QT = core gui svg designer
SOURCES += ../qnavwidget/QNavWidget.cpp QNavWidgetPlugin.cpp
HEADERS +=  ../qnavwidget/QNavWidget.h QNavWidgetPlugin.h
RESOURCES += ../resources/qnavwidget.qrc qnavwidgetplugin.qrc
OBJECTS_DIR = obj

plugin_staticlib.files = dist/libqnavwidgetplugin.a dist/libqnavwidgetplugind.a
plugin_staticlib.path = ../install/plugins/designer

plugin_lib.files = dist/qnavwidgetplugin.dll dist/qnavwidgetplugind.dll
plugin_lib.path = ../install/plugins/designer

INSTALLS = plugin_lib plugin_staticlib


win32 {
    DEFINES += QT_DLL
}
