#ifndef __DEF__CLASS__INFORMATION_TEXT_ITEM_HH__
#define __DEF__CLASS__INFORMATION_TEXT_ITEM_HH__


#include "CommonDef.h"

#include <QtGui/QtGui>

#include <QtGui/QGraphicsTextItem>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE


class CInformationTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
	enum ETextItemType
	{
		TextItemType_Begin = 0,
		TextItemType_Title,
		TextItemType_Context,

		TextItemType_End
	};
public:
    CInformationTextItem(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0, ETextItemType nTextItemType = TextItemType_Title);
	virtual ~CInformationTextItem();
	EProjectClassType getClassType() const;
    int type() const;
	QPixmap image() const;



public slots:
	void slotSetFont();
	void slotSetColor();
signals:
	/*
	signal: 
	QGraphicsTextItem
	void focusOutEvent(QFocusEvent* event);
	slot:
	CIndicatorEditorScene
	void slotEditorLostFocus(CInformationTextItem* item);
	*/
    void signalEditorLostFocus(CInformationTextItem* item);
    void selectedChange(QGraphicsItem* item);

public:
	void SetTextItemFont(const QFont& fontValue);
	QFont GetTextItemFont();
	QColor getTextItemColor();
	void SetTextItemColor(const QColor& colorValue);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    void focusOutEvent(QFocusEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent);
	void hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent);

	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
private:
	void _CreateActions();
	void _CreateConnect();
	void _SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor);
private:
	QAction* m_pActionSetFont;
	QAction* m_pActionSetColour;
	QPointF m_pEventScreenPos;
	QCursor* m_pCurrentCursor;

private:
	QFont m_TextFont;
	QColor m_TextColor;
	QString m_strFamily;
	int m_nPointSize;
	int m_nWeight;//QFont::Bold
	bool m_bItalic;
	bool m_bUnderline;
	ETextItemType m_nTextItemType;
private:
	EProjectClassType m_nClassType;


};


#endif//__DEF__CLASS__INFORMATION_TEXT_ITEM_HH__
