#include<SQLiteDB.h>

#include <Windows.h>
#include<stdexcept>
#include<vector>

using namespace std;

//数据库的查询结果储存
int CallBack(void* NotUsed, int NumberOfColumn, char** ResultInRow, char** azColName)
{
    
    for (int i = 0; i < NumberOfColumn; i++)
    {
        //qDebug() << azColName[i] << " = " << (ResultInRow[i] ? ResultInRow[i] : "NULL") << ", ";
        tempCallBack += (ResultInRow[i] ? ResultInRow[i] : "NULL") ;
        tempCallBack += " ";
        
    }
    
 return 0;
}

//打开数据库
bool openDatabase()
{
    //打开路径采用utf-8编码  
    //如果路径中包含中文，需要进行编码转换  

    int nRes = sqlite3_open("test.db", &pDB);
    if (nRes != SQLITE_OK)
    {
        qDebug()  << "Open database fail: " << sqlite3_errmsg(pDB);
        sqlite3_close(pDB);
        return false;
    }
    else
        return true;
}

//关闭数据库
void closeDatabase()
{
    qDebug() <<"closing Database..." ;
    
    sqlite3_close(pDB);
    qDebug() << "Database Closed" ;
}

//创建表
bool CreateTable()
{
    

    string strGP = "create table if not exists GP( ID text not null,COMPANY text not null, TOP integer not null,BOTTOM integer not null,OPEN integer not null,CLOSE integer not null,YEAR integer not null,MONTH integer not null,DAY integer not null,PRIMARY KEY(ID,YEAR,MONTH,DAY))";
    string strCAPM = "create table if not exists CAPM(ID text not null,COMPANY text not null,BETA real not null,ERS real not null,YEAR interger not null,MONTH interger not null,DAY interger not null,PRIMARY KEY(ID))";

    char* cErrMsgGP;
    char* cErrMsgCAPM;
    int nResGP = sqlite3_exec(pDB, strGP.c_str(), 0, 0, &cErrMsgGP);
    if (nResGP != SQLITE_OK)
    {
        qDebug() << "create table GP fail: " << cErrMsgGP ;
        return false;
    }

    int nResCAPM = sqlite3_exec(pDB, strCAPM.c_str(), 0, 0, &cErrMsgCAPM);
    if (nResCAPM != SQLITE_OK)
    {
        qDebug() << "create table CAPM fail: " << cErrMsgCAPM ;
        return false;
    }

    sqlite3_free(cErrMsgGP);
    sqlite3_free(cErrMsgCAPM);
    
    return true;
}

//增加股票  
bool AddGP(const string& ID, const string& COMPANY, const string& TOP, const string& BOTTOM, const string& OPEN, const string& CLOSE, const string& YEAR, const string& MONTH, const string& DAY)
{
    



    string strSql = "";
    strSql += "insert or replace into GP(ID,COMPANY,TOP,BOTTOM,OPEN,CLOSE,YEAR,MONTH,DAY)";
    strSql += "values('";
    strSql += ID;
    strSql += "','";
    strSql += COMPANY;
    strSql += "','";
    strSql += TOP;
    strSql += "','";
    strSql += BOTTOM;
    strSql += "','";
    strSql += OPEN;
    strSql += "','";
    strSql += CLOSE;
    strSql += "','";
    strSql += YEAR;
    strSql += "','";
    strSql += MONTH;
    strSql += "','";
    strSql += DAY;
    strSql += "');";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        qDebug() << "add RECORDS fail: " << cErrMsg ;
        return false;
    }
    sqlite3_free(cErrMsg);

    return true;
}

//删除股票 
bool DeleteGP(const string& ID, const string& COMPANY, const string& YEAR, const string& MONTH, const string& DAY)
{
    
    string strSql = "";
    strSql += "delete from GP where ID='";
    strSql += ID;
    strSql += "' and COMPANY='";
    strSql += COMPANY;
    strSql += "' and YEAR='";
    strSql += YEAR;
    strSql += "' and MONTH='";
    strSql += MONTH;
    strSql += "' and DAY='";
    strSql += DAY;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        qDebug() << "delete RECORDS fail: " << cErrMsg ;
        return false;
    }
    else
    {
        qDebug()  << "delete RECORDS success: " << COMPANY.c_str() << "\t" << YEAR.c_str() << MONTH.c_str() << DAY.c_str()  ;
    }
    
    sqlite3_free(cErrMsg);
 
    return true;
}

