#ifndef __CLASS__INDICATOR_EDITOR_MAIN_WINDOW_H__
#define __CLASS__INDICATOR_EDITOR_MAIN_WINDOW_H__

#include "CommonDef.h"
#include <QtGui/QtGui>
#include <QtCore/QModelIndex>

#include <QtGui/QMainWindow>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTabWidget>

#include <QtGui/QWidget>
#include <QtGui/QAction>
#include <QtGui/QMenu>

#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

#include <QtGui/QMessageBox>
#include <QtGui/QCursor> 
#include <QtGui/QSlider>

#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>

//QT_BEGIN_NAMESPACE

class CIndicatorEditorWindow;
class CDataFileNameWindow;
class CItemBoxView;

class CIndicatorEditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
	enum EFontActionType
	{
		FontActionType_Begin = 0,
		FontActionType_SetValue,
		FontActionType_ShowValue,

		FontActionType_End
	};
public:
    CIndicatorEditorMainWindow(QWidget* parent = 0);
	~CIndicatorEditorMainWindow();


private slots:
	/*
	class: QButtonGroup
	signals:
	buttonClicked(int)
	fun send signals: buttonClicked(int) 

	class: CIndicatorEditorMainWindow
	public slots: 
	void slotButtonGroupPointerTypeClicked(int);
	*/
	void slotButtonGroupPointerTypeClicked(int nIndex);

	
	
	/*
	class: 
		QAction *m_pActionBlod;
		QAction *m_pActionUnderline;
		QAction *m_pActionItalic;
	signals:
	void triggered();	
	fun send signals:  
	void triggered();	

	class: CIndicatorEditorMainWindow
	public slots: 
	void slotFontChange();
	*/
	void slotFontChange();



	/*
	class: 
		QAction* m_pActionSetFontColor;
	signals:
	void triggered();	

	class: CIndicatorEditorMainWindow
	public slots: 
	void slotActionSetFontColorTriggered();
	*/
	void slotActionSetFontColorTriggered();


	/*
	class: 
		QFontComboBox* m_pComboBoxFont;
	signals:
	currentFontChanged(QFont);	

	class: CIndicatorEditorMainWindow
	public slots: 
	void slotCurrentFontChanged(const QFont& font);
	*/
	void slotCurrentFontChanged(const QFont& font);

	/*
	class: 
		QComboBox* m_pComboBoxFontSize;
	signals:
	currentIndexChanged(QString);

	class: CIndicatorEditorMainWindow
	public slots: 
	void slotFontSizeChanged(const QString& strValue);
	*/
	void slotFontSizeChanged(const QString& strValue);

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
	void slotShowFontInfo(QFont fontValue, QColor colorValue);




signals:
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
	void signalMouseActionType(EActionType nActionType);

	
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
	void signalSetFontInfo(QFont, QColor);

public:
	void retranslateUi(QMainWindow* pMainWindow);
	void setupUi(QMainWindow* pMainWindow);
	EProjectClassType getClassType() const;
	int type() const;

private:
	void _CreateActions();
	void _CreateMenus();

	void _CreateToolBars();
	void _CreateConnect();

	void _CreateToolBarColor();
	void _CreateToolBarPointerType();
	void _CreateToolBarEdit();
	void _CreateToolBarFont();

private:
	//QSplitter* m_pSqlitterV;
	QWidget* m_pWidgetCentral;
	QHBoxLayout* m_pHBoxLayout;
	QTabWidget* m_TabWidgetView;
	QTabWidget* m_TabWidgetData;

	CIndicatorEditorWindow* m_pIndicatorEditorWindow;
	CDataFileNameWindow* m_pDataFileNameWindow;
	CItemBoxView* m_pItemBoxView;
private:
	QAction* m_pActionExit;
	QAction* m_ActionDelete;
	QAction* m_pActionBlod;
	QAction* m_pActionUnderline;
	QAction* m_pActionItalic;
	QAction* m_pActionSetFontColor;

	QComboBox* m_pComboBoxFontSize;
	QFontComboBox* m_pComboBoxFont;
private:
	QColor m_colorValue;
	QFont m_FontValue;
	EFontActionType m_nFontActionType;

private:
	QMenu* m_pMenuFile;
	QButtonGroup* m_pButtonGroupPointerType;
	QToolBar* m_pToolBarText;
	QToolBar* m_pToolBarEdit;
	QToolBar* m_pToolBarColor;
	QToolBar* m_pToolBarPointer;
	QSlider* m_pSliderScale;


	EProjectClassType m_nClassType;

};

//QT_END_NAMESPACE

#endif//__CLASS__SMART_TRADER_CLIENT_MAINWINDOW_H__
