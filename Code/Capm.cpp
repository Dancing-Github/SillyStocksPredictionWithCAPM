#include "Capm.h"

//将string转化为double
double Capm::strtodou(string str)
{
	int clen = 0;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		clen++;
		if (str[i] == '.')
			break;
	}
	double l = 0.0;
	double r = 0.0;
	if (clen == len)
	{
		for (int i = 0; i < clen; i++)
		{
			double temp = (double)((int)str[i] - 48);
			double temp1 = 1;
			for (int j = 1; j <= clen - 1 - i; j++)
				temp1 *= 10;
			temp *= temp1;
			l += temp;
		}
		return l;
	}
	int rlen = len - clen;
	clen -= 1;
	for (int i = 0; i < clen; i++)
	{
		double temp = (double)((int)str[i] - 48);
		double temp1 = 1;
		for (int j = 1; j <= clen - 1 - i; j++)
			temp1 *= 10;
		temp *= temp1;
		l += temp;
	}
	for (int i = 1; i <= rlen; i++)
	{
		double temp = (double)((int)str[i+clen] - 48);
		double temp1 = 1;
		for (int j = 1; j <= rlen - i; j++)
			temp1 *= 10;
		temp *= temp1;
		r += temp;
	}
	double k = 1;
	for (int i = 1; i <= rlen; i++)
		k *= 10;
	r /= k;
	l += r;
	return l;
}

//获取所求股票开盘价并将其存储到m_sop
void Capm::getsop(char* data)
{
	m_sop.clear();
	const char delim[2] = " ";
	char* str;
	char* saveptr = NULL;
	str = strtok_s(data, delim, &saveptr);
	while (str != NULL)
	{
		double temp = strtodou(str);
		m_sop.push_back(temp);
		str = strtok_s(NULL, delim, &saveptr);
	}
}

//获取所求股票收盘价并将其存储到m_scl
void Capm::getscl(char* data)
{
	m_scl.clear();
	const char delim[2] = " ";
	char* str;
	char* saveptr = NULL;
	str = strtok_s(data, delim, &saveptr);
	while (str != NULL)
	{
		double temp = strtodou(str);
		m_scl.push_back(temp);
		str = strtok_s(NULL, delim, &saveptr);
	}
}

//获取大盘指数的开盘价并将其存储到m_mop
void Capm::getmop(char* data)
{
	m_mop.clear();
	const char delim[2] = " ";
	char* str;
	char* saveptr=NULL;
	str = strtok_s(data, delim, &saveptr);
	while (str != NULL)
	{
		double temp = strtodou(str);
		m_mop.push_back(temp);
		str = strtok_s(NULL, delim, &saveptr);
	}
}

//获取大盘指数的收盘价并将其存储到m_mcl
void Capm::getmcl(char* data)
{
	m_mcl.clear();
	const char delim[2] = " ";
	char* str;
	char* saveptr = NULL;
	str = strtok_s(data, delim, &saveptr);
	while (str != NULL)
	{
		double temp = strtodou(str);
		m_mcl.push_back(temp);
		str = strtok_s(NULL, delim, &saveptr);
	}
}

//计算所求股票的日收益率
void Capm::calculatesr()
{
	m_sr.clear();
	vector<double>::iterator op = m_sop.begin(), cl = m_scl.begin();
    //qDebug() << "rs:" << endl;
	for (; op < m_sop.end(); op++, cl++)
	{
		double temp = ((*cl) - (*op)) / (*op);
        //qDebug() << temp << " ";
		m_sr.push_back(temp);
	}
    //qDebug() << endl;
}

//计算大盘指数的日收益率
void Capm::calculatemr()
{
	m_mr.clear();
    vector<double>::iterator op = m_mop.begin(), cl = m_mcl.end(); cl -= m_mop.size();
    //qDebug() << "rm:" << endl;
	for (; op < m_mop.end(); op++, cl++)
	{
		double temp = ((*cl) - (*op)) / (*op);
		m_mr.push_back(temp);
        //qDebug() << temp << " ";
	}
    //qDebug() << endl;
}

//计算所求股票日收益率的均值
void Capm::ES()
{
	vector<double>::iterator itr = m_sr.begin();
	double E = 0.0;
	double num = m_sr.size();
	for (; itr < m_sr.end(); itr++)
		E += (*itr);
	E /= num;
	m_Es = E;
    qDebug() << "m_Es:" << m_Es ;
}

//计算大盘指数日收益率的均值
void Capm::EM()
{
	vector<double>::iterator itr = m_mr.begin();
	double E = 0.0;
	double num = m_mr.size();
	for (; itr < m_mr.end(); itr++)
		E += (*itr);
	E /= num;
	m_Em = E;
    qDebug() << "m_Em:" << m_Em ;
}

//计算大盘指数日收益率的二阶原点矩
void Capm::EM2()
{
	double E2 = 0.0;
	double num = m_mr.size();
	vector<double>::iterator itr = m_mr.begin();
	for (; itr < m_mr.end(); itr++)
		E2 += (*itr) * (*itr);
	E2 /= num;
	m_Em2 = E2;
    qDebug() << "m_Em2:" << m_Em2 ;
}

//计算大盘指数日收益率的方差
void Capm::VAR()
{
	m_Var = m_Em2 - m_Em * m_Em;
    qDebug() << "m_Var:" << m_Var ;
}

//计算所求股票和大盘指数的协方差
void Capm::COV()
{
	vector<double>::iterator sitr = m_sr.begin(), mitr = m_mr.begin();
	double Cov = 0.0;
	double num = m_sr.size();
	for (; sitr < m_sr.end(); sitr++, mitr++)
		Cov += ((*sitr) - m_Es) * ((*mitr) - m_Em);
	Cov /= num;
	m_Cov = Cov;
    qDebug() << "m_Cov:" << m_Cov ;
}

//计算所求股票的beta值
void Capm::BETA()
{
	m_Beta = m_Cov / m_Var;
    qDebug() << "m_Beta:" << m_Beta ;
}

//计算所求股票的预期年收益率
void Capm::ERS()
{
	m_Ers = m_rf + m_Beta * (m_Em - m_rf);
    m_Ers*=36000;//转化为预期年收益率（%）
}

//获取数据的函数
void Capm::getDataToCapm(string datasop, string datascl, string datamop,string datamcl)
{
    getsop((char*)datasop.c_str());
	getscl((char*)datascl.c_str());
	getmop((char*)datamop.c_str());
	getmcl((char*)datamcl.c_str());
}

//分析股票的函数
void Capm::analysis()
{
	calculatesr();
	calculatemr();
	ES();
	EM();
	EM2();
	VAR();
	COV();
	BETA();
	ERS();
}

//将Beta转化为string类型的函数
string Capm::doutostrBETA()
{
	return to_string(m_Beta);
}

//将Ers转化为string类型的函数
string Capm::doutostrERS()
{
	return to_string(m_Ers);
}
