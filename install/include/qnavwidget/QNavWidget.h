/* 
 * File:   QNavWidget.h
 * Author: Ivan
 *
 * Created on 25 Декабрь 2012 г., 14:05
 */

#ifndef QNAVWIDGET_H
#define	QNAVWIDGET_H

#include <QtSvg>
#include <QStringList>

#define TEXT_ITEM_COUNT 12

class QNavWidget : public QGraphicsView {
    Q_OBJECT
    Q_PROPERTY ( bool enabledLed0 READ isEnabledLed0 WRITE setEnabledLed0 )
    Q_PROPERTY ( bool enabledLed1 READ isEnabledLed1 WRITE setEnabledLed1 )
    Q_PROPERTY ( bool enabledLed2 READ isEnabledLed2 WRITE setEnabledLed2 )
    Q_PROPERTY ( bool enabledLed3 READ isEnabledLed3 WRITE setEnabledLed3 )
    Q_PROPERTY ( bool enabledLed4 READ isEnabledLed4 WRITE setEnabledLed4 )
    Q_PROPERTY ( bool enabledLed5 READ isEnabledLed5 WRITE setEnabledLed5 )
    Q_PROPERTY ( double valueAmpL READ valueAmpL WRITE setValueAmpL )
    Q_PROPERTY ( double valueAmpR READ valueAmpR WRITE setValueAmpR )
    Q_PROPERTY ( double valueAmpScale READ valueAmpScale WRITE setValueAmpScale )
    Q_PROPERTY ( double valuePointer  READ valuePointer  WRITE setValuePointer  )
    Q_PROPERTY ( QStringList strings  READ strings  WRITE setStrings)
    
public:
    QNavWidget(QWidget* parent = 0);
    virtual ~QNavWidget();
    
    void setEnabledLed0(bool value);
    void setEnabledLed1(bool value);
    void setEnabledLed2(bool value);
    void setEnabledLed3(bool value);
    void setEnabledLed4(bool value);
    void setEnabledLed5(bool value);
    
    bool isEnabledLed0();
    bool isEnabledLed1();
    bool isEnabledLed2();
    bool isEnabledLed3();
    bool isEnabledLed4();
    bool isEnabledLed5();
    
    void setValueAmpL(float value);
    void setValueAmpR(float value);
    void setValueAmpScale(float value);
    void setValuePointer (float value);
    
    float valueAmpL();
    float valueAmpR();
    float valueAmpScale();
    float valuePointer ();
    
    void setStrings(const QStringList& list);
    QStringList strings() const;
    
private:
    void resizeEvent(QResizeEvent *event);
    void updateSize();
    
    QGraphicsScene* m_scene;
    QSvgRenderer* m_renderer;

    QGraphicsSimpleTextItem* m_item_text[TEXT_ITEM_COUNT];
    QGraphicsSimpleTextItem* m_text_amp_l;
    QGraphicsSimpleTextItem* m_text_amp_r;
    QGraphicsSvgItem* m_background;
    QGraphicsSvgItem* m_layer;
    QGraphicsSvgItem* m_pointer;
    QGraphicsSvgItem* m_shadow_l;
    QGraphicsSvgItem* m_shadow_r;
    QGraphicsSvgItem* m_item_led0;
    QGraphicsSvgItem* m_item_led1;
    QGraphicsSvgItem* m_item_led2;
    QGraphicsSvgItem* m_item_led3;
    QGraphicsSvgItem* m_item_led4;
    QGraphicsSvgItem* m_item_led5;
    QStringList m_strings;
    
    float m_amp_l;
    float m_amp_r;
    float m_pointer_value;
    float m_amp_scale;
};

#endif	/* QNAVWIDGET_H */

