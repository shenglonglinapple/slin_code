#include "BoundingRect.h"


CBoundingRect::CBoundingRect( EBoundingRectType nType)
{
	m_nClassType = ClassType_CBoundingRect;

	m_nType = nType;
}

CBoundingRect::~CBoundingRect()
{

}

CBoundingRect::EBoundingRectType CBoundingRect::getRectAreaBoundingType()
{
	return m_nType;
}

void CBoundingRect::setRectAreaBoundingType( EBoundingRectType nType )
{
	m_nType = nType;
}

EProjectClassType CBoundingRect::getClassType() const
{
	return m_nClassType;
}

int CBoundingRect::type() const
{
	return m_nClassType;
}



