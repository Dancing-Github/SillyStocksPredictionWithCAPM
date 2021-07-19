#ifndef CANDLESTICKSET_H
#define CANDLESTICKSET_H

#include <QObject>
#include <QtCharts>
#include <QCandlestickSet>
#pragma execution_character_set("utf-8")

//用于展示k线图，存储单日股票数据的CandlestickSet项
class CandlestickSet : public QCandlestickSet
{
    Q_OBJECT
public:
    explicit CandlestickSet(QObject *parent = nullptr);
    void getHovered();
signals:
    void toHovered(qreal open,qreal high,qreal low,qreal close,qreal idx);
};

#endif // CANDLESTICKSET_H
