#ifndef __CLASS_USER_INSTRUMENT_INFO_HEADER_VIEW_HH__
#define __CLASS_USER_INSTRUMENT_INFO_HEADER_VIEW_HH__



#include <QtGui/QWidget>
#include <QtGui/QHeaderView>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



class CUserInstrumentInfoHeaderView : public QHeaderView
{ 
	Q_OBJECT
public: 
	CUserInstrumentInfoHeaderView(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = 0); 
	~CUserInstrumentInfoHeaderView(); 
public: 
	void mousePressEvent(QMouseEvent* e);
signals:	
	/*
	class: CQuotesTableViewHHeaderView
	signals:
	void signalMouseRightClickInHHeaderView(QMouseEvent*);
	fun send signals: mousePressEvent(QMouseEvent* e);

	class: CQuotesTableView
	public slots: 
	void slotMouseRightClickInHHeaderView(QMouseEvent* e;
	*/
	void signalMouseRightClickInHHeaderView(QMouseEvent* e);

}; 


//QT_END_NAMESPACE



#endif//__CLASS_USER_INSTRUMENT_INFO_HEADER_VIEW_HH__



