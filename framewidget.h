#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>

class FrameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FrameWidget(QWidget *parent = nullptr);
private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPointF m_lastMousePos;

signals:
    void mouseMoveDistanceOnStackFrame(float);
    void mouseReleaseOnStackFrame();
};

#endif // FRAMEWIDGET_H
