#ifndef ANSTACKEDWIDGET_H
#define ANSTACKEDWIDGET_H

#include <QWidget>
#include "framewidget.h"
#include <QTimer>
#include <QPushButton>

class ANStackedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ANStackedWidget(QWidget *parent = nullptr);
    void CreatePageWidgetWithCount(int count);
private:
    int getCount();
    int getCurrentIndex();
    void updateAndDrawAnimation(float moveX);
    FrameWidget* getCurrentWidget();
    FrameWidget* getWigetWithIndex(int index);
    void finishDrwAnimation();
    void setCurrentIndex(int);

private:
    QList<FrameWidget*> m_stackFrameList;
    int m_nCurrentIndex;
    int m_nNextIndex;
    float m_accMoveDistance;
    QTimer* m_pAnimateTimer;
    QPushButton* m_pFinishButton;
signals:
private slots:
    void OnMouseMoveOnStackFrame(float diffPos);
    void OnMouseReleaseOnStackFrame();
    void OnLongPressShowAllDeleteButton();
    void OnAnimationTimerEvent();
    void OnHideDeleteButton();
};

#endif // ANSTACKEDWIDGET_H
