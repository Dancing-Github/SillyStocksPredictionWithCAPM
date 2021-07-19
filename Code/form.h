#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QString>
#include <string>
#include <QLabel>
#include<SQLiteDB.h>
#pragma execution_character_set("utf-8")


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    QChartView* getChartView();//返回窗口里的QChartView*类型变量
    void showAnalysis();//展示分析结果的函数
    void setID(std::string);//获取股票名
    std::string showResult(qreal);//返回分析的结果
private:
    Ui::Form *ui;
    std::string ID;
};

#endif // FORM_H
