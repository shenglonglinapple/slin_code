#include "InfomationItemInEditor.h"
#include "InformationRectItem.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

static const std::string DEF_VALUE_CInfomationItemInEditor_TopText = "Top Text";
static const std::string DEF_VALUE_CInfomationItemInEditor_BottomText = "Bottom Text";

CInfomationItemInEditor::CInfomationItemInEditor(const QRectF& rect, QGraphicsItem* parent, QGraphicsScene* scene)
:CInformationBase(rect, parent)
{
	m_nClassType = ClassType_CInfomationItemInEditor;

	m_strTextTop = QString(DEF_VALUE_CInfomationItemInEditor_TopText.c_str());
	m_strTextBottom = QString(DEF_VALUE_CInfomationItemInEditor_BottomText.c_str());

	this->setTopText(m_strTextTop);
	this->setBottomText(m_strTextBottom);

}

CInfomationItemInEditor::~CInfomationItemInEditor()
{

}


EProjectClassType CInfomationItemInEditor::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CInfomationItemInEditor::type() const
{
	return m_nClassType;
}

////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE



