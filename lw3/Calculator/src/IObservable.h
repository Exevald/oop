#pragma once

#include "IObserver.h"
#include <memory>

using Id = unsigned long;

class IObservable
{
public:
	virtual Id RegisterObserver(const std::shared_ptr<IObserver>& observer) = 0;
	virtual void RemoveObserver(Id observerId) = 0;
	virtual Id GetNextObserverId() = 0;
	virtual ~IObservable() = default;

private:
	virtual void NotifyObservers() = 0;
};