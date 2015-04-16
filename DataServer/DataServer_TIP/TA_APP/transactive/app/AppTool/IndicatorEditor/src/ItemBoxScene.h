#ifndef __CLASS__ITEM_BOX_SECNE_H__
#define __CLASS__ITEM_BOX_SECNE_H__

#include "CommonDef.h"

#include <QtGui/QtGui>
#include <QtGui/QGraphicsScene>

//QT_BEGIN_NAMESPACE


class CItemBoxScene : public QGraphicsScene
{
    Q_OBJECT



public:
    CItemBoxScene(QObject *parent = 0);
	virtual ~CItemBoxScene();

protected:
	// dragEnterEvent 当拖拽后进入接收拖拽的控件时触发
	//void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	// dragLeaveEvent 当拖拽(没有释放鼠标时)离开接收拖拽的控件时触发
	//void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	// dragMoveEvent 拖拽状态下在接收拖拽的控件内移动鼠标时触发

	//dropEvent 拖拽状态下释放鼠标时触发
	//void dropEvent(QGraphicsSceneDragDropEvent *event);
};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_SECNE_H__
