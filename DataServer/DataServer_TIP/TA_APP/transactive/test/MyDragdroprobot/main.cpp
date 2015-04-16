#include <QtGui>

#include "coloritem.h"
#include "robot.h"
#include "RectItem.h"

#include <math.h>

#include "IndicatorEditorView.h"
#include "IndicatorEditorScene.h"
#include "IndicatorToolView.h"
#include "IndicatorToolScene.h"

//! [0]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	CIndicatorToolScene* pToolScene = NULL;
	CIndicatorToolView* pToolView = NULL;
	CIndicatorEditorScene* pSceneTwo = NULL;
	CIndicatorEditorView* pViewTwo = NULL;

	//////////////////////////////////////////////////////////////////////////
	pToolScene = new CIndicatorToolScene(NULL);
	pToolView = new CIndicatorToolView(NULL);

	pToolScene->setSceneRect(-200, -200, 1000, 1000);

	for (int nIndex = 0; nIndex < 2; ++nIndex) 
	{
		//ColorItem* pItem = new ColorItem();
		//pItem->setPos(::sin((i * 3.14 * 2) / 10.0) * 150, ::cos((i * 3.14 * 2) / 10.0) * 150);
		//pSceneTwo->addItem(pItem);

		CRectItem* pItem = new CRectItem(NULL, pToolScene); 
		pItem->setItemPos(QPointF(nIndex * 200, nIndex * 200));
		pToolScene->addItem(pItem);
    }

	pToolView->setScene(pToolScene);    
    pToolView->setRenderHint(QPainter::Antialiasing);
    pToolView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //pViewOne->setBackgroundBrush(QColor(230, 200, 167));
	//pViewOne->setBackgroundBrush(QColor(0, 200, 0));
    pToolView->setWindowTitle("Drag and Drop Robot");
	pToolView->move(300,300);
	pToolView->resize(300, 600);
    pToolView->show();
	//////////////////////////////////////////////////////////////////////////

	pSceneTwo = new CIndicatorEditorScene(NULL);
	pViewTwo = new CIndicatorEditorView(NULL);

	pSceneTwo->setSceneRect(-200, -200, 1000, 1000);

	for (int nIndex = 0; nIndex < 2; ++nIndex) 
	{
		//ColorItem* pItem = new ColorItem();
		//pItem->setPos(::sin((i * 3.14 * 2) / 10.0) * 150, ::cos((i * 3.14 * 2) / 10.0) * 150);
		//pSceneTwo->addItem(pItem);

		CRectItem* pItem = new CRectItem(NULL, pSceneTwo); 
		pItem->setItemPos(QPointF(nIndex * 200, nIndex * 200));
		pSceneTwo->addItem(pItem);
	}

	pViewTwo->setScene(pSceneTwo);
	pViewTwo->setRenderHint(QPainter::Antialiasing);
	pViewTwo->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	//pViewOne->setBackgroundBrush(QColor(230, 200, 167));
	//pViewOne->setBackgroundBrush(QColor(0, 200, 0));
	pViewTwo->setWindowTitle("Drag and Drop Robot");
	pViewTwo->move(900,300);
	pViewTwo->resize(600, 600);
	pViewTwo->show();





    return app.exec();
}
//! [2]
