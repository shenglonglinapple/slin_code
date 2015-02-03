#include "YahuoHistoryReqAck.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <sstream>

#include "BaseException.h"
#include "Log4cppLogger.h"

CYahuoHistoryReqAck::CYahuoHistoryReqAck()
{

}

CYahuoHistoryReqAck::~CYahuoHistoryReqAck()
{

}

/*
2014-01-01 - 2014-02-01    month value - 1
http://ichart.yahoo.com/table.csv?s=000008.SZ&a=0&b=1&c=2014&d=1&e=1&f=2014&g=d&ignore=.csv
*/
QString CYahuoHistoryReqAck::getRequestUrl(
	const QString &strSymbolUse, 
	qint32 startYear, qint32 startMonth, qint32 startDay,
	qint32 endYear, qint32 endMonth, qint32 endDay, 
	const QString &rangeType) 
{
	QString strUrl;
	std::stringstream byteUrl;
	int nRequestStartMonth = 0;
	int nRequestEndMonth = 0;

	nRequestStartMonth = startMonth - 1;
	nRequestEndMonth = endMonth - 1;

	MYLOG4CPP_DEBUG<<"startMonth="<<startMonth
		<<" "<<"nRequestStartMonth="<<nRequestStartMonth
		<<" "<<"endMonth="<<endMonth
		<<" "<<"nRequestEndMonth="<<nRequestEndMonth;

	byteUrl << "http://ichart.yahoo.com/table.csv?s="
		<< strSymbolUse.toStdString()
		<< "&a="
		<< nRequestStartMonth
		<< "&b="
		<< startDay
		<< "&c="
		<< startYear
		<< "&d="
		<< nRequestEndMonth
		<< "&e="
		<< endDay
		<< "&f="
		<< endYear
		<< "&g="
		<< rangeType.toStdString()
		<< "&ignore=.csv";

	strUrl = byteUrl.str().c_str();
	return strUrl;

	
	//"http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014";
}//

QString CYahuoHistoryReqAck::getRequestUrl( const QString &strSymbolUse, 
qint32 startYear, qint32 startMonth, unsigned startDay, 
qint32 endYear, qint32 endMonth, qint32 endDay, const YahuoReqAck::RangeType &rangeType )
{
	QString strRangeTyep = YahuoReqAck::getString(rangeType);
	return getRequestUrl(strSymbolUse, startYear, startMonth, startDay, endYear, endMonth, endDay, strRangeTyep);
}






void CYahuoHistoryReqAck::test_CYahuoHistoryReqAck()
{

	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	QString strResGet;
	strResGet= classCYahuoHistoryReqAck.getRequestUrl("600667.SS", 2010, 4, 1, 2014, 10, 13, YahuoReqAck::dividendsOnly);
	// if data can not be retrieved by any of the functions, an exception is thrown

	QString petr4HistoricalPrices = classCYahuoHistoryReqAck.getRequestUrl("600667.SS",
		2014, 4, 2,
		2014, 10, 7,
		YahuoReqAck::daily);
}


////////////////
#if 0

