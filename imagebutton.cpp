#include "imagebutton.h"

ImageButton::ImageButton(QWidget *parent) : QPushButton(parent)
{
    m_isPressing = false;
    m_pPressingTimer = new QTimer(this);
    connect(m_pPressingTimer,&QTimer::timeout,this,&ImageButton::onPressingTimerEvent);
}

void ImageButton::mousePressEvent(QMouseEvent *event)
{
    m_pPressingTimer->start(200);
    m_pressingStartTime = QTime::currentTime();
    //调用父控件的mousePressEvent，将其交给父控件
    QWidget::mousePressEvent(event);
}

void ImageButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_pPressingTimer->isActive())
        m_pPressingTimer->stop();
    QWidget::mouseReleaseEvent(event);
}

void ImageButton::onPressingTimerEvent()
{
    QTime currentTime = QTime::currentTime();
    int during = m_pressingStartTime.msecsTo(currentTime);
    if(during > 1400)
    {
        emit longPressAppButtonSignal();
        if(m_pPressingTimer->isActive())
            m_pPressingTimer->stop();
    }
}
