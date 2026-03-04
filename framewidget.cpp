#include "framewidget.h"
#include <QMouseEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QHash>

#define APPBUTTON_WIDTH 80
#define APPBUTTON_HEIGHT 115

#define ALIGNMENT_X_BORDER 10
#define ALIGNMENT_Y_BORDER 30

FrameWidget::FrameWidget(QWidget *parent)
    : QWidget{parent}
{
    m_bShowingDeleteBtn = false;
    setAcceptDrops(true);
}

void FrameWidget::HideAllDeleteButtons()
{
    if(m_AppWidgetList.count()<=0)
        return;
    for(int i = 0;i<m_AppWidgetList.count();i++)
    {
        AppWidget* appWidget = m_AppWidgetList.at(i);
        if(appWidget!=nullptr)
        {
            //调用appWidget的显示删除按钮函数
            appWidget->SetDeleteButtonHidden(true);
        }
    }
}

void FrameWidget::ShowAllDeleteButtons()
{
    if(m_AppWidgetList.count()<=0)
        return;
    for(int i = 0;i<m_AppWidgetList.count();i++)
    {
        AppWidget* appWidget = m_AppWidgetList.at(i);
        if(appWidget!=nullptr)
        {
            //调用appWidget的显示删除按钮函数
            appWidget->SetDeleteButtonHidden(false);
        }
    }
}

void FrameWidget::IsShowingDelBtnTrigger(bool isShowing)
{
    m_bShowingDeleteBtn = isShowing;
}

void FrameWidget::ShowAnimatingAfterLongPress()
{
    if(m_AppWidgetList.count()<=0)
        return;
    for(int i = 0;i<m_AppWidgetList.count();i++)
    {
        AppWidget* appWidget = m_AppWidgetList.at(i);
        if(appWidget!=nullptr)
        {
            appWidget->ShowAnimationOnWidget();
        }
    }
}

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

void FrameWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //如果当前处于删除App模式，则不允许App拖入
    if(m_bShowingDeleteBtn == true)
        return;

    QString fileName = event->mimeData()->urls()[0].fileName();
    if(fileName.endsWith("jpg",Qt::CaseInsensitive)
        ||fileName.endsWith("jpeg",Qt::CaseInsensitive)||fileName.endsWith("png",Qt::CaseInsensitive))
        event->acceptProposedAction();      //允许拖进来
    else
        event->ignore();
}

void FrameWidget::dropEvent(QDropEvent *event)
{
    const QString filePath = event->mimeData()->urls()[0].toLocalFile();   //获取本地路径，如"E:\person\chenchao\costomWidget\QMobileHome\ImageResources\01.png"
    createNewAppButton(filePath);

    event->acceptProposedAction();
}

void FrameWidget::createNewAppButton(QString filePath)
{
    //生产一个AppWidget
    AppWidget* appWidget = new AppWidget(this);
    connect(appWidget,&AppWidget::LongPressShowDeleteButtonSignal,this,&FrameWidget::LongPressShowAllDeleteButtonSignal);
    appWidget->setGeometry(0,0,APPBUTTON_WIDTH,APPBUTTON_HEIGHT);
    appWidget->SetAppImage(filePath);


    QFileInfo fileInfo = QFileInfo(filePath);
    QString fileName = fileInfo.fileName();

    static const QHash<QString,QString> appNameMap =
    {
        {"01.png","谷歌地图"},
        {"02.png", "三国无双"},
        {"03.png", "百度网盘"},
        {"04.png", "火山视频"},
        {"05.png", "牛市彩票"},
        {"06.png", "猎豹浏览器"},
        {"07.png", "京东商城"},
        {"08.png", "天猫超市"},
        {"09.png", "网易股票"},
        {"10.png", "美团点评"},
        {"11.png", "迅雷下载"},
        {"12.png", "腾讯篮球"},
        {"13.png", "美颜相机"}
    };

    //设置App title
    QString title = appNameMap.value(fileName,"未知应用");
    appWidget->SetTitle(title);

    m_AppWidgetList.append(appWidget);
    //刷新app布局
    refreshAppsAlignment();
}

void FrameWidget::refreshAppsAlignment()
{
    if(m_AppWidgetList.count()<=0)
        return;
    //将每一个AppWidget重新放置位置
    for(int i = 0;i<m_AppWidgetList.count();i++)
    {
        AppWidget* appwidget = m_AppWidgetList.at(i);
        if(appwidget!=nullptr)
        {
            int XStep = i % 4;
            int YStep = i / 4;
            int XMove = ALIGNMENT_X_BORDER + XStep*(APPBUTTON_WIDTH + ALIGNMENT_X_BORDER);
            int YMove = ALIGNMENT_Y_BORDER + YStep*(APPBUTTON_HEIGHT + ALIGNMENT_Y_BORDER);
            appwidget->move(XMove,YMove);
            appwidget->setHidden(false);
        }
    }
}

