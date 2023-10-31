#ifndef MWAVEVIEW_H
#define MWAVEVIEW_H

#include <QObject>
#include <QWidget>
#include <QChartView>
#include <QtCharts>
#include <QByteArray>
#include <QDebug>
#include "PionwayDLL.h"


// 定义最大通道数量
#define WAVE_CHANNEL_MAX  16
enum WAVE_CH
{
    WAVE_CH0,
    WAVE_CH1,
    WAVE_CH2,
    WAVE_CH3,
    WAVE_CH4,
    WAVE_CH5,
    WAVE_CH6,
    WAVE_CH7,
    WAVE_CH8,
    WAVE_CH9,
    WAVE_CH10,
    WAVE_CH11,
    WAVE_CH12,
    WAVE_CH13,
    WAVE_CH14,
    WAVE_CH15,
};

enum IMPEDANCE_CH
{
    IMPEDANCE_CH0,
    IMPEDANCE_CH1,
    IMPEDANCE_CH2,
    IMPEDANCE_CH3,
    IMPEDANCE_CH4,
    IMPEDANCE_CH5,
    IMPEDANCE_CH6,
    IMPEDANCE_CH7,
    IMPEDANCE_CH8,
    IMPEDANCE_CH9,
    IMPEDANCE_CH10,
    IMPEDANCE_CH11,
    IMPEDANCE_CH12,
    IMPEDANCE_CH13,
    IMPEDANCE_CH14,
    IMPEDANCE_CH15,
};

// 直线:  QLineSeries
// 平滑线  QSplineSeries
typedef QLineSeries SeriesType;

struct Wave
{
    QMap<int, SeriesType *> map_series;  //key: ch, value SeriesType *
    QChart *chart;  // 图纸
    QValueAxis *axisX, *axisY;   // xy轴
    double rangeX, rangeY;      // 控制XY的可视范围

    double multipleX, multipleY;   // 放大倍数，对应缩小倍数为1/multiple.
    double last_point_x = 0;
};

struct Event
{
    bool rightButtonPressed = false;
    bool leftButtonPressed = false;
    QPoint PressedPos;
    double moveX,moveY;  // 记录移动
    bool pauseWave;
    QMenu *menu;
    QAction* startAction;
    QAction* pauseAction;
};



class MWaveView:public QChartView
{
    Q_OBJECT
public:
    MWaveView(QWidget *parent);
    ~MWaveView();

    #define SET_GLOBLE_CHANNEL  16

    void openChannel(int ch);

    void closeChannel(int ch);

    void clearChannel(int ch);

    void addSeriesData(int ch, const QPointF& point);

    void addSeriesData(int ch, const QList<QPointF>& point_list);
    /*
    void openChannel(WAVE_CH ch);

    void openChannel(IMPEDANCE_CH ch);

    void closeChannel(WAVE_CH ch);

    void closeChannel(IMPEDANCE_CH ch);

    void clearChannel(WAVE_CH ch);

    void clearChannel(IMPEDANCE_CH ch);

    void addSeriesData(WAVE_CH ch, const QPointF& point);

    void addSeriesData(IMPEDANCE_CH ch, const QPointF& point);

    void addSeriesData(WAVE_CH ch, const QList<QPointF>& point_list);

    void addSeriesData(IMPEDANCE_CH ch, const QList<QPointF>& point_list);
    */

    // 设置X轴范围
    void setRangeX(int rangeX);
    // 设置Y轴范围
    void setRangeY(int rangeY);

    // 设置X轴范围放大倍数,默认1.2，不可为0，对应缩小为1/multiple
    void setZoomX(double multiple);
    // 设置Y轴范围放大倍数，默认1.2，不可为0，对应缩小为1/multiple
    void setZoomY(double multiple);

    // X轴范围按比例缩小
    void ZoomOutX(void);
    // X轴范围按比例放大
    void ZoomX(void);

    // Y轴范围按比例缩小
    void ZoomOutY(void);
    // Y轴范围按比例放大
    void ZoomY(void);

    // 波形开始
    void startGraph(void);
    // 波形暂停
    void pauseGraph(void);

    void moveWaveDown(int distance);

public slots:
    // 波形开始槽函数
    void slots_startGraph(void);
    // 波形暂停槽函数
    void slots_pauseGraph(void);
protected:
    // 事件重写
    virtual void mouseMoveEvent(QMouseEvent *pEvent) override;
    virtual void mousePressEvent(QMouseEvent *pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent *pEvent) override;
    virtual void wheelEvent(QWheelEvent *pEvent) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private:

    void addChannel(int ch);
    void getdata(int ch);
    /*
    void addChannel(WAVE_CH ch);
    void getdata(WAVE_CH ch);
    void addChannel(IMPEDANCE_CH ch);
    void getdata(IMPEDANCE_CH ch);
    */

    void updateRange(void);


    QBoxLayout *wave_layout;
    Wave m_wave;
    Event m_event;
};

#endif // MWAVEVIEW_H
