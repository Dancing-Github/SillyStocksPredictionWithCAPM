#pragma once
#pragma execution_character_set("utf-8")
#include <string>  
#include<QDebug>
#include <sqlite3.h>  
#pragma comment(lib, "sqlite3.lib") 
using namespace std;
static sqlite3* pDB;//将打开的数据库依附到这里
static string tempCallBack;//数据库的查询结果储存



     //数据库的查询结果储存
	int CallBack(void* NotUsed, int NumberOfColumn, char** ResultInRow, char** azColName);

     //打开数据库
	bool openDatabase();

    //关闭数据库
	void closeDatabase();

	//创建表
	bool CreateTable();

	//增加股票  
	bool AddGP(const string& ID, const string& COMPANY, const string& TOP, const string& BOTTOM, const string& OPEN, const string& DOWN, const string& YEAR, const string& MONTH, const string& DAY);

	//删除股票 
	bool DeleteGP(const string& ID, const string& COMPANY, const string& YEAR, const string& MONTH, const string& DAY);

	//修改股票 
	bool ModifyGP(const string& ID, const string& COMPANY, const string& TOP, const string& BOTTOM, const string& OPEN, const string& DOWN, const string& YEAR, const string& MONTH, const string& DAY);

	//查找股票 
	bool SelectGP(const string& ID, const string& NameOfColumn, const string& YEAR = "", const string& MONTH = "", const string& DAY = "");

	string findGP(const string& ID, const string& NameOfColumn, const string& YEAR = "", const string& MONTH = "", const string& DAY = "");

    //增加处理后的数据
	bool AddCAPM(const string& ID, const string& COMPANY, const string& BETA, const string& ERS, const string& YEAR, const string& MONTH, const string& DAY);

    //删除处理后的数据
	bool DeleteCAPM(const string& ID, const string& COMPANY);

    //修改处理后的数据
	bool ModifyCAPM(const string& ID, const string& COMPANY, const string& BETA, const string& ERS, const string& YEAR, const string& MONTH, const string& DAY);

	//查找
	bool SelectCAPM(const string& ID, const string& NameOfColumn = "");

    //调用SelectCAPM并返回tempCallBack
	string findCAPM(const string& ID, const string& NameOfColumn = "");

	//切分与导入
	bool InputInfo(const string ID, const string &data, string COMPANY);

	//ascii 转 Utf8 
	string ASCII2UTF_8(string strAsciiCode);

	//ascii 转 Unicode 
	wstring Acsi2WideByte(string& strascii);

	//Unicode 转 Utf8 
	std::string Unicode2Utf8(const std::wstring& widestring);

    //返回当前时间
	string TimeOfNow(string time="");


	


