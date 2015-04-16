#ifndef __CLASS__INDICATOR_EDITOR_VIEW_H__
#define __CLASS__INDICATOR_EDITOR_VIEW_H__

#include <QtGui/QtGui>

#include <QtGui/QGraphicsView>



class CIndicatorEditorView : public QGraphicsView
{
    Q_OBJECT


public:
    CIndicatorEditorView(QWidget *parent = 0);
	virtual ~CIndicatorEditorView();
public:

};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_VIEW_H__
