/* 
 * File:   qnavwidget_plugin.h
 * Author: Ivan
 *
 * Created on 26 Декабрь 2012 г., 15:37
 */

#ifndef QNAVWIDGETPLUGIN_H
#define	QNAVWIDGETPLUGIN_H


#include <QDesignerContainerExtension>
#include <QDesignerCustomWidgetInterface>
#include "../QNavWidget/QNavWidget.h"

class QNavWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface {
     Q_OBJECT
     Q_INTERFACES(QDesignerCustomWidgetInterface)    
public:

#if QT_VERSION >= 0x050000
Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface" )
#endif
    
    QNavWidgetPlugin(QObject *parent = 0);
    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

 private:
    bool initialized;

};

#endif	/* QNAVWIDGETPLUGIN_H */

