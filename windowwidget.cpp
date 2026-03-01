#include "windowwidget.h"
#include <QPainter>
#include <QScreen>
#include <QMouseEvent>

#define LANGCHERWIDGET_WIDTH 436
#define LANGCHERWIDGET_HEIGHT 859


WindowWidget::WindowWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);     //背景图片的周边透明部分被系统用纯色填充，使用这个方法可以让系统不对透明部分进行填充以达到背景图片周边透明的目的
    m_bgPixMap.load(":/ImageResources/background.png");

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    int StartX = (screenGeometry.width() - LANGCHERWIDGET_WIDTH)/2;
    int SatrtY = (screenGeometry.height() - LANGCHERWIDGET_HEIGHT)/2;

    setGeometry(StartX,SatrtY,LANGCHERWIDGET_WIDTH,LANGCHERWIDGET_HEIGHT);

    loadStackWidget();
}

void WindowWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawPixmap(rect(),m_bgPixMap);
}

void WindowWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_lastMousePos = event->globalPosition();
    }
}

void WindowWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF pos = this->pos() + event->globalPosition() - m_lastMousePos;
        this->move(pos.x(),pos.y());
        m_lastMousePos = event->globalPosition();
    }
}

void WindowWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void WindowWidget::loadStackWidget()
{
    m_pStackWidget = new ANStackedWidget(this);
}
