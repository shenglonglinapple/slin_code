#ifndef __CLASS__INSTRUMENT_INFO_VIEW_HH__
#define __CLASS__INSTRUMENT_INFO_VIEW_HH__




#include <QtCore/QModelIndex>
#include <QtGui/QMainWindow>


QT_BEGIN_NAMESPACE
class QWidget;
class QVBoxLayout;
class QTreeView;
QT_END_NAMESPACE


class CItemModelInstrumentInfo;
class CItemInstrumentInfo;


class CInstrumentInfoView : public QMainWindow
{
    Q_OBJECT

public:
    CInstrumentInfoView(QWidget* parent = 0);
	~CInstrumentInfoView();
public:
	void setupUi();
	void translateLanguage();


public slots:
	void slotInstrumentInfoChanged(CItemInstrumentInfo* pTreeItem);
	void slotTreeViewDoubleClick(const QModelIndex & index);

signals: 

private:
	void _CreateConnect();
private:
	CItemModelInstrumentInfo* m_pItemModelInstrumentInfo;

private:
	QWidget* m_pWidget_Central;
	QVBoxLayout* m_pVBoxLayout;
	QTreeView* m_pTreeView_InstrumentInfo;

};



#endif//__CLASS__INSTRUMENT_INFO_VIEW_HH__
