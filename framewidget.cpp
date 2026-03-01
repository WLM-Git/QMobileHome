#include "framewidget.h"
#include <QMouseEvent>

FrameWidget::FrameWidget(QWidget *parent)
    : QWidget{parent}
{}

void FrameWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        m_lastMousePos = event->globalPosition();
}

void FrameWidget::mouseMoveEvent(QMouseEvent *event)
{
    //拿到鼠标运动位移
    float diffPos = event->globalPosition().x() - m_lastMousePos.x();
    m_lastMousePos = event->globalPosition();       //更新m_lastMousePos，使得diffPos为每时每刻运动的位移小增量

    emit mouseMoveDistanceOnStackFrame(diffPos);
}

void FrameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleaseOnStackFrame();
}
