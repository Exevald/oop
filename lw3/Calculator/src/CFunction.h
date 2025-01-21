#pragma once

#include "IObserver.h"
#include "IValueProvider.h"

class CFunction : public IValueProvider
	, public IObserver
{
public:
	[[nodiscard]] std::shared_ptr<double> GetValue() const override;
	[[nodiscard]] bool IsDefined() const override;
	void CalculateValue() override;

private:
};
