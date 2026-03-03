#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "imagebutton.h"

class AppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget *parent = nullptr);
    void SetAppImage(const QString &imgUrl);
    void SetTitle(const QString &titleNmae);
    void SetAppIndex(int index);
    void SetDeleteButtonHidden(bool flag);
    void ShowAnimationOnWidget();
private:
    void loadAppWidget();
    int m_nAppIndex;
    bool m_aniStatus;

private:
    QWidget* m_pSubjectWidget;
    ImageButton* m_pAppButton;
    QLabel* m_pTitleLabel;
    QPushButton* m_pDeleteButton;
signals:
    void LongPressShowDeleteButtonSignal();
};

#endif // APPWIDGET_H
