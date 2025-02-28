#include "CCalculator.h"
#include <iostream>

void CCalculator::DefineVariable(const std::string& identifier)
{
	ValidateIdentifier(identifier);
	m_variablesMap.emplace(identifier, std::make_shared<CVariable>(CVariable()));
}

void CCalculator::UpdateVariable(const std::string& identifierName, const std::shared_ptr<double>& value)
{
	if (!m_variablesMap.contains(identifierName))
	{
		m_variablesMap[identifierName] = std::make_shared<CVariable>();
	}
	m_variablesMap[identifierName]->SetValue(value);
}

void CCalculator::DefineFunction(const std::string& identifier, const std::string& leftOperandName)
{
	CCalculator::ValidateIdentifier(identifier);
	auto leftOperand = CCalculator::GetIdentifier(leftOperandName);
	auto function = std::make_shared<CFunction>(CFunction(leftOperand));

	function->SubscribeToDependencies();
	m_functionsMap.emplace(identifier, function);
}

void CCalculator::DefineFunction(const std::string& identifier, const std::string& leftOperandName, Operation operation, const std::string& rightOperandName)
{
	CCalculator::ValidateIdentifier(identifier);
	auto leftOperand = CCalculator::GetIdentifier(leftOperandName);
	auto rightOperand = CCalculator::GetIdentifier(rightOperandName);
	auto function = std::make_shared<CFunction>(CFunction(leftOperand, operation, rightOperand));

	m_functionsMap.emplace(identifier, function);
	function->SubscribeToDependencies();
}

void CCalculator::ValidateIdentifier(const std::string& identifier)
{
	if (m_variablesMap.contains(identifier) || m_functionsMap.contains(identifier))
	{
		throw std::runtime_error("Identifier is used");
	}
}

VariablesMap CCalculator::GetAvailableVariables() const
{
	return m_variablesMap;
}

FunctionsMap CCalculator::GetAvailableFunctions() const
{
	return m_functionsMap;
}

std::shared_ptr<IValueProvider> CCalculator::GetIdentifier(const std::string& identifierName) const
{
	auto variableIt = m_variablesMap.find(identifierName);
	auto functionIt = m_functionsMap.find(identifierName);

	if (variableIt != m_variablesMap.end())
	{
		return variableIt->second;
	}
	if (functionIt != m_functionsMap.end())
	{
		return functionIt->second;
	}

	throw std::runtime_error("Unknown identifier: " + identifierName);
}

std::shared_ptr<double> CCalculator::GetIdentifierValue(const std::string& identifierName) const
{
	auto identifier = GetIdentifier(identifierName);
	return identifier->GetValue();
}
