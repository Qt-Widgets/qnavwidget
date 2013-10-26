/* 
 * File:   QNavWidget.cpp
 * Author: Ivan
 * 
 * Created on 25 Декабрь 2012 г., 14:05
 */

#include "QNavWidget.h"
#include <math.h>

QNavWidget::QNavWidget(QWidget* parent) : QGraphicsView(parent) {
    
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);
    setInteractive(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255, 255, 255, 0));
    setPalette(p);

    QFont f = font();
    f.setPointSizeF(24);
    setFont(f);
    
    m_amp_l = 0.8;
    m_amp_r = 0.8;
    m_amp_scale = 30.0;
    m_pointer_value = 0.5;
    
    m_renderer = new QSvgRenderer(QString(":nav_channel.svg"));
    
    m_scene = new QGraphicsScene(this);
    setSceneRect(0, 0, 540, 540);
    setScene(m_scene);
    
    m_background = new QGraphicsSvgItem();
    m_pointer  = new QGraphicsSvgItem();
    m_layer    = new QGraphicsSvgItem();
    m_shadow_l = new QGraphicsSvgItem();
    m_shadow_r = new QGraphicsSvgItem();
    
    m_item_led0 = new QGraphicsSvgItem();
    m_item_led1 = new QGraphicsSvgItem();
    m_item_led2 = new QGraphicsSvgItem();
    m_item_led3 = new QGraphicsSvgItem();
    m_item_led4 = new QGraphicsSvgItem();
    m_item_led5 = new QGraphicsSvgItem();
    
    m_background->setElementId("ground");
    m_pointer->setElementId("pointer");
    m_layer->setElementId("layer");
    m_shadow_l->setElementId("shadow_l");
    m_shadow_r->setElementId("shadow_r");
    
    m_item_led0->setElementId("led0");
    m_item_led1->setElementId("led1");
    m_item_led2->setElementId("led2");
    m_item_led3->setElementId("led3");
    m_item_led4->setElementId("led4");
    m_item_led5->setElementId("led5");
    
    m_background->setSharedRenderer(m_renderer);
    m_layer->setSharedRenderer(m_renderer);
    m_pointer->setSharedRenderer(m_renderer);
    m_shadow_l->setSharedRenderer(m_renderer);
    m_shadow_r->setSharedRenderer(m_renderer);

    m_item_led0->setSharedRenderer(m_renderer);
    m_item_led1->setSharedRenderer(m_renderer);
    m_item_led2->setSharedRenderer(m_renderer);
    m_item_led3->setSharedRenderer(m_renderer);
    m_item_led4->setSharedRenderer(m_renderer);
    m_item_led5->setSharedRenderer(m_renderer);
    
    m_scene->addItem(m_background);
    m_scene->addItem(m_layer);
    m_scene->addItem(m_pointer);
    m_scene->addItem(m_shadow_l);
    m_scene->addItem(m_shadow_r);
    m_scene->addItem(m_item_led0);
    m_scene->addItem(m_item_led1);
    m_scene->addItem(m_item_led2);
    m_scene->addItem(m_item_led3);
    m_scene->addItem(m_item_led4);
    m_scene->addItem(m_item_led5);

    m_text_amp_l = new QGraphicsSimpleTextItem();
    m_text_amp_l->setFont(font());
    m_text_amp_l->setBrush(QBrush(QColor(255, 255, 255, 196)));

    m_text_amp_r = new QGraphicsSimpleTextItem();
    m_text_amp_r->setFont(font());
    m_text_amp_r->setBrush(QBrush(QColor(255, 255, 255, 196)));

    m_scene->addItem(m_text_amp_l);
    m_scene->addItem(m_text_amp_r);
    
    for (int i = 0; i < TEXT_ITEM_COUNT; ++i) {
        m_item_text[i] = new QGraphicsSimpleTextItem();
        m_item_text[i]->setFont(font());
        m_item_text[i]->setBrush(QBrush(QColor(255, 255, 255, 196)));
        m_item_text[i]->setText("");
        m_scene->addItem(m_item_text[i]);
    }
    
    updateSize();
}

QNavWidget::~QNavWidget() {

}

void QNavWidget::resizeEvent(QResizeEvent* event) {
    updateSize();
}