//修改股票 
bool ModifyGP(const string& ID, const string& COMPANY, const string& TOP, const string& BOTTOM, const string& OPEN, const string& CLOSE, const string& YEAR, const string& MONTH, const string& DAY)
{
    
    string strSql = "";
    strSql += "update GP set TOP ='";
    strSql += TOP;
    strSql += "',BOTTOM='";
    strSql += BOTTOM;
    strSql += "',OPEN='";
    strSql += OPEN;
    strSql += "',CLOSE='";
    strSql += CLOSE;
    strSql += "'where ID='";
    strSql += ID;
    strSql += "' and COMPANY='";
    strSql += COMPANY;
    strSql += "' and YEAR='";
    strSql += YEAR;
    strSql += "' and MONTH='";
    strSql += MONTH;
    strSql += "' and DAY='";
    strSql += DAY;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
         qDebug()  << "modify GP fail: " << cErrMsg  ;
        return false;
    }
    else
    {
         qDebug()  << "modify GP success: " << COMPANY.c_str() << "\t" << YEAR.c_str() << MONTH.c_str() << DAY.c_str()  ;
    }

    sqlite3_free(cErrMsg);

    return true;
}

//查找
bool SelectGP(const string& ID,const string& NameOfColumn,const string& YEAR, const string& MONTH, const string& DAY)
{
    tempCallBack.clear();
    
   
    char* cErrMsg;
    string strSql;

    if (YEAR == "" && MONTH == "" && DAY == "")
    {
        strSql = "select " + NameOfColumn + " from GP where ID='" + ID + "' ;";
    }
    else if (YEAR != "" && MONTH == "" && DAY == "")
    {
        strSql = "select " + NameOfColumn + " from GP where ID='" + ID + "'and YEAR='" + YEAR + "' ;";
    }
    else if (YEAR != "" && MONTH != "" && DAY == "")
    {
        strSql = "select " + NameOfColumn + " from GP where ID='" + ID + "'and YEAR='" + YEAR + "'and MONTH='" + MONTH + "' ;";

    }
    else if (YEAR != "" && MONTH != "" && DAY != "")
    {
        strSql = "select " + NameOfColumn + " from GP where ID='" + ID + "'and YEAR='" + YEAR + "'and MONTH='" + MONTH + "'and DAY='" + DAY + "' ;";
    }
    else
    {
        throw invalid_argument("格式错误");
    }

    int res = sqlite3_exec(pDB, strSql.c_str(), CallBack, 0, &cErrMsg);

    if (res != SQLITE_OK)
    {
         qDebug()  << "select fail: " << cErrMsg  ;
        return false;
    }
   
    sqlite3_free(cErrMsg);

    return true;
}

//调用SelectGP并返回tempCallBack
string findGP(const string& ID, const string& NameOfColumn, const string& YEAR, const string& MONTH, const string& DAY)
{
    tempCallBack.clear();
    qDebug()<<QString::fromStdString(ID) ;
    if (SelectGP(ID, NameOfColumn, YEAR, MONTH, DAY))
    {

        return tempCallBack;
    }
    else
    {
        qDebug()<<"hhh";
        return "";
    }
}

//增加处理后的数据
bool AddCAPM(const string& ID, const string& COMPANY, const string& BETA, const string& ERS, const string& YEAR, const string& MONTH, const string& DAY)
{
    



    string strSql = "";
    strSql += "insert or ignore into CAPM(ID,COMPANY,BETA,ERS,YEAR,MONTH,DAY)";
    strSql += "values('";
    strSql += ID;
    strSql += "','";
    strSql += COMPANY;
    strSql += "','";
    strSql += BETA;
    strSql += "','";
    strSql += ERS;
    strSql += "','";
    strSql += YEAR;
    strSql += "','";
    strSql += MONTH;
    strSql += "','";
    strSql += DAY;
    strSql += "');";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
         qDebug()  << "add CAPM fail: " << cErrMsg  ;
        return false;
    }
   

    sqlite3_free(cErrMsg);

    return true;
}

