#pragma once

#include <memory>

enum class Operation
{
	Plus,
	Minus,
	Mult,
	Div,
};

class IValueProvider
{
public:
	[[nodiscard]] virtual std::shared_ptr<double> GetValue() const = 0;
	[[nodiscard]] virtual bool IsDefined() const = 0;
	virtual void CalculateValue() = 0;
	virtual ~IValueProvider() = default;
};