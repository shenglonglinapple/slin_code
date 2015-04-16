#include "DragRectParam.h"



static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_ClassType = "Param_ClassType";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_RectHotXValue = "Param_RectHotXValue";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_RectHotYValue = "Param_RectHotYValue";

static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont = "Param_TextTopFont";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_PointSize = "Param_TextTopFont_PointSize";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_Weight = "Param_TextTopFont_Weight";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_bItalic = "Param_TextTopFont_Italic";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_Underline = "Param_TextTopFont_Underline";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorR = "Param_TextTopColorR";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorG = "Param_TextTopColorG";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorB = "Param_TextTopColorB";

static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont = "Param_TextBottomFont";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_PointSize = "Param_TextBottomFont_PointSize";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_Weight = "Param_TextBottomFont_Weight";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_bItalic = "Param_TextBottomFont_Italic";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_Underline = "Param_TextBottomFont_Underline";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorR = "Param_TextBottomColorR";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorG = "Param_TextBottomColorG";
static const std::string DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorB = "Param_TextBottomColorB";


CDragRectParam::CDragRectParam()
{
	m_nClassType = ClassType_CDragRectParam;
}

CDragRectParam::~CDragRectParam()
{

}

void CDragRectParam::setParamValue(EProjectClassType nRectItemType,
								   const QColor& RectLineColor,
								   const QPoint& pointHot, 
								   const QFont& TextFontTop,
								   const QColor& TextColorTop,
								   const QFont& TextFontBottom,
								   const QColor& TextColorBottom
								   )
{
	m_nDataType = m_nClassType;//ClassType_CDragRectParam
	m_nDragItemType = nRectItemType;
	m_RectLineColor = RectLineColor;	
	m_pointHot = pointHot;
	m_TextFontTop = TextFontTop;
	m_TextFontTopPointSize = m_TextFontTop.pointSize();
	m_TextFontTopWeight = m_TextFontTop.weight();
	m_TextFontTopItalic = m_TextFontTop.italic();
	m_TextFontTopUnderline = m_TextFontTop.underline();
	m_TextColorTop = TextColorTop;
	m_TextFontBottom = TextFontBottom;
	m_TextFontBottomPointSize = m_TextFontBottom.pointSize();
	m_TextFontBottomWeight = m_TextFontBottom.weight();
	m_TextFontBottomItalic = m_TextFontBottom.italic();
	m_TextFontBottomUnderline = m_TextFontBottom.underline();
	m_TextColorBottom = TextColorBottom;

	this->m_strDataType = QString("%1").arg(this->m_nDataType);//"ClassType_CDragRectParam";
	this->m_RectLineColor = RectLineColor;
	this->m_strParamClassType = QString("%1").arg(this->m_nDragItemType);//ClassType_CRectItemInBox
	this->m_strParamRectHotXValue = QString("%1").arg(pointHot.x());//hot x
	this->m_strParamRectHotYValue = QString("%1").arg(pointHot.y());//hot y

	this->m_strParamTextTopFont = TextFontTop.toString();
	this->m_strParamTextTopFontPointSize = QString("%1").arg(m_TextFontTopPointSize);
	this->m_strParamTextTopFontWeight = QString("%1").arg(m_TextFontTopWeight);
	this->m_strParamTextTopFontItalic = QString("%1").arg(m_TextFontTopItalic);
	this->m_strParamTextTopFontUnderline = QString("%1").arg(m_TextFontTopUnderline);
	this->m_strParamTextTopColorR = QString("%1").arg(TextColorTop.red());
	this->m_strParamTextTopColorG = QString("%1").arg(TextColorTop.green());
	this->m_strParamTextTopColorB = QString("%1").arg(TextColorTop.blue());

	this->m_strParamTextBottomFont = TextFontBottom.toString();
	this->m_strParamTextBottomFontPointSize = QString("%1").arg(m_TextFontBottomPointSize);
	this->m_strParamTextBottomFontWeight = QString("%1").arg(m_TextFontBottomWeight);
	this->m_strParamTextBottomFontItalic = QString("%1").arg(m_TextFontBottomItalic);
	this->m_strParamTextBottomFontUnderline = QString("%1").arg(m_TextFontBottomUnderline);
	this->m_strParamTextBottomColorR = QString("%1").arg(TextColorBottom.red());
	this->m_strParamTextBottomColorG = QString("%1").arg(TextColorBottom.green());
	this->m_strParamTextBottomColorB = QString("%1").arg(TextColorBottom.blue());

}

