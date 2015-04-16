#ifndef __CLASS__INDICATOR_TOOL_VIEW_H__
#define __CLASS__INDICATOR_TOOL_VIEW_H__

#include <QtGui/QtGui>

#include <QtGui/QGraphicsView>



class CIndicatorToolView : public QGraphicsView
{
    Q_OBJECT


public:
    CIndicatorToolView(QWidget *parent = 0);
	virtual ~CIndicatorToolView();
public:

};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_TOOL_VIEW_H__
