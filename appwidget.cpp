#include "appwidget.h"

#define APPBUTTON_WIDTH 80
#define APPBUTTON_HEIGHT 115
#define IMAGEBUTTON_WIDTH 70
#define IMAGEBUTTON_HEIGHT 70
#define DELETEBUTTON_WIDTH 20
#define DELETEBUTTON_HEIGHT 20

AppWidget::AppWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(QSize(APPBUTTON_WIDTH,APPBUTTON_HEIGHT));
    loadAppWidget();
    m_aniStatus = 0;
}

void AppWidget::SetAppImage(const QString &imgUrl)
{
    m_pAppButton->setIcon(QIcon(imgUrl));
}

void AppWidget::SetTitle(const QString &titleNmae)
{
    m_pTitleLabel->setText(titleNmae);
}

void AppWidget::SetDeleteButtonHidden(bool flag)
{
    if(m_pDeleteButton->isHidden() == flag)
        return;
    m_pDeleteButton->setHidden(flag);
}

void AppWidget::ShowAnimationOnWidget()
{
    int moveX = -1;
    int moveY = -1;

    if(m_aniStatus)
    {
        moveX = -1;
        moveY = -1;
        m_aniStatus = !m_aniStatus;
    }
    else
    {
        moveX = -1;
        moveY = 1;
        m_aniStatus = !m_aniStatus;
    }
    m_pSubjectWidget->move(moveX,moveY);
}

void AppWidget::loadAppWidget()
{
    m_pSubjectWidget = new QWidget(this);
    m_pSubjectWidget->move(0,0);
    m_pSubjectWidget->setFixedSize(APPBUTTON_WIDTH,APPBUTTON_HEIGHT);
    m_pSubjectWidget->setAttribute(Qt::WA_StyledBackground);
    m_pSubjectWidget->setStyleSheet("background-color: rgba(0,0,0,0)");

    m_pAppButton = new ImageButton(m_pSubjectWidget);
    connect(m_pAppButton,&ImageButton::longPressAppButtonSignal,this,&AppWidget::LongPressShowDeleteButtonSignal);
    m_pAppButton->move(10,10);
    m_pAppButton->setFixedSize(QSize(IMAGEBUTTON_WIDTH,IMAGEBUTTON_HEIGHT));
    m_pAppButton->setIconSize(QSize(IMAGEBUTTON_WIDTH,IMAGEBUTTON_HEIGHT));
    m_pAppButton->setFlat(true);
    m_pAppButton->setAttribute(Qt::WA_StyledBackground);
    m_pAppButton->setStyleSheet("background-color: rgba(0,0,0,0)");

    m_pTitleLabel = new QLabel(m_pSubjectWidget);
    m_pTitleLabel->setGeometry(0,APPBUTTON_HEIGHT - 20,APPBUTTON_WIDTH,20);
    m_pTitleLabel->setFont(QFont("Arial",15,50));
    m_pTitleLabel->setAttribute(Qt::WA_StyledBackground);
    m_pTitleLabel->setStyleSheet("background-color: rgba(0,0,0,0)");
    m_pTitleLabel->setAlignment(Qt::AlignCenter);
    m_pTitleLabel->setText("");

    m_pDeleteButton = new QPushButton(m_pSubjectWidget);
    connect(m_pDeleteButton,&QPushButton::clicked,this,[this](){
        emit deleteAppWidgetSignal(this);
    });
    m_pDeleteButton->move(0,0);
    m_pDeleteButton->setFixedSize(QSize(DELETEBUTTON_WIDTH,DELETEBUTTON_HEIGHT));
    m_pDeleteButton->setIcon(QIcon(":/ImageResources/delete_item.png"));
    m_pDeleteButton->setIconSize(QSize(DELETEBUTTON_WIDTH,DELETEBUTTON_HEIGHT));
    m_pDeleteButton->setAttribute(Qt::WA_StyledBackground);
    m_pDeleteButton->setStyleSheet("QPushButton{background:transparent;}");
    m_pDeleteButton->setHidden(true);
    m_pAppButton->setFlat(true);
}
