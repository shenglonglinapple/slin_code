#include <QtGui/QtGui>

#include "InformationTextItem.h"

CInformationTextItem::CInformationTextItem(QGraphicsItem* parent, QGraphicsScene* scene, ETextItemType nTextItemType)
    : QGraphicsTextItem(parent, scene)
{
	m_nTextItemType = nTextItemType;

	m_pCurrentCursor = NULL;
	m_pCurrentCursor = new QCursor();


	m_nClassType = ClassType_CInformationTextItem;
	m_pEventScreenPos = this->scenePos();
	
	if (TextItemType_Title == m_nTextItemType)
	{
		m_strFamily = "Helvetica";
		m_nPointSize = 30;
		m_nWeight = QFont::Bold;
		m_bItalic = false;
		m_bUnderline = false;
		m_TextColor = Qt::black;
	}
	else //if (TextItemType_Context == m_nTextItemType)
	{
		m_strFamily = "Helvetica";
		m_nPointSize = 10;
		m_nWeight = QFont::Bold;
		m_bItalic = false;
		m_bUnderline = false;
		m_TextColor = Qt::black;
	}
	m_TextFont = QFont(m_strFamily, m_nPointSize, m_nWeight, m_bItalic);

	this->setFont(m_TextFont);
	this->setDefaultTextColor(m_TextColor);

	setAcceptsHoverEvents(true);

	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);

	_CreateActions();
	_CreateConnect();
}


CInformationTextItem::~CInformationTextItem()
{

	if (NULL != m_pCurrentCursor)
	{
		delete m_pCurrentCursor;
		m_pCurrentCursor = NULL;
	}

}




QVariant CInformationTextItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
	{
        emit selectedChange(this);
	}

    return value;
}

void CInformationTextItem::focusOutEvent(QFocusEvent* event)
{
    this->setTextInteractionFlags(Qt::NoTextInteraction);

    emit signalEditorLostFocus(this);

    QGraphicsTextItem::focusOutEvent(event);
}

void CInformationTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (this->textInteractionFlags() == Qt::NoTextInteraction)
	{
		//set can edit
        this->setTextInteractionFlags(Qt::TextEditorInteraction);
	}

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}



QPixmap CInformationTextItem::image() const
{
	QPixmap pixmap(":/images/textpointer.png");
	//QPixmap pixmap(":/images/textpointer.png").scaled(30, 30);

	return pixmap;
}

EProjectClassType CInformationTextItem::getClassType() const
{
	return m_nClassType;
}

int CInformationTextItem::type() const
{
	return m_nClassType;
}



void CInformationTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu;
	m_pEventScreenPos = event->screenPos();
	m_pEventScreenPos.setX(m_pEventScreenPos.x() + 50);

	menu.addAction(m_pActionSetFont);
	menu.addAction(m_pActionSetColour);
	menu.exec(event->screenPos());

	
}

void CInformationTextItem::_CreateActions()
{
	m_pActionSetFont = new QAction(QObject::tr("SetFont"), this);
	//m_pActionSetFont->setCheckable(true);
	//connect(m_pActionBlod, SIGNAL(triggered()), this, SLOT(slotFontChange()));

	m_pActionSetColour = new QAction(QObject::tr("SetColour"), this);
	//m_pActionSetColour->setCheckable(true);
}

void CInformationTextItem::_CreateConnect()
{

	connect(m_pActionSetFont, SIGNAL(triggered()), this, SLOT(slotSetFont()));
	connect(m_pActionSetColour, SIGNAL(triggered()), this, SLOT(slotSetColor()));

}

void CInformationTextItem::slotSetFont()
{
	//m_pEventScreenPos
	bool bTriggerOK = false;
	m_TextFont = QFontDialog::getFont(
		&bTriggerOK,
		this->font(),
		NULL,
		QObject::tr("fontDialog"));

	if (bTriggerOK)
	{
		this->setFont(m_TextFont);
		m_strFamily = m_TextFont.family();
		m_nPointSize = m_TextFont.pointSize();
		m_nWeight = m_TextFont.weight();
		m_bItalic = m_TextFont.italic();
		m_bUnderline = m_TextFont.underline();
	}
	this->adjustSize();

	emit selectedChange(this);
}

void CInformationTextItem::slotSetColor()
{
	QColor colorValue;

	colorValue = QColorDialog::getColor(
		m_TextColor, 
		NULL, 
		QObject::tr("ColorDialog"));

	if (colorValue.isValid())
	{
		m_TextColor = colorValue;

		//textitem1->setHtml("<h2><font color=green size=2>-75</font></h2>");
		this->setDefaultTextColor(m_TextColor);
		emit selectedChange(this);
	}
}



void CInformationTextItem::SetTextItemFont(const QFont& fontValue)
{
	m_TextFont = fontValue;
	this->setFont(m_TextFont);
	m_strFamily = m_TextFont.family();
	m_nPointSize = m_TextFont.pointSize();
	m_nWeight = m_TextFont.weight();
	m_bItalic = m_TextFont.italic();
	m_bUnderline = m_TextFont.underline();
}


QFont CInformationTextItem::GetTextItemFont()
{
	return m_TextFont;
}


void CInformationTextItem::SetTextItemColor(const QColor& colorValue)
{
	m_TextColor = colorValue;

	this->setDefaultTextColor(m_TextColor);

}


QColor CInformationTextItem::getTextItemColor()
{
	return m_TextColor;
}

void CInformationTextItem::hoverEnterEvent( QGraphicsSceneHoverEvent* pEvent )
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();
	_SetCursorShape(pointCurrent, m_pCurrentCursor);
	this->setCursor(*m_pCurrentCursor);
	this->update();
	QGraphicsTextItem::hoverEnterEvent(pEvent);
}

void CInformationTextItem::hoverMoveEvent( QGraphicsSceneHoverEvent* pEvent )
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();
	_SetCursorShape(pointCurrent, m_pCurrentCursor);
	this->setCursor(*m_pCurrentCursor);
	this->update();
	QGraphicsTextItem::hoverMoveEvent(pEvent);
}

void CInformationTextItem::hoverLeaveEvent( QGraphicsSceneHoverEvent* pEvent )
{
	m_pCurrentCursor->setShape(Qt::ArrowCursor);
	this->setCursor(*m_pCurrentCursor);
	update();
	QGraphicsTextItem::hoverLeaveEvent(pEvent);
}


void CInformationTextItem::_SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor)
{			
	pCurrentCursor->setShape(Qt::IBeamCursor);
}
