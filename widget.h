/***************************************************************************
**                                                                        **
**                                                                        **
**  Copyright (C) 2020-  YuXinhong                                        **
**                                                                        **
**  This program is commpany software                                     **
**  Total 3 Zone                                                          **
**  1.Broadband detection garpics area:the sonal broadband processing     **
**  results can be displayed in azimuth-amplitude diagram(A_type display) **
**  ,short integration or long integration) and azimuth-time history-lumi **
**  nace diagram(B-type Display)waterfall chart.real-time label display of**
**  tracking target                                                       **
**                                                                        **
**                                             .                          **
**                                                                        **
**                                                                        **
**                                                                    .   **
**                                                                        **
****************************************************************************
**           Author: YuXinhong                                            **
**           dateStart:2020/10/14                                         **
**                                                                        **
**                                                                        **
**                                                                        **
****************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>//udp传输头文件
#include <qcustomplot.h>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void PositionExtent();
    void setupWaterfall();
//    void AnimalGroup();
protected:
    void mousePressEvent(QMouseEvent * event);
    bool eventFilter(QObject *obj,QEvent *event);//事件处理器
private:
    Ui::Widget *ui;
    QCPItemText *textLabel;//单击时提示信息框
    QCPItemLine *arrow;//提示信息的箭头
    QButtonGroup *BtnGroup;
    QButtonGroup *BtnAnimalGroup;
    QString labeltext;
    QList<QVector<double>> colormapdata;
    bool yaxisChange;
    int timeClockCount;
};
#endif // WIDGET_H
