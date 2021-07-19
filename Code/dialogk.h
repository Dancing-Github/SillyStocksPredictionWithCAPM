#ifndef DIALOGK_H
#define DIALOGK_H
#include <QDialog>
#include <QDialogButtonBox>
#include<QDebug>
#include<cstring>
#include <QLineEdit>

namespace Ui {
class DialogK;
}

class DialogK : public QDialog
{
    Q_OBJECT

public:
    explicit DialogK(QWidget *parent = nullptr);
    ~DialogK();
    void searchListWidgetItem();//查找并将股票代号显示出来
    void select();//选择股票
    void setID(std::string);//获取一串股票的编号
    void setTitle(QString);//设置窗口名字
    static QString result;//储存选中的股票代号
private:
    Ui::DialogK *ui;
    QStringList GPIDS;//储存股票号的链表
    QString selection;//选中的股票代号


};

#endif // DIALOGK_H
