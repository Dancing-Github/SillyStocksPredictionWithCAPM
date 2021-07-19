#include "CandleSeries.h"


CandleSeries::CandleSeries(QWidget *parent )
    
{
    //初始化CandleSeries系列
    gpSeries->setIncreasingColor(QColor(Qt::red));
    gpSeries->setDecreasingColor(QColor(Qt::green));
    gpSeries->setUseOpenGL(true);
}

//获取股票名的函数
void CandleSeries::setID(std::string gpName)
{
    ID = QString::fromStdString(gpName);
    gpSeries->setName(ID);
}

//创建相应CandlestickSet加入到CandleSeries系列中，并将数据加进去
void CandleSeries::setData()
{
    int num=openList.size();
    for (int i=0; i <num ; i++)
    {
        categories << timeList[i];
        set[i] = readCandlestickSet(i);
        gpSeries->append(set[i]);

        connect(set[i],&QCandlestickSet::clicked,set[i],&CandlestickSet::getHovered);
        connect(set[i],&CandlestickSet::toHovered,[&](qreal qopen,qreal qhigh,qreal qlow,qreal qclose,qreal qidx)
        {
            QWidget * widget=new QWidget;

            QString open="开盘价: ";
            open+=QString::number(qopen);
            QString high="最高价: ";
            high+=QString::number(qhigh);
            QString low="最低价: ";
            low+=QString::number(qlow);
            QString close="收盘价: ";
            close+=QString::number(qclose);


            QLabel * labelopen=new QLabel(widget);
            labelopen->move(75,20);
            labelopen->setText(open);
            QLabel * labelhigh=new QLabel(widget);
            labelhigh->move(75,40);
            labelhigh->setText(high);
            QLabel * labellow=new QLabel(widget);
            labellow->move(75,60);
            labellow->setText(low);
            QLabel * labelclose=new QLabel(widget);
            labelclose->move(75,80);
            labelclose->setText(close);
            widget->setFixedSize(250,100);
            widget->setWindowTitle("股票数据");
            widget->setAttribute(Qt::WA_DeleteOnClose);
            widget->show();

        });
    }  
}

//读取线性表数据并存值进CandlestickSet
CandlestickSet* CandleSeries::readCandlestickSet(int i)
{

    CandlestickSet* candle = new CandlestickSet;
    candle->setOpen(openList[i]);
    candle->setHigh(highList[i]);
    candle->setLow(lowList[i]);
    candle->setClose(closeList[i]);
    candle->setTimestamp(i);
    return candle;
}

//设置好CandleSeries系列的参数
void CandleSeries::printChart()
{
    gpSeries->setBodyWidth(0.3);
    chart->addSeries(gpSeries);
    chart->setTitle("GP:"+ID);
    
    chart->createDefaultAxes();
    
    QBarCategoryAxis* axisX = qobject_cast<QBarCategoryAxis*>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);
    axisX->setLabelsAngle(45);

    QValueAxis* axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);
    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    
    chartView->setRenderHint(QPainter::Antialiasing);
}

//获取开盘价，并存储到openList
void CandleSeries::getOpenList(std::string data)
{
    const char delim[2] = " ";
    char* str;
    char* saveptr = NULL;
    str = strtok_s((char*)data.c_str(), delim, &saveptr);
    while (str != NULL)
    {
        QString t=str;
           openList.append(t.toDouble());
        str = strtok_s(NULL, delim, &saveptr);
    }




}

//获取最高价，并存储到highList
void CandleSeries::getHighList(std::string data)
{
    const char delim[2] = " ";
    char* str;
    char* saveptr = NULL;
    str = strtok_s((char*)data.c_str(), delim, &saveptr);
    while (str != NULL)
    {
        QString t=str;
           highList.append(t.toDouble());
        str = strtok_s(NULL, delim, &saveptr);

    }

}

//获取最低价，并存储到lowList
void CandleSeries::getLowList(std::string data)
{
    const char delim[2] = " ";
    char* str;
    char* saveptr = NULL;
    str = strtok_s((char*)data.c_str(), delim, &saveptr);
    while (str != NULL)
    {
        QString t=str;
           lowList.append(t.toDouble());
        str = strtok_s(NULL, delim, &saveptr);
    }




}

//获取收盘价，并存储到closeList
void CandleSeries::getCloseList(std::string data)
{
    const char delim[2] = " ";
    char* str;
    char* saveptr = NULL;
    str = strtok_s((char*)data.c_str(), delim, &saveptr);
    while (str != NULL)
    {
        QString t=str;
           closeList.append(t.toDouble());
        str = strtok_s(NULL, delim, &saveptr);
    }




}

//获取时间，并存储到timeList
void CandleSeries::getTimeList(std::string data)
{
     int counter = 0;
     QString tempstr;
    const char delim[2] = " ";
    char* str;
    char* saveptr = NULL;
    str = strtok_s((char*)data.c_str(), delim, &saveptr);
    while (str != NULL)
    {
        QString standardlize=str;
        if(standardlize.size()==1)
        {standardlize="0"+standardlize;}

        tempstr+=standardlize;
        switch (counter)
        {
        case 0:
        {
            counter++;
            break;
        }
        case 1:
        {
            counter++;
            break;
        }
        case 2:
        {
            timeList.append(tempstr);
            tempstr.clear();
            counter=0;
            break;
        }
        }
        str = strtok_s(NULL, delim, &saveptr);

    }




}


