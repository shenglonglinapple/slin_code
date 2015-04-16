#ifndef __CLASS__INDICATOR_EDITOR_SECNE_H__
#define __CLASS__INDICATOR_EDITOR_SECNE_H__


#include <QtGui/QtGui>
#include <QtGui/QGraphicsScene>


class CIndicatorEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CIndicatorEditorScene(QObject *parent = 0);
	virtual ~CIndicatorEditorScene();

public slots:
	

signals:


protected:
	// dragEnterEvent 当拖拽后进入接收拖拽的控件时触发
	//void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	// dragLeaveEvent 当拖拽(没有释放鼠标时)离开接收拖拽的控件时触发
	void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	
	//dragMoveEvent 拖拽状态下在接收拖拽的控件内移动鼠标时触发
	//void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
	//dropEvent 拖拽状态下释放鼠标时触发
	//void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
	QColor m_nColor;

	QColor m_nDragColor;
	bool m_bDragOver;
};


#endif//__CLASS__INDICATOR_EDITOR_SECNE_H__