//删除处理后的数据
bool DeleteCAPM(const string& ID, const string& COMPANY)
{
    
    string strSql = "";
    strSql += "delete from GP where ID='";
    strSql += ID;
    strSql += "' and COMPANY='";
    strSql += COMPANY;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
         qDebug()  << "delete CAPM fail: " << cErrMsg  ;
        return false;
    }
    else
    {
         qDebug()  << "delete CAPM success: " << ID.c_str() << "\t"  << COMPANY.c_str()  ;
    }
 
    sqlite3_free(cErrMsg);

    return true;
}

//修改处理后的数据
bool ModifyCAPM(const string& ID, const string& COMPANY, const string& BETA, const string& ERS, const string& YEAR, const string& MONTH, const string& DAY)
{
  
    string strSql = "";
    strSql += "update CAPM set BETA ='";
    strSql += BETA;
    strSql += "',ERS='";
    strSql += ERS;
    strSql += "',YEAR='";
    strSql += YEAR;
    strSql += "',MONTH='";
    strSql += MONTH;
    strSql += "',DAY='";
    strSql += DAY;
    strSql += "'where ID='";
    strSql += ID;
    strSql += "' and COMPANY='";
    strSql += COMPANY;    
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
         qDebug()  << "modify CAPM fail: " << cErrMsg  ;
        return false;
    }
    else
    {
         qDebug()  << "modify CAPM success: " << ID.c_str() << "\t" << COMPANY.c_str() << "\t" << BETA.c_str() << "\t" <<ERS.c_str() << "\t" << YEAR.c_str() << "\t" << MONTH.c_str() << "\t" << DAY.c_str() << "\t"  ;
    }

    sqlite3_free(cErrMsg);

    return true;
}

//查找 
bool SelectCAPM(const string& ID, const string& NameOfColumn)
{
    tempCallBack.clear();
  
    char* cErrMsg;
    string strSql;
    if (NameOfColumn == "" )
    {
        strSql = "select * from CAPM where ID='" + ID + "' ;";
    }
    else 
    {
        strSql = "select " + NameOfColumn + " from CAPM where ID='" + ID + "' ;";
    }
       

    int res = sqlite3_exec(pDB, strSql.c_str(), CallBack, 0, &cErrMsg);

    if (res != SQLITE_OK)
    {
         qDebug()  << "select fail: " << cErrMsg  ;
        return false;
    }
    
    sqlite3_free(cErrMsg);

    return true;
}

//调用SelectCAPM并返回tempCallBack
string findCAPM(const string& ID, const string& NameOfColumn)
{
    tempCallBack.clear();
    if (SelectCAPM(ID, NameOfColumn))
    {
        return tempCallBack;
    }
    else
    {
        return "";
    }
}

