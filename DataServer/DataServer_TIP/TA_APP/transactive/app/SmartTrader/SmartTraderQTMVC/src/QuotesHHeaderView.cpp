#include "QuotesHHeaderView.h"

#include <QtGui/QMenu>
#include <QtGui/QCursor>
#include <QtGui/QMessageBox>
#include <QtCore/QEvent>
#include <QtGui/QContextMenuEvent>



#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CQuotesHHeaderView::CQuotesHHeaderView( Qt::Orientation orientation /*= Qt::Horizontal*/, QWidget *parent /*= 0*/ )
:QHeaderView(orientation, parent)
{
	this->setClickable(true);
	this->setHighlightSections(true);
	this->setMovable(true);//move columns
	this->setStretchLastSection(true);
}

CQuotesHHeaderView::~CQuotesHHeaderView()
{

}

void CQuotesHHeaderView::mousePressEvent( QMouseEvent* e )
{
	if (Qt::RightButton == e->button()) 
	{
		{
			MYLOG4CPP_DEBUG<<" "<<"emit"
				<<" "<<"class:"<<"CQuotesTableViewHHeaderView"
				<<" "<<"emit"
				<<" "<<"signalMouseRightClickInHHeaderView(QMouseEvent*)"
				<<" "<<"param:"
				<<" "<<"QMouseEvent* e="<<e;

			emit signalMouseRightClickInHHeaderView(e);
		}

	}
	QHeaderView::mousePressEvent(e);
}

//QT_END_NAMESPACE










