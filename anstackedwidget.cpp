#include "anstackedwidget.h"
#include <QPalette>
#define STACKWIDGET_WIDTH   375
#define STACKWIDGET_HEIGHT  750

ANStackedWidget::ANStackedWidget(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(30,55,STACKWIDGET_WIDTH,STACKWIDGET_HEIGHT);
    m_nCurrentIndex = 0;
    m_nNextIndex = 0;
    m_accMoveDistance = 0;

    int pageCount = 3;
    CreatePageWidgetWithCount(pageCount);

    m_pAnimateTimer = new QTimer(this);
    connect(m_pAnimateTimer,&QTimer::timeout,this,&ANStackedWidget::OnAnimationTimerEvent);

    m_pFinishButton = new QPushButton(this);
    m_pFinishButton->setGeometry(STACKWIDGET_WIDTH-85,0,80,30);
    m_pFinishButton->setIcon(QIcon(":/ImageResources/showDel_finished.png"));
    m_pFinishButton->setIconSize(QSize(80,30));
    m_pFinishButton->setAutoFillBackground(true);
    m_pFinishButton->setFlat(true);
    m_pFinishButton->setStyleSheet("QPushButton{background: transparent;}");
    m_pFinishButton->setHidden(true);

    connect(m_pFinishButton,&QPushButton::clicked,this,&ANStackedWidget::OnHideDeleteButton);
}

void ANStackedWidget::CreatePageWidgetWithCount(int count)
{
    if(count <= 0)
        return;

    for(int i = 0; i < count; i++)
    {
        FrameWidget* frameWidget = new FrameWidget(this);
        frameWidget->setGeometry(0,0,STACKWIDGET_WIDTH,STACKWIDGET_HEIGHT);
        connect(frameWidget,&FrameWidget::mouseMoveDistanceOnStackFrame,this,&ANStackedWidget::OnMouseMoveOnStackFrame);
        connect(frameWidget,&FrameWidget::mouseReleaseOnStackFrame,this,&ANStackedWidget::OnMouseReleaseOnStackFrame);
        connect(frameWidget,&FrameWidget::LongPressShowAllDeleteButtonSignal,this,&ANStackedWidget::OnLongPressShowAllDeleteButton);
        QPalette pal = frameWidget->palette();

        if(i == 0)
            frameWidget->setHidden(false);
        else
            frameWidget->setHidden(true);
        m_stackFrameList.append(frameWidget);
    }
}

int ANStackedWidget::getCount()
{
    return m_stackFrameList.count();
}

int ANStackedWidget::getCurrentIndex()
{
    return m_nCurrentIndex;
}

void ANStackedWidget::updateAndDrawAnimation(float moveX)
{
    //当前页面
    FrameWidget* currentFrameWidget = getCurrentWidget();
    //当前的下一个页面
    FrameWidget* nextFrameWidget = getWigetWithIndex(m_nNextIndex);

    nextFrameWidget->setHidden(false);

    if(m_accMoveDistance < 0 )
    {
        currentFrameWidget->move(currentFrameWidget->pos().x()+moveX,currentFrameWidget->pos().y());
        if(currentFrameWidget != nextFrameWidget)
            nextFrameWidget->move(STACKWIDGET_WIDTH-qAbs(m_accMoveDistance),0);
    }
    else
    {
        currentFrameWidget->move(currentFrameWidget->pos().x()+moveX,currentFrameWidget->pos().y());
        if(currentFrameWidget != nextFrameWidget)
            nextFrameWidget->move(qAbs(m_accMoveDistance) - STACKWIDGET_WIDTH,0);
    }
}

FrameWidget *ANStackedWidget::getCurrentWidget()
{
    FrameWidget* currentWidget = m_stackFrameList.at(m_nCurrentIndex);
    if(currentWidget != nullptr)
        return currentWidget;
    return nullptr;
}

FrameWidget *ANStackedWidget::getWigetWithIndex(int index)
{
    if(index < 0)
        return nullptr;
    if(index >= getCount())
        return nullptr;

    FrameWidget* framWidget = m_stackFrameList.at(index);
    if(framWidget != nullptr)
        return framWidget;
    return nullptr;
}

void ANStackedWidget::finishDrwAnimation()
{
    //设置新的当前页面
    setCurrentIndex(m_nNextIndex);
    //将m_accMoveDistance置0
    m_accMoveDistance = 0;
    m_nNextIndex = m_nCurrentIndex;
}

