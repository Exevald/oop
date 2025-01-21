#pragma once

#include "IObservable.h"
#include "IValueProvider.h"
#include <memory>

class CVariable : public IValueProvider
	, public IObservable
{
public:
	CVariable()
		: m_value(nullptr){};

	void SetValue(const std::shared_ptr<double>& value);
	[[nodiscard]] std::shared_ptr<double> GetValue() const override;
	[[nodiscard]] bool IsDefined() const override;
	void CalculateValue() override;

private:
	std::shared_ptr<double> m_value;
};
