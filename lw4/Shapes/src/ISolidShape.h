#pragma once

#include "IShape.h"

class ISolidShape : public virtual IShape
{
public:
	[[nodiscard]] virtual uint32_t GetFillColor() const = 0;
};