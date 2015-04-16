#ifndef  __DEF__CLASS__INFORMATION_ITEM_IN_EDITOR_HH__
#define  __DEF__CLASS__INFORMATION_ITEM_IN_EDITOR_HH__


#include "CommonDef.h"

#include "InformationRectItem.h"
#include "InformationBase.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CInfomationItemInEditor : public CInformationBase
{
public:
    CInfomationItemInEditor(const QRectF& rect, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	virtual ~CInfomationItemInEditor();
public:
	EProjectClassType getClassType() const;
	int type() const;
private:
	QString m_strTextTop;//Relative history infomation
	QString m_strTextBottom;
private:
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__INFORMATION_ITEM_IN_EDITOR_HH__



////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE










