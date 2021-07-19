#pragma once
#ifndef CAPM_H
#define CAPM_H
#pragma execution_character_set("utf-8")
#include <QDebug>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

class Capm
{
public:
    double strtodou(string);//将string转化为double
    void getsop(char*);//获取所求股票开盘价并将其存储到m_sop
    void getscl(char*);//获取所求股票收盘价并将其存储到m_scl
    void getmop(char*);//获取大盘指数的开盘价并将其存储到m_mop
    void getmcl(char*);//获取大盘指数的收盘价并将其存储到m_mcl
    void calculatesr();//计算所求股票的日收益率
    void calculatemr();//计算大盘指数的日收益率
    void ES();//计算所求股票日收益率的均值
    void EM();//计算大盘指数日收益率的均值
    void EM2();//计算大盘指数日收益率的二阶原点矩
    void VAR();//计算大盘指数日收益率的方差
    void COV();//计算所求股票和大盘指数的协方差
    void BETA();//计算所求股票的beta值
    void ERS();//计算所求股票的预期年收益率

    //获取数据的函数
	void getDataToCapm(string datasop, string datascl, string datamop, string datamcl);
    void analysis();//分析股票的函数
    string doutostrBETA();//将Beta转化为string类型的函数
    string doutostrERS();//将Ers转化为string类型的函数

private:
	vector<double> m_sop;
	vector<double> m_scl;
	vector<double> m_sr;
	vector<double> m_mop;
	vector<double> m_mcl;
	vector<double> m_mr;
	double m_Es = 0.0;
	double m_Em = 0.0;
	double m_E = 0.0;
	double m_E2 = 0.0;
	double m_Em2 = 0.0;
	double m_Var = 0.0;
	double m_Cov = 0.0;
	const double m_rf = 0.038 / 360;
	double m_Beta = 0.0;
	double m_Ers = 0.0;
};
#endif
