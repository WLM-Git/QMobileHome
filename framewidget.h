#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include "appwidget.h"

class FrameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FrameWidget(QWidget *parent = nullptr);
    void HideAllDeleteButtons();
    void ShowAllDeleteButtons();
    void IsShowingDelBtnTrigger(bool isShowing);
    void ShowAnimatingAfterLongPress();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void createNewAppButton(QString filePath);
    void refreshAppsAlignment();


private:
    QPointF m_lastMousePos;
    QList<AppWidget*> m_AppWidgetList;
    bool m_bShowingDeleteBtn;

signals:
    void mouseMoveDistanceOnStackFrame(float);
    void mouseReleaseOnStackFrame();
    void LongPressShowAllDeleteButtonSignal();
};

#endif // FRAMEWIDGET_H
