#ifndef __CLASS__INDICATOR_EDITOR_WINDOW_H__
#define __CLASS__INDICATOR_EDITOR_WINDOW_H__


#include "CommonDef.h"
#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>


//QT_BEGIN_NAMESPACE


class CIndicatorEditorWindow : public QWidget
{
    Q_OBJECT
public:
    CIndicatorEditorWindow(QWidget* parent = 0);
	virtual ~CIndicatorEditorWindow();

public slots:

signals:

public:
	void setupUi(QWidget* pWindow);
	void retranslateUi(QWidget *pWindow);

	EProjectClassType getClassType() const;
	int type() const;
private:
	void _AddRects();

private:
	QHBoxLayout* m_pHBoxLayout;
	QGraphicsView* m_pIndicatorEditorView;
	QGraphicsScene* m_pIndicatorEditorScene;
	QRectF m_rectScene;
	EProjectClassType m_nClassType;
};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_WINDOW_H__
