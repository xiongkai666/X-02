#include "mwaveview.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <chrono>
#include "controlwindow.h"

static QColor chColor[16] = {
    QColor (255, 228, 16),
    QColor (0, 225, 255),
    QColor (255, 20, 255),
    QColor (0, 23, 255),
    QColor (127, 255, 0),
    QColor (255, 0, 255),
    QColor (147, 112, 219),
    QColor (0, 255, 255),
    QColor (0, 0, 128),
    QColor (128, 0, 128),
    QColor (46, 139, 87),
    QColor (152, 251, 152),
    QColor (0, 255, 127),
    QColor (0, 0, 255),
    QColor (135, 206, 250),
    QColor (255, 192, 203),
};


// 构造函数
MWaveView::MWaveView(QWidget *parent) : QChartView(parent)
{

    this->wave_layout = new QBoxLayout(QBoxLayout::LeftToRight,parent);
    // set Axis------------------
    this->m_wave.axisX = new QValueAxis;
    this->m_wave.axisY = new QValueAxis;
    this->m_wave.axisX->setTickCount(9);
    this->m_wave.axisY->setTickCount(9);
    this->m_wave.axisX->setLabelFormat("%d");
    this->m_wave.axisY->setLabelFormat("%d");

    this->m_wave.axisX->setTickType(QValueAxis::TickType::TicksFixed);

    this->m_wave.axisX->setRange(0, 100);
    this->m_wave.axisY->setRange(-10, 310);

    // set chart-----------------
    this->m_wave.chart = new QChart;
    this->m_wave.chart->legend()->setVisible(false);
    this->m_wave.chart->setTheme(QChart::ChartThemeLight);
    this->setChart(this->m_wave.chart);

    this->m_wave.chart->addAxis(this->m_wave.axisX, Qt::AlignBottom);
    this->m_wave.chart->addAxis(this->m_wave.axisY, Qt::AlignLeft);

    // 隐藏X轴及其刻度和线
    this->m_wave.axisX->setLinePen(QPen(Qt::transparent));
    this->m_wave.axisX->setLabelsVisible(true);
    this->m_wave.axisX->setGridLineVisible(false);
    this->m_wave.axisX->setTickCount(6);
    this->m_wave.axisX->setLabelFormat("%d0ms");


    this->m_wave.axisY->setVisible(false);


    this->setRenderHint(QPainter::Antialiasing, true);      //反走样

    // 添加通道，初始化通道的线-------------
    for (int i = 0; i < SET_GLOBLE_CHANNEL; i++){
        addChannel((WAVE_CH)i);
        addChannel((IMPEDANCE_CH)i);
    }


    // 初始化部分参数-----------------
    m_wave.rangeX = 100;
    m_wave.rangeY = 100;
    this->m_wave.multipleX = 0.5;
    this->m_wave.multipleY = 0.5;
    this->m_event.rightButtonPressed = false;
    this->m_event.pauseWave = false;

    // menu--------------------
    this->m_event.menu = new QMenu(this);

    this->m_event.startAction = new QAction("开始",this);
    this->m_event.pauseAction = new QAction("暂停",this);
    this->m_event.startAction->setVisible(false);

    this->m_event.menu->addAction(this->m_event.startAction);
    this->m_event.menu->addAction(this->m_event.pauseAction);

    // 实现自动反转action
    connect(m_event.startAction, &QAction::triggered, [=] {
        m_event.startAction->setVisible(false);
        m_event.pauseAction->setVisible(true);});
    connect(m_event.pauseAction, &QAction::triggered, [=] {
        m_event.pauseAction->setVisible(false);
        m_event.startAction->setVisible(true);});

    // 信号与槽
    connect(m_event.pauseAction, &QAction::triggered, this, &MWaveView::slots_pauseGraph);
    connect(m_event.startAction, &QAction::triggered, this, &MWaveView::slots_startGraph);

}

MWaveView::~MWaveView()
{

}


void MWaveView::addChannel(int ch)
{
    SeriesType *series = new SeriesType();

    QPen pen;
    pen.setWidth(2);          // 设置线的宽度
    pen.setColor(chColor[ch]);   // 设置颜色
    series->setPen(pen);
    series->setUseOpenGL(true);  // 开启OPENGL

    // 添加进map
    this->m_wave.map_series.insert(ch,series);
    // 在chart中add series
    this->m_wave.chart->addSeries(this->m_wave.map_series[ch]);
    // 把线对应轴
    this->m_wave.map_series[ch]->attachAxis(m_wave.axisX);
    this->m_wave.map_series[ch]->attachAxis(m_wave.axisY);
}

//调用打开通道图像
void MWaveView::openChannel(int ch)
{
    if (this->m_wave.map_series.contains(ch))
    {
        this->m_wave.map_series[ch]->setVisible(true);
    }
}


// 调用关闭通道图像

void MWaveView::closeChannel(int ch)
{
    if (this->m_wave.map_series.contains(ch))
    {
        this->m_wave.map_series[ch]->setVisible(false);
    }
}
void MWaveView::clearChannel(int ch)
{
    if (this->m_wave.map_series.contains(ch))
    {
        this->m_wave.map_series[ch]->clear();
    }
}
// 设置范围
void MWaveView::setRangeX(int rangeX)
{
    this->m_wave.rangeX = rangeX;
}
// 设置范围
void MWaveView::setRangeY(int rangeY)
{
    this->m_wave.rangeY = rangeY;
}

