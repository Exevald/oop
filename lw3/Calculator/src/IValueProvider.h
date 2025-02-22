#pragma once

#include <memory>
#include <unordered_set>

class IValueProvider
{
public:
	[[nodiscard]] virtual std::shared_ptr<double> GetValue() const = 0;
	[[nodiscard]] virtual bool HasValue() const = 0;
	virtual void CalculateValue() = 0;
	[[nodiscard]] virtual std::unordered_set<std::shared_ptr<IObservable>> GetValueDependencies() = 0;
	virtual ~IValueProvider() = default;
};