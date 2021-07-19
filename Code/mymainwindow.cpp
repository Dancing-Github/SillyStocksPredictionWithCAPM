#include "mymainwindow.h"
#include "ui_mymainwindow.h"



MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    ui->textBrowser->setText("欢迎使用股票分析系统\n初次使用请点击初始化，否则数据库没有数据\n\n支持单支股票的初始化或者更新\n若整体初始化或更新，时间要视网速而定，期间程序可能进入假死状态\n\n点击K线图分析并在框内输入股票号来搜索股票\n\n鸣谢：搜孤财经网页提供的数据\n鸣谢：CAPM股票模型的论文");

    setWindowTitle("股票分析系统");

    //创建所需功能按钮
    QAction * updataTool= ui->toolBar->addAction("更新数据");
    QAction* oneupdataTool = ui->toolBar->addAction("单支股票更新数据");
    QAction * initializeTool= ui->toolBar->addAction("初始化数据");
    QAction* oneinitializeTool = ui->toolBar->addAction("单支股票初始化数据");
    QAction * kGraphTool= ui->toolBar->addAction("数据分析及K线图");
    QAction* analysisTool = ui->toolBar->addAction("股票分析");

    //将“更新数据”的按钮与相应功能连接
    connect(updataTool,&QAction::triggered,this,[=]()
    {
        update();
    });

    //将“单支股票更新数据”的按钮与相应功能连接
    connect(oneupdataTool, &QAction::triggered, this, [=]()
    {
            QString GP = getGP("更新股票数据");
            if (!GP.isEmpty())
            {
                if(GP.size()==8){GP=GP.mid(2);}
                UpdateGP(GP.toStdString());
                QMessageBox::information(this, "提示", "更新完成！");
            }
    });

    //将“初始化数据”的按钮与相应功能连接
    connect(initializeTool,&QAction::triggered,this,[=]()
    {
        initialize();
        QMessageBox::information(this,"提示","初始化完成！");

    });

    //将“单支股票初始化数据”的按钮与相应功能连接
    connect(oneinitializeTool, &QAction::triggered, this, [=]()
    {
        QString GP = getGP("初始化股票");
        if (!GP.isEmpty())
        {
            if(GP.size()==8){GP=GP.mid(2);}

            InitializeGP(GP.toStdString());
            QMessageBox::information(this, "提示", "初始化完成！");
        }
    });

    //将“数据分析及K线图”的按钮与相应功能连接
    connect(kGraphTool,&QAction::triggered,this,[=]()
    {
        QString GP=getGP("k线图");

        if(!GP.isEmpty())
        {
            qDebug()<<GP;
            kGraph(GP);
        }


    });

    //将“股票分析”的按钮与相应功能连接
    connect(analysisTool, &QAction::triggered, this, [=]()
        {
            QString GP = getGP("股票分析");

            if (!GP.isEmpty())
            {

                analysis(GP);
            }


        });
}


MyMainWindow::~MyMainWindow()
{
    delete ui;
}

//更新所有股票的数据的函数
void MyMainWindow::update()
{
    UpdateGP(IDsOfGP);//调用更新数据的函数，更新股票编号列表IDsOfGP中出现的股票

    string text="更新完成";
    string text1="股票分析系统有2017年10月9日至今的数据";
    string text2="本系统根据CAPM模型进行数据分析";

    QWidget * widget=new QWidget;
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle("股票分析系统数据库基本信息");
    QLabel * label=new QLabel(widget);
    label->move(20,50);
    label->setText(QString::fromStdString(text));
    QLabel * label1=new QLabel(widget);
    label1->move(20,100);
    label1->setText(QString::fromStdString(text1));
    QLabel * label2=new QLabel(widget);
    label2->move(20,150);
    label2->setText(QString::fromStdString(text2));
    widget->setFixedSize(500,250);
    widget->show();

}