void ANStackedWidget::setCurrentIndex(int index)
{
    if(m_accMoveDistance>-60 && m_accMoveDistance<60)
    {
        for(int i = 0 ;i < m_stackFrameList.count();i++)
        {
            FrameWidget* frame = m_stackFrameList.at(i);
            if(frame != nullptr)
            {
                frame->setGeometry(0,0,STACKWIDGET_WIDTH,STACKWIDGET_HEIGHT);
                if(i == m_nCurrentIndex)
                    frame->setHidden(false);
                else
                    frame->setHidden(true);
            }
        }
        return;
    }
    //将index对应的页面设置为当前页面，其余页面均为不可见
    for(int i = 0 ;i < m_stackFrameList.count();i++)
    {
        FrameWidget* frame = m_stackFrameList.at(i);
        if(frame != nullptr)
        {
            frame->setGeometry(0,0,STACKWIDGET_WIDTH,STACKWIDGET_HEIGHT);
            if(i == index)
                frame->setHidden(false);
            else
                frame->setHidden(true);
        }
    }
    m_nCurrentIndex = index;
}

void ANStackedWidget::OnMouseMoveOnStackFrame(float diffPos)
{
    m_accMoveDistance += diffPos;

    //拿到总页数以及当前页数，对页数进行范围的判断
    int totalWidget = getCount();
    int stackWidgetIndex = getCurrentIndex();

    int oldNextIndex = m_nNextIndex;

    //根据滑动距离改变页面(stackWidgetIndex为潜在页面下标)
    if(m_accMoveDistance > 0)
    {
        stackWidgetIndex--;
    }
    else if(m_accMoveDistance < 0)
    {
        stackWidgetIndex++;
    }



    //对stackWidgetIndex进行判断以及使其符合范围要求
    if(stackWidgetIndex >= totalWidget)
    {
        stackWidgetIndex = totalWidget - 1;
    }
    else if(stackWidgetIndex < 0)
    {
        stackWidgetIndex = 0;
    }

    if(oldNextIndex != stackWidgetIndex)
    {
        for(int i = 0 ;i < m_stackFrameList.count();i++)
        {
            FrameWidget* frame = m_stackFrameList.at(i);
            if(frame != nullptr)
            {
                frame->setGeometry(0,0,STACKWIDGET_WIDTH,STACKWIDGET_HEIGHT);
                if(i == stackWidgetIndex || i == m_nCurrentIndex)
                    frame->setHidden(false);
                else
                    frame->setHidden(true);
            }
        }
    }

    m_nNextIndex = stackWidgetIndex;

    updateAndDrawAnimation(diffPos);
}

void ANStackedWidget::OnMouseReleaseOnStackFrame()
{
    finishDrwAnimation();
}

//显示所有App的删除按钮
void ANStackedWidget::OnLongPressShowAllDeleteButton()
{
    if(m_stackFrameList.count()<=0)
        return;
    //拿出每一个页面，并将其设置删除按钮抖动
    for(int i = 0;i<m_stackFrameList.count();i++)
    {
        FrameWidget* frameWidget = m_stackFrameList.at(i);
        if(frameWidget != nullptr)
        {
            //将frameWidget设置删除按钮显示
            frameWidget->ShowAllDeleteButtons();
            frameWidget->IsShowingDelBtnTrigger(true);
        }
    }
    if(m_pAnimateTimer != nullptr)
    {
        m_pAnimateTimer->start(100);
    }
    m_pFinishButton->setHidden(false);
}

void ANStackedWidget::OnAnimationTimerEvent()
{
    if(m_stackFrameList.count()<=0)
        return;
    for(int i = 0;i<m_stackFrameList.count();i++)
    {
        FrameWidget* frameWidget = m_stackFrameList.at(i);
        if(frameWidget!=nullptr)
        {
            frameWidget->ShowAnimatingAfterLongPress();
        }
    }
}

void ANStackedWidget::OnHideDeleteButton()
{
    if(m_stackFrameList.count()<=0)
        return;
    //拿出每一个页面，并将其设置删除按钮抖动
    for(int i = 0;i<m_stackFrameList.count();i++)
    {
        FrameWidget* frameWidget = m_stackFrameList.at(i);
        if(frameWidget != nullptr)
        {
            //将frameWidget设置删除按钮显示
            frameWidget->HideAllDeleteButtons();
            frameWidget->IsShowingDelBtnTrigger(false);
        }
    }
    if(m_pAnimateTimer != nullptr)
    {
        m_pAnimateTimer->stop();
    }
    m_pFinishButton->setHidden(true);
}

