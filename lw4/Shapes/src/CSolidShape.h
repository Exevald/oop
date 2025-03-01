#pragma once

#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public CShape, public ISolidShape
{
public:
	CSolidShape(uint32_t fillColor, uint32_t outlineColor);

	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;

	~CSolidShape() override = default;

protected:
	virtual std::string GetShapeInfo() const = 0;

private:
	uint32_t m_fillColor, m_outlineColor{};
};