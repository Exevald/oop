#pragma once

#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public CShape
	, public ISolidShape
{
public:
	CSolidShape(uint32_t fillColor, uint32_t outlineColor);

	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;

	~CSolidShape() override = default;

private:
	uint32_t m_fillColor;
};