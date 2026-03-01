#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H
#include <QWidget>
#include "anstackedwidget.h"

class WindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = nullptr);
private:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void loadStackWidget();
private:
    QPixmap m_bgPixMap;
    QPointF m_lastMousePos;
    ANStackedWidget* m_pStackWidget;

signals:
};

#endif // WINDOWWIDGET_H
