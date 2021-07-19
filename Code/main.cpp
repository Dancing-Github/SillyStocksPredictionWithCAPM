#include "mymainwindow.h"
#include <SQLiteDB.h>
#include<spider.h>
#include"Capm.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    if (!openDatabase())//打开数据库
    {
        return -1;
   }
    if (!CreateTable())//创建表
    {
        return -1;
    }

    QApplication a(argc, argv);
    MyMainWindow w;

    w.show();
    return a.exec();

    closeDatabase();
}

