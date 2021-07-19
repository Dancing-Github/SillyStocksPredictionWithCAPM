#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

//返回窗口里的QChartView*类型变量
QChartView* Form::getChartView()
{
    return ui->scrollAreaWidgetContents;
}

//获取股票名
void Form::setID(std::string id)
{
    ID=id;
}

//展示分析结果的函数
void Form::showAnalysis()
{
    //获取相应股票分析的结果
    std::string Company = findCAPM(ID, "COMPANY");
    std::string Beta = findCAPM(ID, "BETA");
    std::string Ers = findCAPM(ID, "ERS");
    std::string result = showResult(QString::fromStdString(Beta).toDouble());
    std::string text = "";
    std::string text1 = "";
    std::string text2 = "";

    text += "股票号：";
    text += ID;
    text += "   公司名：";
    text += ASCII2UTF_8(Company);

    text1 += "该股票的预期年收益率为：";
    text1 += Ers;
    text1 += "%";
    text1 += "   该股票的beta系数为：";
    text1 += Beta;

    text2 += result;

    ui->label->setText(QString::fromStdString(text));
    ui->label1->setText(QString::fromStdString(text1));
    ui->label2->setText(QString::fromStdString(text2));
}

//返回分析的结果
std::string Form::showResult(qreal m_Beta)
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
