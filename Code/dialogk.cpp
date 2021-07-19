#include "dialogk.h"
#include "ui_dialogk.h"

QString DialogK::result="";

DialogK::DialogK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogK)
{
    ui->setupUi(this);

    GPIDS.clear();

    //信号与槽的连接
    connect(ui->lineEdit,&QLineEdit::textChanged,this,&DialogK::searchListWidgetItem);
    connect(ui->listWidget,&QListWidget::itemClicked,this,&DialogK::select);
    connect(ui->pushButton,&QPushButton::clicked,[this]()
    {
        (this->result)=(this->selection);
        this->close();
    });
}


//获取一串股票的编号
void DialogK::setID(std::string IDs)
{
    const char delim[2] = " ";
    char*data=(char*)IDs.c_str();
    char* str;
    char* saveptr = NULL;
    str = strtok_s(data, delim, &saveptr);
    while (str != NULL)
    {
        QString t=str;
        t="cn"+t;
        GPIDS.append(t);
        str = strtok_s(NULL, delim, &saveptr);
    }

    ui->listWidget->clear();
    ui->listWidget->addItems(GPIDS);
    searchListWidgetItem();
}

DialogK::~DialogK()
{
    delete ui;
}

//设置窗口名字
void DialogK::setTitle(QString name)
{
   setWindowTitle(name);
}

//查找并将股票代号显示出来
void DialogK::searchListWidgetItem()
{
    QString strToFind=ui->lineEdit->text();//获取框内文字

    QList<QListWidgetItem *> list;
    list =  ui->listWidget->findItems(strToFind,Qt::MatchStartsWith);
    //若，str == ""  findItems函数 能返回全部项
    QStringList strList;
    if(!list.isEmpty())
    {
        for(int i=0;i<list.length();i++)
        {
            strList<<list.at(i)->text();
        }
        ui->listWidget->clear();
        for(int i =0;i<strList.length();i++)
        {
            ui->listWidget->addItem(strList.at(i));
        }
    }
    else
    {
        ui->lineEdit->backspace(); //当查询不到时backspace
        qApp->beep();   // 警报
    }
}

//选择股票
void DialogK::select()
{
QListWidgetItem* i=ui->listWidget->currentItem();
selection=i->text();
}
