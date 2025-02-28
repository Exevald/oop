#include "CVariable.h"
#include "IObserver.h"
#include <cmath>
#include <iostream>

void CVariable::SetValue(const std::shared_ptr<double>& value)
{
	m_value = value;

	CVariable::NotifyObservers();
}

std::shared_ptr<double> CVariable::GetValue() const
{
	return m_value;
}

bool CVariable::HasValue() const
{
	return m_value != nullptr;
}

void CVariable::CalculateValue()
{
}

Id CVariable::RegisterObserver(const std::shared_ptr<IObserver>& observer)
{
	auto nextObserverId = CVariable::GetNextObserverId();
	m_observers.emplace(nextObserverId, observer);

	return nextObserverId;
}

void CVariable::RemoveObserver(Id observerId)
{
	m_observers.erase(observerId);
}

void CVariable::NotifyObservers()
{
	auto observersCopy = m_observers;
	for (const auto& [_, observer] : observersCopy)
	{
		observer->Update();
	}
}

Id CVariable::GetNextObserverId()
{
	static Id nextId = 0;
	return ++nextId;
}

std::unordered_set<std::shared_ptr<IObservable>> CVariable::GetValueDependencies()
{
	return { shared_from_this() };
}