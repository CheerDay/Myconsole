#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QTime>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,labeltext("nihnaiohnvui")
    ,yaxisChange(false)
    ,timeClockCount(0)
{
    //初始化
    ui->setupUi(this);
    QTimer *ReflashTime = new QTimer(this);
//    QTimer *waterfall = new QTimer(this);
    connect(ReflashTime,SIGNAL(timeout()),this,SLOT(PositionExtent()));
//    connect(waterfall,SIGNAL(timeout()),this,SLOT(setupWaterFall()));
    ReflashTime->start(1000);
    startTimer(1000, Qt::CoarseTimer);//每30ms触发一次timeEvent事件

//    waterfall->start(1000);
//    setupWaterFall();
    //radiobutton的group方式调用
    ui->PositionExtent->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::PositionExtent()
{

    //添加一个图层，并设置画笔和填充的颜色
    QCustomPlot *customplot = ui->PositionExtent;
    customplot->addGraph();
    customplot->graph(0)->setPen(QPen(Qt::red));
    customplot->graph(0)->setBrush(QBrush(QColor(0,255,0,20)));

    QVector<double> x_data(90,0.0);
    QVector<double> y_data1(90,0.0);
    for(int i=0;i<90;i++){
        x_data[i] = i;
        y_data1[i] = sin(i)*QRandomGenerator::global()->bounded(100.3);
//        y_data1[i] = cos(i);

    }
    //在将数据存入容器
    if(colormapdata.size()<90)
    {
        colormapdata.prepend(y_data1);
    }else{
        yaxisChange = true;
        timeClockCount++;
        colormapdata.removeLast();
        colormapdata.prepend(y_data1);
    }
    //设置坐标轴相关内容
    customplot->xAxis2->setVisible(true);
    customplot->xAxis2->setTickLabels(false);
    customplot->yAxis2->setVisible(true);
    customplot->yAxis2->setTickLabels(false);
    customplot->xAxis->setLabel("角度范围");
    customplot->yAxis->setLabel("幅值");

    customplot->graph(0)->setData(x_data,y_data1);
     //自动调整XY轴的范围
    customplot->graph(0)->rescaleAxes(1);

    customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customplot->replot();
    customplot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));
    customplot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    customplot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    textLabel = new QCPItemText(ui->PositionExtent);
    textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5,0.2);
    textLabel->setFont(QFont(font().family(),16));
    textLabel->setPen(QPen(Qt::black));
    textLabel->setText(labeltext);
    setupWaterfall();

    //利用上述数据画瀑布图
    //具体思路，先使用一个容器，保存这次生成的数据，然后有两种想法要试验一下1.从头部新增数据，读取的时候每次都是从头部开始读取
    //2.从尾部读取数据，新增的时候从读取范围内的数据

//    QCustomPlot *ColorMap = ui->PositionTime;
//    QCPColorMap *ColorMapData = new QCPColorMap(ColorMap->xAxis,ColorMap->yAxis);
//    ColorMapData->data()->setSize()
//    QCPAxis *yAxis = ColorMap->axisRect(1)->axis(QCPAxis::atLeft);  // 左轴


}

//void Widget::setupWaterFall()
//{

//       QVector<QString> hours = {"12a", "1a", "2a", "3a", "4a", "5a", "6a",
//               "7a", "8a", "9a","10a","11a",
//               "12p", "1p", "2p", "3p", "4p", "5p",
//               "6p", "7p", "8p", "9p", "10p", "11p"};
//       QVector<QString> days = {"Saturday", "Friday", "Thursday",
//               "Wednesday", "Tuesday", "Monday", "Sunday"};

