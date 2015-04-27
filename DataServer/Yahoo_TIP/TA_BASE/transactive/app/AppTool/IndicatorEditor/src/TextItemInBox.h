#ifndef __DEF__CLASS__TEXT_ITEM_IN_BOX_HH__
#define __DEF__CLASS__TEXT_ITEM_IN_BOX_HH__


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


class CTextItemInBox : public QGraphicsTextItem
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
    CTextItemInBox(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0, ETextItemType nTextItemType = TextItemType_Title);
	virtual ~CTextItemInBox();
	EProjectClassType getClassType() const;
    int type() const;



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
    void signalEditorLostFocus(CTextItemInBox* item);
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
	void mousePressEvent(QGraphicsSceneMouseEvent* pEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent);

	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
private:
	void _CreateActions();
	void _CreateConnect();
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
	QString m_strText;
private:
	EProjectClassType m_nClassType;


};


#endif//__DEF__CLASS__TEXT_ITEM_IN_BOX_HH__