void MWaveView::updateRange()
{
    double maxX,minX;
    double maxY,minY;

    maxX = m_wave.last_point_x > m_wave.rangeX? m_wave.last_point_x:m_wave.rangeX;
    minX = maxX - m_wave.rangeX >0 ? maxX - m_wave.rangeX: 0;

    maxY = 300;
    minY = -10;

    this->m_wave.axisX->setRange(minX, maxX);
    this->m_wave.axisY->setRange(minY, maxY);
}

// 设置放大倍数
void MWaveView::setZoomX(double multiple)
{
    if (multiple > 0){
        this->m_wave.multipleX = multiple;
    }
}
// 设置放大倍数
void MWaveView::setZoomY(double multiple)
{
    if (multiple > 0){
        this->m_wave.multipleY = multiple;
    }
}

void MWaveView::ZoomOutX(void)
{
    double zoom_out = 1.0/this->m_wave.multipleX;

    this->m_wave.rangeX *= zoom_out;

}

void MWaveView::ZoomX(void)
{   
    this->m_wave.rangeX *= this->m_wave.multipleX;
}

void MWaveView::ZoomOutY(void)
{
    double zoom_out = 1.0/this->m_wave.multipleY;

    this->m_wave.rangeY *= zoom_out;
}
void MWaveView::ZoomY(void)
{
    this->m_wave.rangeY *= this->m_wave.multipleY;
}

void MWaveView::startGraph(void)
{
    this->m_event.pauseWave = false;
}
void MWaveView::pauseGraph(void)
{
    this->m_event.pauseWave = true;
}

void MWaveView::slots_startGraph(void)
{
    startGraph();

}
void MWaveView::slots_pauseGraph(void)
{
    pauseGraph();
}

/*
void MWaveView::addSeriesData(int ch, const QPointF& point)
{

    if (this->m_event.pauseWave == true) return;

    if (this->m_wave.map_series.contains(ch))
    {
        this->m_wave.map_series[ch]->append(point);
    }
}
*/
void MWaveView::addSeriesData(int ch, const QList<QPointF>& point_list)
{
    static double x;

    if (this->m_event.pauseWave == true) return;

    if (this->m_wave.map_series.contains(ch))
    {
        this->m_wave.map_series[ch]->replace(point_list);

        if (point_list.count()){
            x = point_list[point_list.count()-1].x();
            m_wave.last_point_x = x > m_wave.last_point_x? x: m_wave.last_point_x;
        }
        else{
            m_wave.last_point_x = 0;
        }

        updateRange();
    }
}

void MWaveView::mousePressEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        this->m_event.leftButtonPressed = true;
        this->m_event.PressedPos = pEvent->pos();
        this->setCursor(Qt::OpenHandCursor);
    }
}

void MWaveView::mouseReleaseEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        this->m_event.leftButtonPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
}

void MWaveView::mouseMoveEvent(QMouseEvent *pEvent)
{
    if (m_event.leftButtonPressed)
    {
        QPoint oDeltaPos = pEvent->pos() - m_event.PressedPos;

        m_wave.chart->scroll(-oDeltaPos.x(), oDeltaPos.y());

        QPointF pos = m_wave.chart->mapToValue(pEvent->pos()) - m_wave.chart->mapToValue(m_event.PressedPos);

        m_event.moveX += -pos.x();
        m_event.moveY += -pos.y();

        m_event.PressedPos = pEvent->pos();
    }

    for (int ch = 0; ch < SET_GLOBLE_CHANNEL; ch++)
    {
        if (this->m_wave.map_series.contains(ch))
        {
            QLineSeries *series = this->m_wave.map_series[ch];
            const QVector<QPointF>& points = series->pointsVector();

            for (const QPointF& point : points)
            {
                QPointF pointInView = this->m_wave.chart->mapToPosition(point, series);
                QRectF pointRect(pointInView.x() - 5, pointInView.y() - 5, 10, 10);
                if (pointRect.contains(pEvent->pos()))
                {
                    QString str = '(' + QString::number(point.x()) + ',' + QString::number(point.y()) + ')';
                    QToolTip::showText(pEvent->globalPos(), str);
                    return;
                }
            }
        }
    }

    QToolTip::hideText();
}



void MWaveView::wheelEvent(QWheelEvent *pEvent)
{
    double multipleX, multipleY;
    if (this->m_event.pauseWave == false){

        QRectF oPlotAreaRect = m_wave.chart->plotArea();
        QPointF oCenterPoint = oPlotAreaRect.center();

        if (pEvent->delta()<0){
            multipleX = this->m_wave.multipleX;
            multipleY = this->m_wave.multipleY;
            ZoomOutX();
            ZoomOutY();
        }
        else
        {
            multipleX = 1/this->m_wave.multipleX;
            multipleY = 1/this->m_wave.multipleY;
            ZoomX();
            ZoomY();
        }

        oPlotAreaRect.setWidth(oPlotAreaRect.width() * multipleX);
        oPlotAreaRect.setHeight(oPlotAreaRect.height() * multipleY);
        QPointF oNewCenterPoint((2*oCenterPoint - pEvent->pos()) - (oCenterPoint - pEvent->pos()) / ((multipleX+multipleY)*0.5));
        oPlotAreaRect.moveCenter(oNewCenterPoint);
        QPointF movepos =  m_wave.chart->mapToValue(oNewCenterPoint) - m_wave.chart->mapToValue(oCenterPoint);
        m_event.moveY += movepos.ry();
        this->m_wave.chart->zoomIn(oPlotAreaRect);
    }
}

void MWaveView::contextMenuEvent(QContextMenuEvent *event)
{
    m_event.menu->move(cursor().pos());
    m_event.menu->show();
}






