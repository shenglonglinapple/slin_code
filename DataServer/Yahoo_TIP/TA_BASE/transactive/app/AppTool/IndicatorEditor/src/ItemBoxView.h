#ifndef __CLASS__ITEM_BOX_VIEW_H__
#define __CLASS__ITEM_BOX_VIEW_H__


#include "CommonDef.h"
#include <QtGui/QGraphicsView>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE
class CItemBoxScene;

class CItemBoxView : public QGraphicsView
{
    Q_OBJECT


public:
    CItemBoxView(QWidget *parent = 0);
	virtual ~CItemBoxView();
private:
	CItemBoxScene* m_pItemBoxScene;
private:

};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_VIEW_H__