void YahooHistoryObject::getUrl (QDateTime sd, QDateTime ed, QString symbol, QString &url)
{
	//http://ichart.finance.yahoo.com/table.csv?s=AAPL&d=1&e=22&f=2011&g=d&a=8&b=7&c=1984&ignore=.csv
	url = "http://ichart.finance.yahoo.com/table.csv?s=";
	url.append(symbol);
	url.append("&d=" + QString::number(ed.date().month() - 1));
	url.append("&e=" + ed.date().toString("d"));
	url.append("&f=" + ed.date().toString("yyyy"));
	url.append("&a=" + QString::number(sd.date().month() - 1));
	url.append("&b=" + sd.date().toString("d"));
	url.append("&c=" + sd.date().toString("yyyy"));
	url.append("&ignore=.csv");
}
int YahooHistoryObject::downloadName (QString symbol, QString &name)
{
	QString url = "http://download.finance.yahoo.com/d/quotes.csv?s=";
	url.append(symbol);
	url.append("&f=n");
	url.append("&e=.csv");

	QNetworkAccessManager manager;
	QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
	QEventLoop e;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &e, SLOT(quit()));
	e.exec();

	// parse the data and save quotes
	QByteArray ba = reply->readAll();
	QString s(ba);
	s = s.remove('"');
	s = s.remove(',');
	s = s.trimmed();
	if (s.isEmpty())
		return 0;

	name = s;

	return 1;
}
#endif
////////////////
#if 0
如何使用 Yahoo! Finance stock API 获取股票数据 
http://blog.sina.com.cn/s/blog_7ed3ed3d010147pk.html
1、通过API获取实时数据
请求地址
http://finance.yahoo.com/d/quotes.csv?s=<股票名称>&f=<数据列选项>
参数
s – 表示股票名称，多个股票之间使用英文加号分隔，如”XOM+BBDb.TO+JNJ+MSFT”，罗列了四个公司的股票：XOM, BBDb.TO, JNJ, MSFT。
f – 表示返回数据列，如”snd1l1yr”。更详细的参见雅虎股票 API f 参数对照表。
2、通过API获取历史数据
请求地址
http://ichart.yahoo.com/table.csv?s=<string>&a=<int>&b=<int>&c=<int>&d=<int>&e=<int>&f=<int>&g=d&ignore=.csv
参数
s – 股票名称
a – 起始时间，月
b – 起始时间，日
c – 起始时间，年
d – 结束时间，月
e – 结束时间，日
f – 结束时间，年
g – 时间周期。Example: g=w, 表示周期是’周’。d->’日’(day), w->’周’(week)，m->’月’(mouth)，v->’dividends only’
一定注意月份参数，其值比真实数据-1。如需要9月数据，则写为08。
3、通过API获取深沪股票数据
雅虎的API是国际性的，支持查询国内沪深股市的数据，但代码稍微变动一下，如浦发银行的代号是：600000.SS。规则是：上海市场末尾加.ss，深圳市场末尾加.sz。

最近股市甚火，受聘开发一股票网站，股票的数据从哪里来成了一个大问题，股票软件一般都是加密处理的，还有一些web services也是要帐号的，免费的方法只有一种了，抓别人网站的数据。好在经我研究，发现yahoo提供国内和国外股市每天的交易数据资料，这可谓一 大幸事啊。
http://table.finance.yahoo.com/table.csv?s=ibm&d=6&e=22&f=2006&g=d&a=11&b=16&c=1991&ignore=.csv
上面的链接可以抓取IBM股票从1991年11月16日起到2006年6月22的数据。把ibm改成sohu，就可以抓到sohu的股票数据了。
http://table.finance.yahoo.com/table.csv?s=sohu&d=6&e=22&f=2008&g=d&a=11&b=16&c=2008&ignore=.csv
上面链接可以抓搜狐股票的数据。

　　那么中国股市的数据有没有呢？答案是肯定的，不过要按照下面的参数做些调整，下面提供全球证券交易所的资料。
  上证股票是股票代码后面加上.ss，深证股票是股票代码后面加上.sz
  例如：000001 = 000001.sz
深市数据链接：http://table.finance.yahoo.com/table.csv?s=000001.sz
上市数据链接：http://table.finance.yahoo.com/table.csv?s=600000.ss
上证综指代码：000001.ss，深证成指代码：399001.SZ，沪深300代码：000300.ss

下面就是世界股票交易所的网址和缩写，要查找哪个股票交易所的数据，就按照上面的格式以此类推。
上海交易所=cn.finance.yahoo.com,.SS,Chinese,sl1d1t1c1ohgv
深圳交易所=cn.finance.yahoo.com,.SZ,Chinese,sl1d1t1c1ohgv
美国交易所=finance.yahoo.com,,United States,sl1d1t1c1ohgv
加拿大=ca.finance.yahoo.com,.TO,Toronto,sl1d1t1c1ohgv
新西兰=au.finance.yahoo.com,.NZ,sl1d1t1c1ohgv
新加坡=sg.finance.yahoo.com,.SI,Singapore,sl1d1t1c1ohgv
香港=hk.finance.yahoo.com,.HK,Hong Kong,sl1d1t1c1ohgv
台湾=tw.finance.yahoo.com,.TW,Taiwan,sl1d1t1c1ohgv
印度=in.finance.yahoo.com,.BO,Bombay,sl1d1t1c1ohgv
伦敦=uk.finance.yahoo.com,.L,London,sl1d1t1c1ohgv
澳洲=au.finance.yahoo.com,.AX,Sydney,sl1d1t1c1ohgv
巴西=br.finance.yahoo.com,.SA,Sao Paulo,sl1d1t1c1ohgv
瑞典=se.finance.yahoo.com,.ST,Stockholm,sl1d1t1c1ohgv
#endif