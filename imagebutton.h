#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
//长按按钮发送信号，以供父控件将其抖动
class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    ImageButton(QWidget* parent = 0);
private:
    QTimer* m_pPressingTimer;
    bool m_isPressing;
    QTime m_pressingStartTime;

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void onPressingTimerEvent();
signals:
    void longPressAppButtonSignal();
};

#endif // IMAGEBUTTON_H
