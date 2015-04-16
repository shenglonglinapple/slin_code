#ifndef __CLASS__DATA_FILE_NAME_WINDOW_H__
#define __CLASS__DATA_FILE_NAME_WINDOW_H__



#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListView>
#include <QtGui/QTreeView>
#include <QtCore/QStringList>
#include <QtGui/QStringListModel>
#include <QtCore/QModelIndex>




//QT_BEGIN_NAMESPACE




class CDataFileNameWindow : public QWidget
{
    Q_OBJECT


public:
    CDataFileNameWindow(QWidget* parent = 0);
	virtual ~CDataFileNameWindow();
	
public slots:
	/*
	class: QListView : public QAbstractItemView
	signals:
	void doubleClicked(const QModelIndex& index);
	fun send signals: QAbstractItemView 

	class: CDataFileNameWindow
	public slots: 
	void slotListViewDoubleClicked(const QModelIndex& index);
	*/
	void slotListViewDoubleClicked(const QModelIndex& index);
signals:
	/*
	class: CDataFileNameWindow
	signals:
	void signalShowFile(const QString&);
	fun send signals: QAbstractItemView 

	class: CIndicatorEditorWindow
	public slots: 
	void slotShowFile(const QString&);
	*/
	void signalShowFile(const QString& strFileName);

public:
	void setupUi(QWidget* pWindow);
	void retranslateUi(QWidget *pWindow);
private:
	void _CreateConnect();
private:
	QHBoxLayout* m_pHBoxLayout;

	QStringList m_StringList;
	QStringListModel* m_pStringListModel;
	QListView* m_pListView;

};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_WINDOW_H__
