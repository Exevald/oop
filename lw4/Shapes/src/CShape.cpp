#include "CShape.h"

CShape::CShape(uint32_t color)
	: m_outlineColor(color)
{
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}