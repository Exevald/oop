#pragma once

#include "IObservable.h"
#include "IValueProvider.h"
#include <memory>
#include <unordered_map>

class CVariable : public IValueProvider
	, public IObservable
	, public std::enable_shared_from_this<CVariable>
{
public:
	CVariable()
		: m_value(nullptr){};

	void SetValue(const std::shared_ptr<double>& value);
	[[nodiscard]] std::shared_ptr<double> GetValue() const override;
	[[nodiscard]] bool HasValue() const override;
	void CalculateValue() override;
	Id RegisterObserver(const std::shared_ptr<IObserver>& observer) override;
	void RemoveObserver(Id observerId) override;
	Id GetNextObserverId() override;
	std::unordered_set<std::shared_ptr<IObservable>> GetValueDependencies() override;

private:
	void NotifyObservers() override;

private:
	std::shared_ptr<double> m_value;
	std::unordered_map<Id, std::shared_ptr<IObserver>> m_observers;
};
