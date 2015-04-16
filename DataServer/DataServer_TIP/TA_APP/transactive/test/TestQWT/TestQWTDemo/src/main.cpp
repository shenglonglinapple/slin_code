//#include "vld.h"

//#include <qapplication.h>
#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QPixmap>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QSharedMemory>
#include <QtCore/QFile>

//////////////////////////////////////////////////////////////////////////

#include <QtGui/QApplication>
#include <Qt/qmath.h>
//#include <QVector>
#include <QtCore/QVector>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>

//////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "Log4cppLogger.h"
//QWT_DLL

#pragma comment(lib, "Ws2_32.lib")//winsock2
//Ws2_32.lib

int main( int argc, char* argv[] )
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();
	CLog4cppLogger::removeInstance();



	QApplication a(argc, argv);
	QwtPlot plot(QwtText("CppQwtExample1"));
	plot.resize(640,400);
	//设置坐标轴的名称
	plot.setAxisTitle(QwtPlot::xBottom, "x->");
	plot.setAxisTitle(QwtPlot::yLeft, "y->");
	//设置坐标轴的范围//设置X与Y坐标范围  
	plot.setAxisScale(QwtPlot::xBottom, 0.0, 2.0 * M_PI);
	plot.setAxisScale(QwtPlot::yLeft, -1.0, 1.0);
	//设置右边标注
	plot.insertLegend(new QwtLegend(), QwtPlot::RightLegend);
	//使用滚轮放大/缩小
	(void) new QwtPlotMagnifier( plot.canvas() );
	//使用鼠标左键平移
	(void) new QwtPlotPanner( plot.canvas() );
	//计算曲线数据
	QVector<double> xs;
	QVector<double> ys;
	for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 10.0))
	{
		xs.append(x);
		ys.append(qSin(x));
	}
	//构造曲线数据
	QwtPointArrayData * const data = new QwtPointArrayData(xs, ys);
	
	//新建一个曲线对象
	QwtPlotCurve curve("Sine");//curve1
	curve.setData(data);//设置数据
	curve.setStyle(QwtPlotCurve::Lines);//直线形式
	curve.setCurveAttribute(QwtPlotCurve::Fitted, true);//是曲线更光滑
	curve.setRenderHint(QwtPlotItem::RenderAntialiased,true);//抗锯齿 
	curve.setPen(QPen(Qt::blue));//设置画笔
	curve.attach(&plot);//把曲线附加到plot上
	plot.show();

	a.exec();
	
	return 0;
}