//       QVector<QVector<double>> data = {{0,0,5},{0,1,3},{0,2,6},{0,3,0},{0,4,0},{0,5,0},{0,6,0},{0,7,0},{0,8,0},{0,9,0},{0,10,0},{0,11,2},{0,12,4},{0,13,1},{0,14,1},{0,15,3},{0,16,4},{0,17,6},{0,18,4},
//                               {0,19,4},{0,20,3},{0,21,3},{0,22,2},{0,23,5},{1,0,7},{1,1,0},{1,2,0},{1,3,0},{1,4,0},{1,5,0},{1,6,0},{1,7,0},{1,8,0},{1,9,0},{1,10,5},{1,11,2},{1,12,2},{1,13,6},{1,14,9},{1,15,11},
//                               {1,16,6},{1,17,7},{1,18,8},{1,19,12},{1,20,5},{1,21,5},{1,22,7},{1,23,2},{2,0,1},{2,1,1},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0},{2,7,0},{2,8,0},{2,9,0},{2,10,3},{2,11,2},{2,12,1},
//                               {2,13,9},{2,14,8},{2,15,10},{2,16,6},{2,17,5},{2,18,5},{2,19,5},{2,20,7},{2,21,4},{2,22,2},{2,23,4},{3,0,7},{3,1,3},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,1},
//                               {3,9,0},{3,10,5},{3,11,4},{3,12,7},{3,13,14},{3,14,13},{3,15,12},{3,16,9},{3,17,5},{3,18,5},{3,19,10},{3,20,6},{3,21,4},{3,22,4},{3,23,1},{4,0,1},{4,1,3},{4,2,0},{4,3,0},{4,4,0},
//                               {4,5,1},{4,6,0},{4,7,0},{4,8,0},{4,9,2},{4,10,4},{4,11,4},{4,12,2},{4,13,4},{4,14,4},{4,15,14},{4,16,12},{4,17,1},{4,18,8},{4,19,5},{4,20,3},{4,21,7},{4,22,3},{4,23,0},{5,0,2},
//                               {5,1,1},{5,2,0},{5,3,3},{5,4,0},{5,5,0},{5,6,0},{5,7,0},{5,8,2},{5,9,0},{5,10,4},{5,11,1},{5,12,5},{5,13,10},{5,14,5},{5,15,7},{5,16,11},{5,17,6},{5,18,0},{5,19,5},{5,20,3},{5,21,4},
//                               {5,22,2},{5,23,0},{6,0,1},{6,1,0},{6,2,0},{6,3,0},{6,4,0},{6,5,0},{6,6,0},{6,7,0},{6,8,0},{6,9,0},{6,10,1},{6,11,0},{6,12,2},{6,13,1},{6,14,3},{6,15,4},{6,16,0},{6,17,0},{6,18,0},
//                               {6,19,0},{6,20,1},{6,21,2},{6,22,2},{6,23,6}};
//       for(int i=0;i<24;i++)
//       {
//           data.append({0,1,QRandomGenerator::global()->bounded(9.5)});
//       }
//        QCustomPlot *TAngle = ui->PositionTime;
//        //创建一个colormap
//        QCPColorMap *timeAngle = new QCPColorMap(TAngle->xAxis, TAngle->yAxis);
//        //设置key value size
//        timeAngle->data()->setSize(hours.size(), days.size());
//        //设置范围
//        timeAngle->data()->setRange(QCPRange(0.5, hours.size() - 0.5), QCPRange(0.5, days.size() - 0.5));

//        // 设置轴的显示，这里使用文字轴，如果这部分还不会的请看 QCustomPlot之个性化外观（二）这章节
//        QSharedPointer<QCPAxisTickerText> xTicker(new QCPAxisTickerText);
//        QSharedPointer<QCPAxisTickerText> yTicker(new QCPAxisTickerText);
////        xTicker->setTicks(labelPositions(hours, 0.5), hours);
////        yTicker->setTicks(labelPosi。3tions(days, 0.5), days);
//        xTicker->setSubTickCount(1);
//        yTicker->setSubTickCount(1);

////        TAngle->xAxis->setTicker(xTicker);
////        TAngle->yAxis->setTicker(yTicker);
//        TAngle->yAxis->setVisible(true);
//        TAngle->xAxis2->setTicker(xTicker);
//        TAngle->xAxis2->setVisible(true);
//        TAngle->xAxis->setVisible(false);

