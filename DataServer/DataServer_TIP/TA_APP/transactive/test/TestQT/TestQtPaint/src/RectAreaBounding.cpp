#include "RectAreaBounding.h"

CRectAreaBounding::CRectAreaBounding()
{

}

CRectAreaBounding::CRectAreaBounding( RectAreaBoundingType nType )
{
	m_nType = nType;
}

CRectAreaBounding::~CRectAreaBounding()
{

}

CRectAreaBounding::RectAreaBoundingType CRectAreaBounding::getRectAreaBoundingType()
{
	return m_nType;
}

void CRectAreaBounding::setRectAreaBoundingType( RectAreaBoundingType nType )
{
	m_nType = nType;
}



