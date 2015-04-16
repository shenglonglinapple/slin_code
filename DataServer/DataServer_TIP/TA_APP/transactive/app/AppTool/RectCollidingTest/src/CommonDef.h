#ifndef  __DEF__COMMON_DEF_H_
#define  __DEF__COMMON_DEF_H_


#include <QtCore/QtGlobal>
#include <QtGui/QGraphicsItem>

//QT_BEGIN_NAMESPACE 

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef qint64          BigInt64;//%I64d
typedef qint64			UBigInt64;// %I64u ¡¢ %I64o ¡¢ %I64x
#else
typedef qint64		BigInt64;
typedef qint64		UBigInt64;
#endif




//QGraphicsItem::UserType
typedef enum en_Project_Class_Type
{
	ClassType_Begin = QGraphicsItem::UserType + 1,

	ClassType_CIndicatorEditorWindow,

	ClassType_CBoundingRect,
	ClassType_CBoundingRectAreas,

	ClassType_CInformationRectItem,

}EProjectClassType;


typedef enum en_Action_Type

{
	ActionType_InsertItem = 0, 
	ActionType_InsertLine, 
	ActionType_InsertText, 
	ActionType_MoveItem,
	ActionType_DeleteItem
}EActionType;



const qreal DEF_VALUE_InfomationRectItem_X = 100;
const qreal DEF_VALUE_InfomationRectItem_Y = 300;
const qreal DEF_VALUE_InfomationRectItem_Width = 150;
const qreal DEF_VALUE_InfomationRectItem_Height = 150;
const qreal DEF_VALUE_InfomationRectItemEdge_Width = 100;
const qreal DEF_VALUE_InfomationRectItemEdge_Height = 100;

//QT_END_NAMESPACE

#endif  // __DEF__CFDSEVER_COMMON_DEF_H_