//初始化所有股票的数据的函数
void MyMainWindow::initialize()
{
    std::string Ids=IDsOfGP;
    InitializeGP(Ids);//调用初始化数据的函数，初始化股票编号列表IDsOfGP中出现的股票
}

//展现单个股票的k线图的函数
void MyMainWindow::kGraph(QString GP)
{
    CandleSeries c;//创建蜡烛系

    c.setID(GP.toStdString());//设立系列的标题，相应的股票名

    //获取相应日期的股票数据并存入系列中
    c.getOpenList(findGP(GP.toStdString(),"OPEN"));
    c.getHighList(findGP(GP.toStdString(),"TOP"));
    c.getLowList(findGP(GP.toStdString(),"BOTTOM"));
    c.getCloseList(findGP(GP.toStdString(),"CLOSE"));
    c.getTimeList(findGP(GP.toStdString(),"YEAR, MONTH, DAY"));

    c.setData();
    c.printChart();

    //创建专门用于展示k线图窗口类，Form，的对象，来展现k线图
    Form* f=new Form;
    f->setID(GP.toStdString());
    f->showAnalysis();
    f->setAttribute(Qt::WA_DeleteOnClose);
    f->getChartView()->setChart(c.chart);
    f->show();


}

//分析单个股票的函数
void MyMainWindow::analysis(QString GP)
{
    //获取相应股票分析出来的结果
    std::string Company = findCAPM(GP.toStdString(), "COMPANY");
    std::string Beta = findCAPM(GP.toStdString(), "BETA");
    std::string Ers = findCAPM(GP.toStdString(), "ERS");
    std::string result = showResult(QString::fromStdString(Beta).toDouble());
    std::string text = "";
    std::string text1 = "";
    std::string text2 = "";

    text += "股票号：";
    text += GP.toStdString();
    text += "   公司名：";
    text += ASCII2UTF_8(Company);

    text1 += "该股票的预期年收益率为：";
    text1 += Ers;
    text1 += "%";
    text1 += "   该股票的beta系数为：";
    text1 += Beta;

    text2 += result;

    //创建窗口展示分析的结果
    QWidget* widget = new QWidget;
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle("股票分析结果");
    QLabel* label = new QLabel(widget);
    label->move(20, 50);
    label->setText(QString::fromStdString(text));
    QLabel* label1 = new QLabel(widget);
    label1->move(20, 100);
    label1->setText(QString::fromStdString(text1));
    QLabel* label2 = new QLabel(widget);
    label2->move(20, 150);
    label2->setText(QString::fromStdString(text2));
    widget->resize(700,250);
    widget->show();
}

//获取用户要分析的股票的编号的函数
QString MyMainWindow::getGP(QString title)
{

    QString text;
    DialogK d(this);
    d.setID(IDsOfGP);
    d.setTitle(title);

    d.show();
    d.exec();

    text=DialogK::result;
    DialogK::result.clear();
    qDebug()<<text;

    return text;
}

//返回分析结果的函数
std::string MyMainWindow::showResult(qreal m_Beta)
{
    if (m_Beta > 1.02)
        return "该支股票的风险高于市场风险的，如果认为大盘近期整体趋势向上，那么可以持有该股票，获取高于市场的收益";
    else if (m_Beta >= 0.98)
        return "该支股票的风险和市场风险的相近，如果认为大盘近期的走势不可预测，那么可以持有该股票";
    else if (m_Beta > 0)
        return "该支股票的风险低于于市场风险的，如果认为大盘近期会整体下跌，那么可以持有该股票，减少损失";
    else if (m_Beta == 0)
        return "该支股票与大盘走势无必然联系";
    else
        return "该支股票与大盘走势相反";
}



