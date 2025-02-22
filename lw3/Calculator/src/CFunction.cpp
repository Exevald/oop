#include "CFunction.h"
#include <iostream>

CFunction::CFunction(const std::shared_ptr<IValueProvider>& leftOperand)
	: m_leftOperand(leftOperand)
{
	CFunction::CalculateValue();
}

CFunction::CFunction(const std::shared_ptr<IValueProvider>& leftOperand, Operation operation, const std::shared_ptr<IValueProvider>& rightOperand)
	: m_leftOperand(leftOperand)
	, m_operation(std::make_shared<Operation>(operation))
	, m_rightOperand(rightOperand)
{
	CFunction::CalculateValue();
}

std::shared_ptr<double> CFunction::GetValue() const
{
	return m_value;
}

bool CFunction::HasValue() const
{
	return m_value != nullptr;
}

void CFunction::CalculateValue()
{
	if (!m_operation || !m_leftOperand->GetValue() || !m_rightOperand->GetValue())
	{
		return;
	}

	switch (*m_operation)
	{
	case ::Operation::Plus: {
		m_value = std::make_shared<double>(*m_leftOperand->GetValue() + *m_rightOperand->GetValue());
		break;
	}
	case Operation::Minus: {
		m_value = std::make_shared<double>(*m_leftOperand->GetValue() - *m_rightOperand->GetValue());
		break;
	}
	case Operation::Mult:
		m_value = std::make_shared<double>(*m_leftOperand->GetValue() * *m_rightOperand->GetValue());
		break;
	case Operation::Div:
		m_value = std::make_shared<double>(*m_leftOperand->GetValue() / *m_rightOperand->GetValue());
		break;
	default:
		throw std::invalid_argument("Unknown operation");
	}
}

void CFunction::Update()
{
	CFunction::CalculateValue();
}

std::unordered_set<std::shared_ptr<IObservable>> CFunction::GetValueDependencies()
{
	return m_dependencies;
}

void CFunction::InitDependencies()
{
	if (!m_rightOperand)
	{
		m_dependencies = m_leftOperand->GetValueDependencies();
		return;
	}

	auto leftOperandDependencies = m_leftOperand->GetValueDependencies();
	auto rightOperandDependencies = m_rightOperand->GetValueDependencies();

	m_dependencies.reserve(leftOperandDependencies.size() + rightOperandDependencies.size());
	m_dependencies = std::move(leftOperandDependencies);
	m_dependencies.merge(std::move(rightOperandDependencies));
}

void CFunction::SubscribeToDependencies()
{
	CFunction::InitDependencies();

	std::cout << "DEPENDENCIES COUNT: " << m_dependencies.size() << std::endl;

	for (const auto& dep : m_dependencies)
	{
		auto obs = shared_from_this();
		dep->RegisterObserver(obs);
	}
}