//        TAngle->xAxis->grid()->setPen(Qt::NoPen);
//        TAngle->yAxis->grid()->setPen(Qt::NoPen);
//        TAngle->xAxis->grid()->setSubGridVisible(true);
//        TAngle->yAxis->grid()->setSubGridVisible(true);
//        TAngle->xAxis->setSubTicks(true);
//        TAngle->yAxis->setSubTicks(true);
//        TAngle->xAxis->setTickLength(0);
//        TAngle->yAxis->setTickLength(0);
//        TAngle->xAxis->setSubTickLength(6);
//        TAngle->yAxis->setSubTickLength(6);
//        TAngle->xAxis->setRange(0, hours.size());
//        TAngle->yAxis->setRange(0, days.size());

//        for (int x = 0; x < hours.size(); ++x) {
//            for (int y = 0; y < days.size(); ++y) {
//                int z = data.at(hours.size() * y + x).at(2)*QRandomGenerator::global()->bounded(3.14);
//                if (z) timeAngle->data()->setData(x, y, z);     // 如果z不为0，则设置颜色值的位置
//                else timeAngle->data()->setAlpha(x, y, 0);  // z为0，设置为透明
//            }
//        }
//        QCPColorScale *colorScale = new QCPColorScale(TAngle);  // 构造一个色条
//        colorScale->setType(QCPAxis::atBottom);   // 水平显示
//        TAngle->plotLayout()->addElement(1, 0, colorScale); // 在颜色图下面显示
//        timeAngle->setColorScale(colorScale);
//        QCPColorGradient gradient;  // 色条使用的颜色渐变
//        gradient.setColorStopAt(0.0, QColor("#f6efa6"));   // 设置色条开始时的颜色
//        gradient.setColorStopAt(1.0, QColor("#bf444c"));  // 设置色条结束时的颜色
//        timeAngle->setGradient(gradient);
////        timeAngle->rescaleDataRange();        // 自动计算数据范围，数据范围决定了哪些数据值映射到QCPColorGradient的颜色渐变当中
//        timeAngle->setDataRange(QCPRange(0, 10));     // 为了保持与echart的例子一致，我们这里手动设置数据范围
////        timeAngle->setTightBoundary(true);         // 为了显示小方块，我们禁用插值

//        // 保持色条与轴矩形边距一致
//        QCPMarginGroup *marginGroup = new QCPMarginGroup(TAngle);
//        TAngle->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
//        colorScale->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
//        TAngle->replot();

//}

void Widget::mousePressEvent(QMouseEvent * event)
{

}

//事件过滤器
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->PositionExtent){
        if(event->type() == QMouseEvent::MouseButtonDblClick){
            qDebug() << "keypress";
            return true;
        }else {
            return false;
        }
    }else{
        return Widget::eventFilter(obj,event);
    }
}


