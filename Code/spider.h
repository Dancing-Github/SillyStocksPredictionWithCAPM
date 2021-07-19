#pragma once
#include<string>
#include<QDebug>
#include<cstring>
#include<windows.h>
#include <WinInet.h>
#pragma execution_character_set("utf-8")
#pragma comment(lib,"wininet.lib")
using namespace std;

class Spider
{
public:
	Spider(string type, string symbol, string DateStart, string DateEnd);
    bool GetHtml(string url,string &str);//访问并将网页源码下载到字符串中

    void InternetReadFileLOOP(HINTERNET request, string& data);//将网页源码循环输入到字符串

    const string GetResult()const;//返回获取的网页

    const string GetID()const;//返回股票代号

    const string GetCompany()const;//返回股票公司名

    bool SetCompany();//根据股票代号自动爬取公司名

	

private:

    string result;//获取股票数据的网页源码
    string urlOfResult;//股票数据的链接
    string urlOfCompany;//公司名的链接
    string ID;//股票id
    string company;//公司名
    string companyPage;//获取公司名的网页源码
};
