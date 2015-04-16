#ifndef __CLASS__INDICATOR_EDITOR_SECNE_H__
#define __CLASS__INDICATOR_EDITOR_SECNE_H__

#include "CommonDef.h"

#include <QtGui/QtGui>
#include <QtGui/QGraphicsScene>

//QT_BEGIN_NAMESPACE

class CSceneInsertTitleParam;
class CSceneInsertLineParam;
class CSceneInsertRectParam;
class CInformationTextItem;

class CIndicatorEditorScene : public QGraphicsScene
{
    Q_OBJECT



public:
    CIndicatorEditorScene(QObject *parent = 0);
	virtual ~CIndicatorEditorScene();

public slots:
	void slotActionDeleteTriggered();
	void slotEditorLostFocus(CInformationTextItem* item);

signals:
	/*
	class: CIndicatorEditorScene
	signals:
	singnalItemSelected(QGraphicsItem*)

	class: CIndicatorEditorWindow
	public slots: 
	void slotItemSelectedInScene(QGraphicsItem*);
	*/
	void singnalItemSelectedInScene(QGraphicsItem* item);

public:
	void setupUi(QGraphicsScene* pWindow);
	void retranslateUi(QGraphicsScene *pWindow);

public:
	EProjectClassType getClassType() const;
	int type() const;
	void setActionType(EActionType nActionType);

	QFont getEditorSceneFont() const;
	
	void setEditorSceneFont( const QFont& fontValue, const QColor& colorValue);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
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
	bool _IsItemChange(int nTypeValue);
	void _InsertRect(CSceneInsertRectParam* pSceneInsertRectParam);
	void _InsertLine(CSceneInsertLineParam* pSceneInsertLineParam);
	void _InsertTitle(CSceneInsertTitleParam* pSceneInsertTitleParam);
private:
	EProjectClassType m_nClassType;
	EActionType m_nActionType;

private:
	QFont m_fontInScene;
	QColor m_colorInScene;
	QColor m_LineColor;
	QGraphicsLineItem* m_pGraphicsLineItemTmp;
};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_SECNE_H__
