#pragma once
#pragma execution_character_set("utf-8")
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QDateTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <string>
#include<cstring>
#include "CandlestickSet.h"

QT_CHARTS_USE_NAMESPACE

//用于展示k线图，存储一段时期内股票数据的CandlestickSeries系列
class CandleSeries :  public QCandlestickSeries
{
     Q_OBJECT
public:
    CandleSeries(QWidget *parent = Q_NULLPTR);

    //CandleSeries系列用于展示k线图，所需要对象
    QChart* chart = new QChart();
    QChartView* chartView = new QChartView(chart);
    QCandlestickSeries* gpSeries = new QCandlestickSeries();


    CandlestickSet* readCandlestickSet(int);//读取线性表数据并存值进CandlestickSet
    void printChart();//设置好CandleSeries系列的参数
    void getOpenList(std::string);//获取开盘价，并存储到openList
    void getHighList(std::string);//获取最高价，并存储到highList
    void getLowList(std::string);//获取最低价，并存储到lowList
    void getCloseList(std::string);//获取收盘价，并存储到closeList
    void getTimeList(std::string);//获取时间，并存储到timeList
    void setData();//创建相应CandlestickSet加入到CandleSeries系列中，并将数据加进去
    void setID(std::string);//获取股票名的函数


private:
    QString ID;//股票的名
    QList<QString> timeList;//存股票时间的线性表
    QList<double> openList;//存股票开盘价的线性表
    QList<double> closeList;//存股票收盘价的线性表
    QList<double> highList;//存股票最高价的线性表
    QList<double> lowList;//存股票最低价的线性表
    QStringList categories;
    CandlestickSet** set=new CandlestickSet*[1200];
};
