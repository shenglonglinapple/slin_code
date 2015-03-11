#include "SQLParam.h"
#include <sstream>
//#include <limits>
#include <string.h>
#include "Log4cppLogger.h"

CSQLParam::CSQLParam()
{
	strParam.clear();
}
CSQLParam::~CSQLParam()
{
	strParam.clear();
}
CSQLParam& CSQLParam::operator=( const CSQLParam& objCopy )
{
	strParam = objCopy.strParam;
	return *this;
}

CSQLParam::CSQLParam( const CSQLParam& objCopy )
{
	strParam = objCopy.strParam;
}


CSQLParam::CSQLParam( const QString& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const char* tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const char& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const qint32& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const qint64& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}
CSQLParam::CSQLParam( const float& tmpValue )
{
	strParam = QString::number(tmpValue, 10, 18);
}
CSQLParam::CSQLParam( const double& tmpValue )
{
	//error!  1222.445  "1222.4"
	//strParam = QString("%1").arg(tmpValue);
	//strParam.setNum();
	//strParam = QString::number(tmpValue);
	//默认精度6来表示，但12345.67会被截断为12345.6,1234567.8， 它的结果会静悄悄地转换为科学记数法：1.23457e+06
	//strParam = QString::number(tmpValue, 'g', 6);

	//strParam = QString::number(tmpValue, 10, 18);//1222.445555600000034246
	strParam = QString::number(tmpValue, 10, 18);
	//strParam =  do_fraction(tmpValue, 6);
}

QString CSQLParam::getParam() const
{
	return strParam;
}
//strParam =  do_fraction(tmpValue, 6);1222.44555
QString CSQLParam::do_fraction(long double value, int decplaces)
{
	QString strGetValue;
	std::ostringstream out;
	qint32 prec = 18; // 18
	std::string str;
	char DECIMAL_POINT='.';
	size_t nFind = 0;

	//prec = numeric_limits::digits10; // 18
	out.precision(prec);//覆盖默认精度
	out<<value;
	str = out.str(); //从流中取出字符串
	nFind = str.find(DECIMAL_POINT);//DECIMAL_POINT//char DECIMAL_POINT='.'; // 欧洲用法为','

	//有小数点吗？
	//后面至少还有decplaces位吗？
	if ((nFind != std::string::npos) && (str.size()> nFind + decplaces))
	{
		//覆盖第一个多余的数
		str[nFind + decplaces] = '\0';
	}
	//删除nul之后的多余字符
	str.swap(std::string(str.c_str()));
	strGetValue = str.c_str();
	return strGetValue;
}



