#ifndef __CLASS__INDICATOR_EDITOR_VIEW_H__
#define __CLASS__INDICATOR_EDITOR_VIEW_H__


#include "CommonDef.h"
#include <QtGui/QGraphicsView>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CIndicatorEditorView : public QGraphicsView
{
    Q_OBJECT


public:
    CIndicatorEditorView(QWidget *parent = 0);
	virtual ~CIndicatorEditorView();
public:
	void setupUi(QGraphicsView* pWindow);
	void retranslateUi(QGraphicsView *pWindow);
	EProjectClassType getClassType() const;
	int type() const;
private:
	EProjectClassType m_nClassType;
};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_VIEW_H__
