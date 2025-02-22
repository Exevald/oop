#pragma once

#include "IObservable.h"
#include "IObserver.h"
#include "IValueProvider.h"
#include <unordered_map>
#include <unordered_set>

enum class Operation
{
	Plus,
	Minus,
	Mult,
	Div,
};

class CFunction : public IValueProvider
	, public IObserver
	, public std::enable_shared_from_this<CFunction>
{
public:
	explicit CFunction(const std::shared_ptr<IValueProvider>& leftOperand);

	CFunction(
		const std::shared_ptr<IValueProvider>& leftOperand,
		Operation operation,
		const std::shared_ptr<IValueProvider>& rightOperand);

	[[nodiscard]] std::shared_ptr<double> GetValue() const override;
	[[nodiscard]] bool HasValue() const override;
	void CalculateValue() override;
	void Update() override;
	std::unordered_set<std::shared_ptr<IObservable>> GetValueDependencies() override;
	void SubscribeToDependencies();

private:
	void InitDependencies();

	std::shared_ptr<IValueProvider> m_leftOperand;
	std::shared_ptr<IValueProvider> m_rightOperand;
	std::shared_ptr<Operation> m_operation;
	std::shared_ptr<double> m_value;

	std::unordered_set<std::shared_ptr<IObservable>> m_dependencies;
};