//切分与导入
bool InputInfo(const string ID, const string &data, const string COMPANY)
{
    
    if (data.find("non-existent") != string::npos)
        {
         qDebug()  << "Error Finding Keywords While AddingRecord";
        return false;
        }
   
    const size_t posStart = data.find("hq");
    const size_t posEnd = data.find("code");
    size_t posOfLeft = posStart+5;
    size_t posOfRight = posOfLeft;
    

    string pieceOfData, YEAR, MONTH, DAY, OPEN, CLOSE, TOP, BOTTOM;

    char*szerrmsg;
    sqlite3_exec(pDB, "begin;", 0,0, &szerrmsg);//设置数据库操作暂时存到内存中

    while (posOfRight<posEnd-4)
    {
        //找到整个网页所需字段的始末位置
        posOfLeft = data.find('[', posOfLeft);
        posOfRight = data.find(']', posOfRight);
        if (posOfLeft == string::npos || posOfRight == string::npos || posOfLeft >= posOfRight )
        {
             qDebug()  << "Error Finding Keywords While Adding Record";
             sqlite3_exec(pDB, "commit;", 0,0, &szerrmsg);//将内存的数据库更改提交到磁盘文件
            return false;
        }
        
       //截取出来的一天的数据条目
        pieceOfData = data.substr(posOfLeft, posOfRight - posOfLeft);       
        //size_t LeftOfPiece = 0;
        //size_t RightOfPiece = 5;

        //截取所需信息，每次counter++移动至后一个双引号之下 
        int counter = 0;
        const char delim[] = "[\",-";
        char* str;
        char* saveptr = NULL;
        str = strtok_s((char*)pieceOfData.c_str(), delim, &saveptr);
        while (str != NULL)
        {
            switch (counter)
            {
            case 0:YEAR = str; break;
            case 1:MONTH = str; break;
            case 2:DAY = str; break;
            case 3:OPEN = str; break;
            case 4:CLOSE = str; break;
            case 7:BOTTOM = str; break;
            case 8:TOP = str; break;
            default:
                break;
            }
            counter++;
            str = strtok_s(NULL, delim, &saveptr);
        }
       
        
        if (!AddGP(ID, COMPANY, TOP, BOTTOM, OPEN, CLOSE, YEAR, MONTH, DAY))
        {
             qDebug()  << "Add Records Failed!";
             sqlite3_exec(pDB, "commit;", 0,0, &szerrmsg);//将内存的数据库更改提交到磁盘文件
            return false;
        }

        posOfLeft++;
        posOfRight++;
    }

sqlite3_exec(pDB, "commit;", 0,0, &szerrmsg);//将内存的数据库更改提交到磁盘文件
    return true;
}

//ascii 转 Utf8 
string ASCII2UTF_8(string strAsciiCode)
{
    string strRet("");
    //先把 ascii 转为 unicode 
    wstring wstr = Acsi2WideByte(strAsciiCode);
    //最后把 unicode 转为 utf8 
    strRet = Unicode2Utf8(wstr);
    return strRet;
}

//ascii 转 Unicode 
wstring Acsi2WideByte(string& strascii)
{
    int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
    if (widesize == ERROR_NO_UNICODE_TRANSLATION)
    {
        throw invalid_argument("Invalid UTF-8 sequence.");
    }
    if (widesize == 0)
    {
        throw invalid_argument("Error in conversion.");
    }
    vector<wchar_t> resultstring(widesize);
    int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
    if (convresult != widesize)
    {
        throw invalid_argument("La falla!");
    }
    return wstring(&resultstring[0]);
}

//Unicode 转 Utf8 
std::string Unicode2Utf8(const std::wstring& widestring)
{
    int utf8size = WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8size == 0)
    {
        throw invalid_argument("Error in conversion.");
    }
    vector<char> resultstring(utf8size);
    int convresult = WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
    if (convresult != utf8size)
    {
        throw invalid_argument("La falla!");
    }
    return string(&resultstring[0]);
}

//返回当前时间
string TimeOfNow(string time)
{
    string TimeNow, strSql = "select strftime('%Y%m%d','now');";
    

    tempCallBack.clear();
    
   
    char* cErrMsg;
    
    
    int res = sqlite3_exec(pDB, strSql.c_str(), CallBack, 0, &cErrMsg);

    if (res != SQLITE_OK)
    {

         qDebug()  << "select fail: " << cErrMsg  ;
        tempCallBack.clear();
        throw invalid_argument("Cannot Get Time Now");
      
    }
    else
    {
        TimeNow = tempCallBack;
        TimeNow.erase(TimeNow.find(" "), 1);
        tempCallBack.clear();
    }
    if (time == "YEAR")
    {
        TimeNow = TimeNow.substr(0, 4);
    }
    if (time == "MONTH")
    {
        TimeNow = TimeNow.substr(4, 2);
    }
    if (time == "DAY")
    {
        TimeNow = TimeNow.substr(6, 2);
    }
    else
    {
        TimeNow = TimeNow.substr(0, 8);
    }
    sqlite3_free(cErrMsg);

    return TimeNow;
}