void QNavWidget::updateSize() {
    QTransform scale_shadow_l;
    QTransform scale_shadow_r;

    m_background->resetTransform();
    m_pointer->resetTransform();
    m_layer->resetTransform();
    m_shadow_l->resetTransform();
    m_shadow_r->resetTransform();

    m_item_led0->resetTransform();
    m_item_led1->resetTransform();
    m_item_led2->resetTransform();
    m_item_led3->resetTransform();
    m_item_led4->resetTransform();
    m_item_led5->resetTransform();
    
    m_background->setPos(10, 10);
    
    float angle = 280.0*valuePointer() - 10.0;
    m_pointer->setPos(220 + angle, 465);
    
    m_layer->setPos(220, 65);
    
    scale_shadow_l.scale(1, (1 - valueAmpL())*5.5);
    m_shadow_l->setTransform(scale_shadow_l);
    m_shadow_l->setPos(220, 65);

    scale_shadow_r.scale(1, (1 - valueAmpR())*5.5);
    m_shadow_r->setTransform(scale_shadow_r);
    m_shadow_r->setPos(430, 65);
    
    m_item_led0->setPos(305, 390);
    m_item_led1->setPos(305, 325);
    m_item_led2->setPos(305, 260);
    m_item_led3->setPos(305, 195);
    m_item_led4->setPos(305, 130);
    m_item_led5->setPos(305, 65);
    
    float psf = 20 + (45 - font().pointSizeF())*0.5;
    m_text_amp_r->setText(QString("%0dB").arg((int)roundf(valueAmpScale()*valueAmpR()), 2, 10, QChar('0')));
    m_text_amp_r->setPos(430, psf);
    m_text_amp_l->setText(QString("%0dB").arg((int)roundf(valueAmpScale()*valueAmpL()), 2, 10, QChar('0')));
    m_text_amp_l->setPos(220, psf);

    int y = 40;
    for (int i = 0; i < TEXT_ITEM_COUNT; ++i) {
        m_item_text[i]->setPos(40, y);
        if (i < m_strings.size())
            m_item_text[i]->setText(m_strings.at(i));
        y +=40;
    }
    
    resetTransform();
    scale((double)viewport()->width()/540, (double)viewport()->height()/540);
}

void QNavWidget::setEnabledLed0(bool value) {
    m_item_led0->setVisible(!value);
}

void QNavWidget::setEnabledLed1(bool value) {
    m_item_led1->setVisible(!value);
}

void QNavWidget::setEnabledLed2(bool value) {
    m_item_led2->setVisible(!value);
}

void QNavWidget::setEnabledLed3(bool value) {
    m_item_led3->setVisible(!value);
}

void QNavWidget::setEnabledLed4(bool value) {
    m_item_led4->setVisible(!value);
}

void QNavWidget::setEnabledLed5(bool value) {
    m_item_led5->setVisible(!value);
}

bool QNavWidget::isEnabledLed0() {
    return !m_item_led0->isVisible();
}

bool QNavWidget::isEnabledLed1() {
    return !m_item_led1->isVisible();
}

bool QNavWidget::isEnabledLed2() {
    return !m_item_led2->isVisible();
}

bool QNavWidget::isEnabledLed3() {
    return !m_item_led3->isVisible();
}

bool QNavWidget::isEnabledLed4() {
    return !m_item_led4->isVisible();
}

bool QNavWidget::isEnabledLed5() {
    return !m_item_led5->isVisible();
}

void QNavWidget::setValueAmpL(float value) {
    if (value < 0) value = 0;
    else
        if (value > 1) value = 1;
    m_amp_l = value;
    updateSize();
}

void QNavWidget::setValueAmpR(float value) {
    if (value < 0) value = 0;
    else
        if (value > 1) value = 1;
    m_amp_r = value;
    updateSize();
}

void QNavWidget::setValueAmpScale(float value) {
    m_amp_scale = value;
    updateSize();
}

void QNavWidget::setValuePointer(float value) {
    m_pointer_value = fabsf(fmodf(value, 1));
    updateSize();
}

float QNavWidget::valueAmpL() {
    return m_amp_l;
}

float QNavWidget::valueAmpR() {
    return m_amp_r;
}

float QNavWidget::valueAmpScale() {
    return m_amp_scale;
}

float QNavWidget::valuePointer() {
    return m_pointer_value;
}

void QNavWidget::setStrings(const QStringList& list) {
    if (list.size() > TEXT_ITEM_COUNT) 
        m_strings = list.mid(0, TEXT_ITEM_COUNT);
    else 
        m_strings = list;
    updateSize();
}

QStringList QNavWidget::strings() const {
    return m_strings;
}