void Widget:: setupWaterfall()//显示Lofar瀑布图
{
    QCustomPlot *fp3 = ui->PositionTime; //创建一个画图指针
//    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    fp3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);//可拖拽+可滚轮缩放
   // fp3->axisRect()->insetLayout() ->setInsetAlignment(0,Qt::AlignRight|Qt::AlignTop); //图例置于右上
    /*
    Qt::AlignLeft|Qt::AlignTop); //图例置于左上
    Qt::AlignCenter|Qt::AlignTop);//图例置于中上
    Qt::AlignRight|Qt::AlignTop);//图例置于右上
    Qt::AlignLeft|Qt::AlignCenter);//图例置于左中
    Qt::AlignCenter);             //图例置于正中
    Qt::AlignRight|Qt::AlignCenter);//图例置于右中
    Qt::AlignLeft|Qt::AlignBottom);//图例置于左下
    Qt::AlignCenter|Qt::AlignBottom);//图例置于中下*/
   // fp3->legend->setVisible(true);//显示图例
    fp3->xAxis2->setVisible(true);
    fp3->xAxis->setVisible(false);
    fp3->xAxis2->setLabel("频率/Hz(单位:*10^4)");//x轴显示文字
    fp3->yAxis->setLabel("时间");//y轴显示文字
    fp3->yAxis->setRange(0,90);
    fp3->xAxis2->setRange(0,90);//当前x轴显示范围
//    if(yaxisChange == false)
//    {
//      fp3->yAxis->setRange(0,89);
//    }else{
//      fp3->yAxis->setRange(timeClockCount,89+timeClockCount);
//    }
    fp3->yAxis->setRangeReversed(true);
    qDebug() << yaxisChange;
    qDebug() << timeClockCount;
    qDebug() << colormapdata.size();
//    fp3->yAxis->setRange(key+0.25, 8);

    //每条曲线都会独占一个graph()
    fp3->addGraph();
    fp3->graph(0)->setPen(QPen(Qt::blue));//曲线颜色

    fp3->graph(0)->setBrush(QBrush(QColor(0,255,255,20)));//曲线与X轴包围区的颜色
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    //给第一个graph设置rescaleAxes()，后续所有graph都设置rescaleAxes(true)即可实现显示所有曲线
    fp3->graph(0)->rescaleValueAxis();
    //通过传递的轴的QCustomPlot进行注册,简洁理解QCPColorMap的数据为（x轴，y轴;颜色，值value）
    QCPColorMap *m_pColorMap = new QCPColorMap(fp3->xAxis2,fp3->yAxis);
    m_pColorMap->data()->setSize(90,90);//设置整个图（x,y）点数
    m_pColorMap->data()->setRange(QCPRange(0,90),QCPRange(0,90));

    for(int x=colormapdata.size()-1;x>0;x--)
    {
      for(int y=0;y<90;y++)
      {
          m_pColorMap->data()->setCell(y,x,colormapdata[x][y]);
      }
    }
//    m_pColorMap->data()->setRange(QCPRange(0,90),QCPRange(0,90));//setRange是设置X轴以及Y轴的范围
    //颜色范围 == 色条
   /* m_pColorScale = new QCPColorScale(fp3);
    fp3->plotLayout()->addElement(0,1,m_pColorScale);//默认右侧添加色彩图
    m_pColorScale->setType(QCPAxis::atRight);
    m_pColorScale->setDataRange(QCPRange(0, 100));//颜色范围对应的取值范围data_maxColorBar这里为测量得到的最大值来代表颜色的最大值
    m_pColorScale->axis()->ticker()->setTickCount(6);
    m_pColorScale->axis()->setLabel("色彩");//色条的名

   // m_pColorMap->setColorScale(m_pColorScale); //热图连接色条

    m_pColorMap->setGradient(QCPColorGradient::gpCold);//设置默认渐进色变化（可在QCPColorGradient中查看）
 // QSharedPointer<QCPColorGradient> colorLayout(new QCPColorGradient);//生成颜色渐进变化对象
    QMap<double, QColor> color_layout;
    m_pColorGradient = new QCPColorGradient();//自定义的渐进色变化对象
    //m_pColorGradient->setColorStops(colorLayout);//QMap<double, QColor> color_layout为;颜*色*布局范围(double取值为0，1)
    m_pColorMap->setGradient(*m_pColorGradient);//设置渐进色变化
    m_pColorMap->rescaleDataRange();

    QCPMarginGroup *marginGroup = new QCPMarginGroup(fp3);
    fp3->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    m_pColorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);*/

    //赋值操作
    m_pColorMap->setGradient(QCPColorGradient::gpJet);//设置默认渐进色变化（可在QCPColorGradient中查看）
    m_pColorMap->rescaleDataRange(true);

// 立即刷新图像
//    fp3->rescaleAxes();//自适应大小
    fp3->replot(QCustomPlot::rpQueuedReplot);

}