//输入股票编号，如000001，自动 初始化 数据以及分析
bool InitializeGP(const std::string& IDsToInitialize)
{


    std::string TimeNow = TimeOfNow();
    if (!CreateTable())
    {
        return -1;
    }

    Spider zs("zs", "399300", TimeOfBegin, TimeNow);
    if (InputInfo(zs.GetID(), zs.GetResult(), zs.GetCompany()))
    {
        qDebug() << "Input Success" ;
    }

    const char delim[2] = " ";
    char* str;
    char* saveptr=NULL;
    char* IDs = (char*)IDsToInitialize.c_str();

    str = strtok_s(IDs, delim,&saveptr);
    while (str != NULL)
    {
        Spider s("cn", str, TimeOfBegin, TimeNow);
        if (InputInfo(s.GetID(), s.GetResult(), s.GetCompany()))
        {
            qDebug() << "Input Success" ;
        }
        else
        {
            str = strtok_s(NULL, delim, &saveptr);
        continue;
        }

        Capm c;
        c.getDataToCapm(findGP(s.GetID(),"OPEN"), findGP(s.GetID(), "CLOSE"), findGP("zs399300", "OPEN"), findGP("zs399300", "CLOSE"));

        c.analysis();

        AddCAPM(s.GetID(), s.GetCompany(),c.doutostrBETA(), c.doutostrERS(),TimeOfNow("YEAR"), TimeOfNow("MONTH"), TimeOfNow("DAY"));
        str = strtok_s(NULL, delim, &saveptr);

    }


    return true;
}


//输入股票编号，如000001，自动 更新 数据以及分析
bool UpdateGP(const std::string IDsToUpdate)
{
   std::string TimeNow = TimeOfNow();

    Spider zs("zs", "399300", TimeOfBegin, TimeNow);
    if (InputInfo(zs.GetID(), zs.GetResult(), zs.GetCompany()))
    {
        qDebug()<<  "Input Success" ;
    }

    tempCallBack.clear();


    std::string TimeOldYear, TimeOldMonth, TimeOldDay;


    const char delim[2] = " ";
    char* str;
    char* saveptr=NULL;
    char* IDs = (char*)IDsToUpdate.c_str();
    str = strtok_s(IDs, delim,&saveptr);
    while (str != NULL)
    {


        TimeOldYear = findCAPM("cn"+(std::string)str,"YEAR");
        TimeOldMonth = findCAPM("cn" + (std::string)str, "MONTH");
        TimeOldDay= findCAPM("cn" + (std::string)str, "DAY");

        if(TimeOldYear=="")
        {
            str = strtok_s(NULL, delim, &saveptr);
            continue;
        }

        if (TimeOldMonth.size() == 2)
        {
            TimeOldMonth = "0" + TimeOldMonth.substr(0, 1);
        }
        else
        {
            TimeOldMonth = TimeOldMonth.substr(0, 2);
        }

        if (TimeOldDay.size() == 2)
        {
            TimeOldDay = "0" + TimeOldDay.substr(0, 1);
        }
        else
        {
            TimeOldDay = TimeOldDay.substr(0, 2);
        }
        TimeOldYear = TimeOldYear.substr(0, 4);


        Spider s("cn", str, TimeOldYear+TimeOldMonth+TimeOldDay, TimeNow);
        if (InputInfo(s.GetID(), s.GetResult(), s.GetCompany()))
        {
            qDebug() << "Input Success" ;
        }
        else
        {
            qDebug() << "UpdateGP failed" ;
        }
        tempCallBack.clear();


        Capm c;
        c.getDataToCapm(findGP(s.GetID(), "OPEN"), findGP(s.GetID(), "CLOSE"), findGP("zs399300", "OPEN"), findGP("zs399300", "CLOSE"));
        c.analysis();
       ModifyCAPM(s.GetID(), s.GetCompany(), c.doutostrBETA(), c.doutostrERS(), TimeOfNow("YEAR"), TimeOfNow("MONTH"), TimeOfNow("DAY"));

       str = strtok_s(NULL, delim, &saveptr);

    }
    return true;
}




