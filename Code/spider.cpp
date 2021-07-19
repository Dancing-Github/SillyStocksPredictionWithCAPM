
#include<spider.h>
#include<stdexcept>


Spider::Spider(string type, string symbol, string DateStart, string DateEnd)
{
	//获取公司名和股票数据的网页，稍后爬取数据
	urlOfCompany = "https://q.stock.sohu.com/"+type+"/"+symbol+"/lshq.shtml";
    urlOfResult = "https://q.stock.sohu.com/hisHq?code="+type+"_"+symbol+"&start="+DateStart+"&end="+DateEnd+"&order=A&period=d&callback=historySearchHandler&rt=jsonp";

	//拼接ID
	ID = type+symbol;
	//爬取数据
	 GetHtml(urlOfResult,result);
	 GetHtml(urlOfCompany, companyPage);

	 //判断该代号对应的股票是否存在
	 if (companyPage.find("keywords") != string::npos|| companyPage.find("description") != string::npos)
	 { 
         qDebug() << "查询失败" ;
		 throw invalid_argument("股票不存在");
	 }
	 else if (companyPage.find("Keywords") != string::npos && companyPage.find("Description") != string::npos)
	 {
         qDebug() << "查询成功";
         //qDebug() << companyPage<<endl<<result<<endl;
	 }
	 SetCompany();//设置上市公司名
}

//访问并将网页源码下载到字符串中
bool Spider::GetHtml(string url,string &str)
{
	const char * URL_STRING = url.c_str();
	
	
	// 初始化URL
	URL_COMPONENTSA crackedURL = { 0 };
	char szHostName[128];
	char szUrlPath[256];
	crackedURL.dwStructSize = sizeof(URL_COMPONENTSA);
	crackedURL.lpszHostName = szHostName;
	crackedURL.dwHostNameLength = ARRAYSIZE(szHostName);
	crackedURL.lpszUrlPath = szUrlPath;
	crackedURL.dwUrlPathLength = ARRAYSIZE(szUrlPath);
	InternetCrackUrlA(URL_STRING, (DWORD)strlen(URL_STRING), 0, &crackedURL);

	// 初始化网络会话
	HINTERNET hInternet = InternetOpenA("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.212 Safari/537.36 Edg/90.0.818.66", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);


	// HTTPS版本
	HINTERNET hHttpSession = InternetConnectA(hInternet, crackedURL.lpszHostName, INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", crackedURL.lpszUrlPath, NULL, "", NULL, INTERNET_FLAG_SECURE, 0);



	DWORD dwRetCode = 0;
	DWORD dwSizeOfRq = sizeof(DWORD);
	BOOL bRet = FALSE;

    // 发送HTTP请求
	HttpSendRequest(hHttpRequest, NULL, 0, NULL, 0);

    // 查询HTTP请求状态
	bRet = HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwRetCode, &dwSizeOfRq, NULL);
	if (bRet == false)
	{
        qDebug() << "连接失败";
		return false;
	}
	else
	{
        qDebug() << "连接成功" ;
	}


	// 循环读取网页内容
	InternetReadFileLOOP(hHttpRequest, str);
	return true;
}

//将网页源码循环输入到字符串
void Spider::InternetReadFileLOOP(HINTERNET request, string& data)
{
	DWORD lpdwNumberOfBytesRead = 0;
	const int bufferLength = 2048;
	BOOL bRet = FALSE;

	char buffer[bufferLength];
	do {
        //通过循环将一段段的buffer输入到data里面
		ZeroMemory(buffer, bufferLength);
		bRet = InternetReadFile(request, buffer, bufferLength - 1, &lpdwNumberOfBytesRead);
		buffer[lpdwNumberOfBytesRead] = '\0';
		data += buffer;
    } while (lpdwNumberOfBytesRead > 0 || bRet == FALSE);
}

//返回获取的网页
const string Spider::GetResult()const
{
	return result;
}

//返回股票代号
const string Spider::GetID() const
{
	return ID;
}

//返回股票公司名
const string Spider::GetCompany()const
{
	return company;
}

//根据股票代号自动爬取公司名
bool Spider::SetCompany()
{
	size_t pos1, pos2, pos;
	string str1, str2;

    //根据实际的网页内容，搜索需要的公司名的位置
	pos1 = companyPage.find("Keywords");
	pos = companyPage.find(",", pos1);
	if (pos != string::npos)
	{
		str1 = companyPage.substr(pos1 + 19, pos - pos1 - 19);
	}

	pos2 = companyPage.find("Description");
	pos = companyPage.find("(", pos2);

	if (pos != string::npos)
	{
		str2 = companyPage.substr(pos2 + 22, pos - pos2 - 22);
	}

    if (str1 != str2)//判断是否输入了不存在的股票
	{
		throw invalid_argument("股票不存在");
		return false;
	}
	else
	{
		company = str1;
	}
	return true;
}

