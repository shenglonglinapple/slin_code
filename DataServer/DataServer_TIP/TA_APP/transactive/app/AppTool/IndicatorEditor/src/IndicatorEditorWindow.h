#ifndef __CLASS__INDICATOR_EDITOR_WINDOW_H__
#define __CLASS__INDICATOR_EDITOR_WINDOW_H__


#include "CommonDef.h"
#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>

//QT_BEGIN_NAMESPACE

class CIndicatorEditorView;
class CIndicatorEditorScene;


class CIndicatorEditorWindow : public QWidget
{
    Q_OBJECT


public:
    CIndicatorEditorWindow(QWidget* parent = 0);
	virtual ~CIndicatorEditorWindow();


		
public slots:
	/*
	class: CDataFileNameWindow
	signals:
	void signalShowFile(const QString&);
	fun send signals: QAbstractItemView 

	class: CIndicatorEditorWindow
	public slots: 
	void slotShowFile(const QString&);
	*/
	void slotShowFile(const QString& strFileName);


	/*
	class: CIndicatorEditorMainWindow
	signals:
	void signalMouseActionType(EActionType nActionType);	
	fun send signals:  
	void slotButtonGroupClicked( int nIndex );

	class: CIndicatorEditorWindow
	public slots: 
	void slotMouseActionType(EActionType nActionType);
	*/
	void slotMouseActionType(EActionType nActionType);

	
	/*
	class: QSlider
	signals:
	valueChanged(int)
	fun send signals: 
	valueChanged(int)

	class: CIndicatorEditorWindow
	public slots: 
	void slotSceneScaleChanged(int);
	*/
	void slotSceneScaleChanged(int nScaleVale);


	/*
	class: ActionDelete
	signals:
	triggered()
	fun send signals: 
	triggered()

	class: CIndicatorEditorWindow
	public slots: 
	void slotActionDeleteTriggered(QString);
	*/
	void slotActionDeleteTriggered();

	/*
	class: CIndicatorEditorScene
	signals:
	singnalItemSelected(QGraphicsItem*)

	class: CIndicatorEditorWindow
	public slots: 
	void slotItemSelectedInScene(QGraphicsItem* item);
	*/
	void slotItemSelectedInScene(QGraphicsItem* item);


	/*
	class: CIndicatorEditorMainWindow
	signals:
	void signalSetFontInfo(QFont fontValue,QColor colorValue);
	fun send signals:  
	void slotButtonGroupClicked( int nIndex );

	class: CIndicatorEditorWindow
	public slots: 
	void slotSetFontInfo(QFont fontValue,QColor colorValue);
	*/
	void slotSetFontInfo(QFont fontValue,QColor colorValue);
signals:
	/*
	class: CIndicatorEditorWindow
	signals:
	void signalShowFontInfo(QFont fontValue, QColor colorValue);
	fun send signals:  
	void slotItemSelectedInScene( QGraphicsItem* item);

	class:  CIndicatorEditorMainWindow
	public slots: 
	void slotShowFontInfo(QFont fontValue, QColor colorValue);
	*/
	void signalShowFontInfo(QFont fontValue, QColor colorValue);

public:
	void setupUi(QWidget* pWindow);
	void retranslateUi(QWidget* pWindow);

	EProjectClassType getClassType() const;
	int type() const;
private:
	void _CreateConnect();
private:
	QHBoxLayout* m_pHBoxLayout;
	CIndicatorEditorView* m_pIndicatorEditorView;
	CIndicatorEditorScene* m_pIndicatorEditorScene;
	QRectF m_rectScene;
	EProjectClassType m_nClassType;
};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_WINDOW_H__
