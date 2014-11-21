#include "UserInstrumentInfoHeaderView.h"

#include <QtGui/QMenu>
#include <QtGui/QCursor>
#include <QtGui/QMessageBox>
#include <QtCore/QEvent>
#include <QtGui/QContextMenuEvent>



#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CUserInstrumentInfoHeaderView::CUserInstrumentInfoHeaderView( Qt::Orientation orientation /*= Qt::Horizontal*/, QWidget *parent /*= 0*/ )
:QHeaderView(orientation, parent)
{
	this->setClickable(true);
	this->setHighlightSections(true);
	this->setMovable(true);//move columns
	this->setStretchLastSection(true);
}

CUserInstrumentInfoHeaderView::~CUserInstrumentInfoHeaderView()
{

}

void CUserInstrumentInfoHeaderView::mousePressEvent( QMouseEvent* e )
{
	if (Qt::RightButton == e->button()) 
	{
		{
			MYLOG4CPP_DEBUG<<" "<<"emit"
				<<" "<<"class:"<<"CQuotesHHeaderView"
				<<" "<<"fun:"<<"mousePressEvent"
				<<" "<<"emit"
				<<" "<<"signalMouseRightClickInHHeaderView(QMouseEvent*)"
				<<" "<<"param:"
				<<" "<<"QMouseEvent* e=0x"<<e;

			emit signalMouseRightClickInHHeaderView(e);
		}

	}
	QHeaderView::mousePressEvent(e);
}

//QT_END_NAMESPACE










