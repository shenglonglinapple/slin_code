#ifndef  __DEF__CLASS__MYRECT_HH__
#define  __DEF__CLASS__MYRECT_HH__

#include <QtGui/QWidget>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>

#include "MyRectGraphicsItem.h"

class CMyRectData;

class CMyRect : public QWidget
{
	Q_OBJECT

public:
	CMyRect(QWidget* parent = 0);  
	virtual ~CMyRect(); 
public:

private:
	void paintEvent(QPaintEvent *pEvent);
private:
	void _SetupWidgetUi();
protected:
	CMyRectData* m_pData;
private:
	QGraphicsView* m_pGraphicsView;
	QGraphicsScene* m_pGraphicsScene;
	CMyRectGraphicsItem* m_pMyRectGraphicsItem;
};


#endif //__DEF__CLASS__MYRECT_HH__




