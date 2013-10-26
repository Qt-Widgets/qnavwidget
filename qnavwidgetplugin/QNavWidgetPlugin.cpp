/* 
 * File:   qnavwidget_plugin.cpp
 * Author: Ivan
 * 
 * Created on 26 Декабрь 2012 г., 15:37
 */

#include "QNavWidgetPlugin.h"

 #include <QtPlugin>

QNavWidgetPlugin::QNavWidgetPlugin(QObject *parent)
     : QObject(parent)
{
     initialized = false;
}

 void QNavWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
 {
     if (initialized)
         return;

     initialized = true;
 }

 bool QNavWidgetPlugin::isInitialized() const
 {
     return initialized;
 }

 QWidget *QNavWidgetPlugin::createWidget(QWidget *parent)
 {
     return new QNavWidget(parent);
 }

 QString QNavWidgetPlugin::name() const
 {
     return "QNavWidget";
 }

 QString QNavWidgetPlugin::group() const
 {
     return "Navigate Widgets";
 }

 QIcon QNavWidgetPlugin::icon() const
 {
     return QIcon(":qnavwidget.png");
 }

 QString QNavWidgetPlugin::toolTip() const
 {
     return "";
 }

 QString QNavWidgetPlugin::whatsThis() const
 {
     return "";
 }

 bool QNavWidgetPlugin::isContainer() const
 {
     return false;
 }

 QString QNavWidgetPlugin::domXml() const
 {
     return "<ui language=\"c++\">\n"
            " <widget class=\"QNavWidget\" name=\"navWidget\">\n"
            "  <property name=\"geometry\">\n"
            "   <rect>\n"
            "    <x>0</x>\n"
            "    <y>0</y>\n"
            "    <width>100</width>\n"
            "    <height>100</height>\n"
            "   </rect>\n"
            "  </property>\n"
            " </widget>\n"
            "</ui>";
 }

 QString QNavWidgetPlugin::includeFile() const
 {
    return "QNavWidget.h";
 }

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( QNavWidgetPlugin, CustomWidgetCollectionInterface )
#endif

