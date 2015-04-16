#include "DragTextParam.h"



static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_ClassType = "Param_ClassType";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_RectHotXValue = "Param_RectHotXValue";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_RectHotYValue = "Param_RectHotYValue";

static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextFont = "Param_TextFont";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_PointSize = "Param_TextFont_PointSize";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_Weight = "Param_TextFont_Weight";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_bItalic = "Param_TextFont_Italic";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_Underline = "Param_TextFont_Underline";



CDragTextParam::CDragTextParam()
{
	m_nClassType = ClassType_CDragTextParam;
}

CDragTextParam::~CDragTextParam()
{

}
void CDragTextParam::setParamValue(EProjectClassType nItemType,
								   const QColor& TextColor,
								   const QPoint& pointHot, 
								   const QFont& TextFont
								   )
{
	m_nDataType = m_nClassType;
	m_nDragItemType = nItemType;
	m_TextColor = TextColor;	
	m_pointHot = pointHot;
	m_TextFont = TextFont;
	m_TextFontPointSize = m_TextFont.pointSize();
	m_TextFontWeight = m_TextFont.weight();
	m_TextFontItalic = m_TextFont.italic();
	m_TextFontUnderline = m_TextFont.underline();

	this->m_strDataType = QString("%1").arg(this->m_nDataType);//"ClassType_CDragTextParam";
	this->m_TextColor = m_TextColor;
	this->m_strParamClassType = QString("%1").arg(this->m_nDragItemType);//ClassType_CTextItemInBox
	this->m_strParamRectHotXValue = QString("%1").arg(pointHot.x());//hot x
	this->m_strParamRectHotYValue = QString("%1").arg(pointHot.y());//hot y

	this->m_strParamTextTopFont = m_TextFont.toString();
	this->m_strParamTextTopFontPointSize = QString("%1").arg(m_TextFontPointSize);
	this->m_strParamTextTopFontWeight = QString("%1").arg(m_TextFontWeight);
	this->m_strParamTextTopFontItalic = QString("%1").arg(m_TextFontItalic);
	this->m_strParamTextTopFontUnderline = QString("%1").arg(m_TextFontUnderline);
}

void CDragTextParam::setDataToContainer(QMimeData* mime)
{
	if (NULL == mime)
	{
		return;
	}

	mime->setText(this->m_strDataType);//ClassType_CInfomationItemInEditor
	mime->setColorData(this->m_TextColor);//
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_ClassType.c_str(), QByteArray(this->m_strParamClassType.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotXValue.c_str(), QByteArray(this->m_strParamRectHotXValue.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotYValue.c_str(), QByteArray(this->m_strParamRectHotYValue.toStdString().c_str()));

	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont.c_str(), QByteArray(this->m_strParamTextTopFont.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_PointSize.c_str(), QByteArray(this->m_strParamTextTopFontPointSize.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_Weight.c_str(), QByteArray(this->m_strParamTextTopFontWeight.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_bItalic.c_str(), QByteArray(this->m_strParamTextTopFontItalic.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_Underline.c_str(), QByteArray(this->m_strParamTextTopFontUnderline.toStdString().c_str()));




}


//const QMimeData *mimeData(

void CDragTextParam::getDataFromContainer(const QMimeData* mime)
{
	if (NULL == mime)
	{
		return;
	}
	this->m_strDataType = qvariant_cast<QString>(mime->text());
	this->m_TextColor = qvariant_cast<QColor>(mime->colorData());

	this->m_strParamClassType = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_ClassType.c_str()).data());
	this->m_strParamRectHotXValue = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotXValue.c_str()).data());
	this->m_strParamRectHotYValue = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotYValue.c_str()).data());

	this->m_strParamTextTopFont = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont.c_str()).data());
	this->m_strParamTextTopFontPointSize = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_PointSize.c_str()).data());
	this->m_strParamTextTopFontWeight = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_Weight.c_str()).data());
	this->m_strParamTextTopFontItalic = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_bItalic.c_str()).data());
	this->m_strParamTextTopFontUnderline = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextFont_Underline.c_str()).data());

	m_nDataType = (EProjectClassType)(this->m_strDataType.toInt());
	m_nDragItemType = (EProjectClassType)(this->m_strParamClassType.toInt());
	m_TextColor = this->m_TextColor;
	m_pointHot = QPoint(this->m_strParamRectHotXValue.toInt(), this->m_strParamRectHotYValue.toInt());
	m_TextFont = QFont(this->m_strParamTextTopFont);
	m_TextFontPointSize = this->m_strParamTextTopFontPointSize.toInt();
	m_TextFontWeight = this->m_strParamTextTopFontWeight.toInt();
	m_TextFontItalic = (bool)(this->m_strParamTextTopFontItalic.toInt());
	m_TextFontUnderline = (bool)(this->m_strParamTextTopFontUnderline.toInt());
	m_TextFont.setPointSize(m_TextFontPointSize);
	m_TextFont.setWeight(m_TextFontWeight);
	m_TextFont.setItalic(m_TextFontItalic);
	m_TextFont.setUnderline(m_TextFontUnderline);

}
void CDragTextParam::getParamValue(EProjectClassType& nItemType, 
								   QColor& TextColor,
								   QPoint& pointHot, 
								   QFont& TextFont
								   )
{
	nItemType = m_nDragItemType;
	TextColor = m_TextColor;
	pointHot = m_pointHot;
	TextFont = m_TextFont;
}



