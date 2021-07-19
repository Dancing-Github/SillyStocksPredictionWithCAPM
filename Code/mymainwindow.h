
#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QString>
#include <QtCharts/QtCharts>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include "Capm.h"
#include "candlestickdatareader.h"
#include "form.h"
#include "CandleSeries.h"
#include "CandlestickSet.h"
#include <SQLiteDB.h>
#include<spider.h>
#include<dialogk.h>
#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE
std::string const static IDsOfGP = "000001 000002 000004 000005 000006 000007 000008 000009 000010 000011 000012 000014 000016 000017 000063 000725 002230 002415 300750 600519 688981";
std::string const static TimeOfBegin="20171001";

//股票分析系统的主界面类
class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    void update();//更新所有股票的数据的函数
    void initialize();//初始化所有股票的数据的函数
    void analysis(QString);//分析单个股票的函数
    void kGraph(QString);//展现单个股票的k线图的函数
    QString getGP(QString);//获取用户要分析的股票的编号的函数
    std::string showResult(qreal);//返回分析结果的函数

private:
    Ui::MyMainWindow *ui;

};


//输入股票编号，如000001，自动 初始化 数据以及分析
bool InitializeGP(const std::string& IDsToInitialize);

//输入股票编号，如000001，自动 更新 数据以及分析
bool UpdateGP(const std::string IDsToUpdate);


#endif // MYMAINWINDOW_H
