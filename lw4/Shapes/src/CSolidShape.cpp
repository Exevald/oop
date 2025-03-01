#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t fillColor, uint32_t outlineColor)
	: CShape(outlineColor)
	, m_fillColor(fillColor)
{
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}
