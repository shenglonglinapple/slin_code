#ifndef __CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__
#define __CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class CItemModelUserInstrument;

class CUserInstrumentTableView : public QTableView
{ 
public: 
	CUserInstrumentTableView(QWidget* parent = 0); 
	~CUserInstrumentTableView(); 
public:
	void slot_DataChange_UserInstrument();
private:
	CItemModelUserInstrument* m_pItemModelUserInstrument;

}; 



#endif//__CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__



