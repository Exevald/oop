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
	std::cout << "OBSERVERS COUNT: " << m_observers.size() << std::endl;
	auto nextObserverId = CVariable::GetNextObserverId();
	std::cout << "NEXT ID: " << nextObserverId << std::endl;
	m_observers.emplace(nextObserverId, observer);
	std::cout << "OBSERVERS COUNT AFTER: " << m_observers.size() << std::endl;

	return nextObserverId;
}

void CVariable::RemoveObserver(Id observerId)
{
	m_observers.erase(observerId);
}

void CVariable::NotifyObservers()
{
	for (const auto& [_, observer] : m_observers)
	{
		observer->Update();
	}
}

Id CVariable::GetNextObserverId()
{
	return m_observers.size() + 1;
}

std::unordered_set<std::shared_ptr<IObservable>> CVariable::GetValueDependencies()
{
	return { shared_from_this() };
}