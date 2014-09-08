#ifndef __CLASS_QUOTES_H_HEADER_VIEW_HH__
#define __CLASS_QUOTES_H_HEADER_VIEW_HH__



#include <QtGui/QWidget>
#include <QtGui/QHeaderView>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



class CQuotesHHeaderView : public QHeaderView
{ 
	Q_OBJECT
public: 
	CQuotesHHeaderView(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = 0); 
	~CQuotesHHeaderView(); 
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



#endif//__CLASS_QUOTES_H_HEADER_VIEW_HH__



