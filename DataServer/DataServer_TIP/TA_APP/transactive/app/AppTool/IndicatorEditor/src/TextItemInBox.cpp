#include <QtGui/QtGui>

#include "TextItemInBox.h"
#include "DragTextParam.h"

CTextItemInBox::CTextItemInBox(QGraphicsItem* parent, QGraphicsScene* scene, ETextItemType nTextItemType)
    : QGraphicsTextItem(parent, scene)
{
	m_nTextItemType = nTextItemType;
	m_nClassType = ClassType_CTextItemInBox;

	m_pCurrentCursor = new QCursor();
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
	m_strText = "Title";	

	this->setFont(m_TextFont);
	this->setDefaultTextColor(m_TextColor);
	this->setHtml(m_strText);

	//setAcceptsHoverEvents(true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setToolTip(QString("%1").arg("Click and drag this Item"));
	setCursor(Qt::OpenHandCursor);
	setAcceptDrops(true);

	_CreateActions();
	_CreateConnect();
}


CTextItemInBox::~CTextItemInBox()
{

	if (NULL != m_pCurrentCursor)
	{
		delete m_pCurrentCursor;
		m_pCurrentCursor = NULL;
	}

}




QVariant CTextItemInBox::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
	{
        emit selectedChange(this);
	}

    return value;
}

void CTextItemInBox::focusOutEvent(QFocusEvent* event)
{
    this->setTextInteractionFlags(Qt::NoTextInteraction);

    emit signalEditorLostFocus(this);

    QGraphicsTextItem::focusOutEvent(event);
}

void CTextItemInBox::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (this->textInteractionFlags() == Qt::NoTextInteraction)
	{
		//set can edit
        this->setTextInteractionFlags(Qt::TextEditorInteraction);
	}

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}





EProjectClassType CTextItemInBox::getClassType() const
{
	return m_nClassType;
}

int CTextItemInBox::type() const
{
	return m_nClassType;
}



void CTextItemInBox::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu;
	m_pEventScreenPos = event->screenPos();
	m_pEventScreenPos.setX(m_pEventScreenPos.x() + 50);

	menu.addAction(m_pActionSetFont);
	menu.addAction(m_pActionSetColour);
	menu.exec(event->screenPos());

	
}

void CTextItemInBox::_CreateActions()
{
	m_pActionSetFont = new QAction(QObject::tr("SetFont"), this);
	//m_pActionSetFont->setCheckable(true);
	//connect(m_pActionBlod, SIGNAL(triggered()), this, SLOT(slotFontChange()));

	m_pActionSetColour = new QAction(QObject::tr("SetColour"), this);
	//m_pActionSetColour->setCheckable(true);
}

void CTextItemInBox::_CreateConnect()
{

	connect(m_pActionSetFont, SIGNAL(triggered()), this, SLOT(slotSetFont()));
	connect(m_pActionSetColour, SIGNAL(triggered()), this, SLOT(slotSetColor()));

}

void CTextItemInBox::slotSetFont()
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

void CTextItemInBox::slotSetColor()
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



void CTextItemInBox::SetTextItemFont(const QFont& fontValue)
{
	m_TextFont = fontValue;
	this->setFont(m_TextFont);
	m_strFamily = m_TextFont.family();
	m_nPointSize = m_TextFont.pointSize();
	m_nWeight = m_TextFont.weight();
	m_bItalic = m_TextFont.italic();
	m_bUnderline = m_TextFont.underline();
}


QFont CTextItemInBox::GetTextItemFont()
{
	return m_TextFont;
}


void CTextItemInBox::SetTextItemColor(const QColor& colorValue)
{
	m_TextColor = colorValue;

	this->setDefaultTextColor(m_TextColor);

}


QColor CTextItemInBox::getTextItemColor()
{
	return m_TextColor;
}




void CTextItemInBox::mousePressEvent(QGraphicsSceneMouseEvent* pEvent)
{
	if(pEvent->button() == Qt::LeftButton)
	{
		m_pCurrentCursor->setShape(Qt::ClosedHandCursor);
		this->setCursor(*m_pCurrentCursor);
	}

	update();

	QGraphicsItem::mousePressEvent(pEvent);
}

void CTextItemInBox::mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent)
{
	QPointF pointMouse;
	QPoint pointHot;
	QPixmap pixmap;
	QPainter painter;

	QDrag* drag = NULL;
	QMimeData* mime = NULL;
	CDragTextParam* pDragTextParam = NULL;
	QPen penLine;

	{
		QPoint pointStart = pEvent->screenPos();
		QPoint pointEnd = pEvent->buttonDownScreenPos(Qt::LeftButton);
		QLineF lineStarEnd(pointStart, pointEnd);
		qreal nLineLength = lineStarEnd.length();
		qreal nLineMinLength = QApplication::startDragDistance();
		if (nLineLength < nLineMinLength)
		{
			//return;
		}
	}

	drag = new QDrag(pEvent->widget());
	mime = new QMimeData();
	pDragTextParam = new CDragTextParam();

	//init data
	pointMouse = pEvent->scenePos();
	pointHot.setX(0);
	pointHot.setY(0);
	//	m_nClassType = ClassType_CTextItemInBox;
	pDragTextParam->setParamValue(m_nClassType, m_TextColor, pointHot, m_TextFont);
	pDragTextParam->setDataToContainer(mime);



	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	
	pixmap = QPixmap(this->boundingRect().width() + 5, this->boundingRect().height() + 5);
	pixmap.fill(Qt::white);

	//paint pixmap
	painter.setRenderHint(QPainter::Antialiasing);

	painter.begin(&pixmap);
	painter.setFont(m_TextFont);
	penLine.setColor(m_TextColor);
	penLine.setWidth(1);
	painter.setPen(penLine);
	painter.drawText(QRectF(0, 0, this->boundingRect().width(), this->boundingRect().height()), m_strText);
	painter.end();
	pixmap.setMask(pixmap.createHeuristicMask());

	//set data
	drag->setMimeData(mime);
	drag->setPixmap(pixmap);
	drag->setHotSpot(pointHot);
	drag->exec(Qt::MoveAction);	//drag->exec();
	this->setCursor(Qt::OpenHandCursor);	
	this->scene()->update();//m_pSceneRef->update();

	if (NULL != pDragTextParam)
	{
		delete pDragTextParam;
		pDragTextParam = NULL;
	}
}

void CTextItemInBox::mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent)
{
	m_pCurrentCursor->setShape(Qt::OpenHandCursor);
	this->setCursor(*m_pCurrentCursor);
	update();
	QGraphicsItem::mouseReleaseEvent(pEvent);
}