void CDragRectParam::setDataToContainer(QMimeData* mime)
{
	if (NULL == mime)
	{
		return;
	}

	mime->setText(this->m_strDataType);//ClassType_CDragRectParam
	mime->setColorData(this->m_RectLineColor);//
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_ClassType.c_str(), QByteArray(this->m_strParamClassType.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotXValue.c_str(), QByteArray(this->m_strParamRectHotXValue.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotYValue.c_str(), QByteArray(this->m_strParamRectHotYValue.toStdString().c_str()));

	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont.c_str(), QByteArray(this->m_strParamTextTopFont.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_PointSize.c_str(), QByteArray(this->m_strParamTextTopFontPointSize.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_Weight.c_str(), QByteArray(this->m_strParamTextTopFontWeight.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_bItalic.c_str(), QByteArray(this->m_strParamTextTopFontItalic.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_Underline.c_str(), QByteArray(this->m_strParamTextTopFontUnderline.toStdString().c_str()));


	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorR.c_str(), QByteArray(this->m_strParamTextTopColorR.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorG.c_str(), QByteArray(this->m_strParamTextTopColorG.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorB.c_str(), QByteArray(this->m_strParamTextTopColorB.toStdString().c_str()));

	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont.c_str(), QByteArray(this->m_strParamTextBottomFont.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_PointSize.c_str(), QByteArray(this->m_strParamTextBottomFontPointSize.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_Weight.c_str(), QByteArray(this->m_strParamTextBottomFontWeight.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_bItalic.c_str(), QByteArray(this->m_strParamTextBottomFontItalic.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_Underline.c_str(), QByteArray(this->m_strParamTextBottomFontUnderline.toStdString().c_str()));

	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorR.c_str(), QByteArray(this->m_strParamTextBottomColorR.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorG.c_str(), QByteArray(this->m_strParamTextBottomColorG.toStdString().c_str()));
	mime->setData(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorB.c_str(), QByteArray(this->m_strParamTextBottomColorB.toStdString().c_str()));

}


//const QMimeData *mimeData(

void CDragRectParam::getDataFromContainer(const QMimeData* mime)
{
	if (NULL == mime)
	{
		return;
	}
	this->m_strDataType = qvariant_cast<QString>(mime->text());
	this->m_RectLineColor = qvariant_cast<QColor>(mime->colorData());

	this->m_strParamClassType = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_ClassType.c_str()).data());
	this->m_strParamRectHotXValue = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotXValue.c_str()).data());
	this->m_strParamRectHotYValue = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_RectHotYValue.c_str()).data());

	this->m_strParamTextTopFont = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont.c_str()).data());
	this->m_strParamTextTopFontPointSize = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_PointSize.c_str()).data());
	this->m_strParamTextTopFontWeight = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_Weight.c_str()).data());
	this->m_strParamTextTopFontItalic = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_bItalic.c_str()).data());
	this->m_strParamTextTopFontUnderline = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopFont_Underline.c_str()).data());

	this->m_strParamTextTopColorR = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorR.c_str()).data());
	this->m_strParamTextTopColorG = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorG.c_str()).data());
	this->m_strParamTextTopColorB = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextTopColorB.c_str()).data());

	this->m_strParamTextBottomFont = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont.c_str()).data());
	this->m_strParamTextBottomFontPointSize = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_PointSize.c_str()).data());
	this->m_strParamTextBottomFontWeight = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_Weight.c_str()).data());
	this->m_strParamTextBottomFontItalic = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_bItalic.c_str()).data());
	this->m_strParamTextBottomFontUnderline = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomFont_Underline.c_str()).data());

	this->m_strParamTextBottomColorR = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorR.c_str()).data());
	this->m_strParamTextBottomColorG = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorG.c_str()).data());
	this->m_strParamTextBottomColorB = QString(mime->data(DEFVALUE_String_QDRAG_QMimeData_Param_TextBottomColorB.c_str()).data());

	//m_nRectItemType = (EProjectClassType)(this->m_strParamClassType.toInt());
	m_nDataType = (EProjectClassType)(this->m_strDataType.toInt());
	m_RectLineColor = this->m_RectLineColor;
	m_nDragItemType = (EProjectClassType)(this->m_strParamClassType.toInt());
	m_pointHot = QPoint(this->m_strParamRectHotXValue.toInt(), this->m_strParamRectHotYValue.toInt());
	m_TextFontTop = QFont(this->m_strParamTextTopFont);
	m_TextFontTopPointSize = this->m_strParamTextTopFontPointSize.toInt();
	m_TextFontTopWeight = this->m_strParamTextTopFontWeight.toInt();
	m_TextFontTopItalic = (bool)(this->m_strParamTextTopFontItalic.toInt());
	m_TextFontTopUnderline = (bool)(this->m_strParamTextTopFontUnderline.toInt());
	m_TextFontTop.setPointSize(m_TextFontTopPointSize);
	m_TextFontTop.setWeight(m_TextFontTopWeight);
	m_TextFontTop.setItalic(m_TextFontTopItalic);
	m_TextFontTop.setUnderline(m_TextFontTopUnderline);
	m_TextColorTop = QColor(this->m_strParamTextTopColorR.toInt(), this->m_strParamTextTopColorG.toInt(), this->m_strParamTextTopColorB.toInt());

	m_TextFontBottom = QFont(this->m_strParamTextBottomFont);
	m_TextFontBottomPointSize = this->m_strParamTextBottomFontPointSize.toInt();
	m_TextFontBottomWeight = this->m_strParamTextBottomFontWeight.toInt();
	m_TextFontBottomItalic = (bool)(this->m_strParamTextBottomFontItalic.toInt());
	m_TextFontBottomUnderline = (bool)(this->m_strParamTextBottomFontUnderline.toInt());
	m_TextFontBottom.setPointSize(m_TextFontBottomPointSize);
	m_TextFontBottom.setWeight(m_TextFontBottomWeight);
	m_TextFontBottom.setItalic(m_TextFontBottomItalic);
	m_TextFontBottom.setUnderline(m_TextFontBottomUnderline);
	m_TextColorBottom = QColor(this->m_strParamTextBottomColorR.toInt(), this->m_strParamTextBottomColorG.toInt(), this->m_strParamTextBottomColorB.toInt());
}
void CDragRectParam::getParamValue(EProjectClassType& nRectItemType, 
								   QColor& RectLineColor,
								   QPoint& pointHot, 
								   QFont& TextFontTop,
								   QColor& TextColorTop,
								   QFont& TextFontBottom,
								   QColor& TextColorBottom
								   )
{
	nRectItemType = m_nDragItemType;
	RectLineColor = m_RectLineColor;
	pointHot = m_pointHot;
	TextFontTop = m_TextFontTop;
	TextColorTop = m_TextColorTop;
	TextFontBottom = m_TextFontBottom;
	TextColorBottom = m_TextColorBottom;
}