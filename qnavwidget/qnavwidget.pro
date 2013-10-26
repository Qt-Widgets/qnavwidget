TEMPLATE = lib
DESTDIR = dist
TARGET = $$qtLibraryTarget(QNavWidget)
CONFIG += qt warn_on build_all dll
QT = core gui svg
SOURCES += QNavWidget.cpp
HEADERS += QNavWidget.h
RESOURCES += ../resources/qnavwidget.qrc
OBJECTS_DIR = obj

headers.files = QNavWidget.h
headers.path = ../install/include/qnavwidget

staticlib.files = dist/libQNavWidget.a dist/libQNavWidgetd.a
staticlib.path = ../install/lib 

lib.files = dist/QNavWidget.dll dist/QNavWidgetd.dll
lib.path = ../install/bin

INSTALLS = headers staticlib lib

win32 {
    DEFINES += QT_DLL
}
