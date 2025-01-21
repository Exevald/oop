#include "CCalculator.h"
#include <iostream>

void CCalculator::DefineVariable(const std::string& identifier)
{
	ValidateIdentifier(identifier);
	m_variablesMap.emplace(identifier, CVariable());
}

void CCalculator::UpdateVariable(const std::string& identifier, const std::shared_ptr<double>& value)
{
	m_variablesMap[identifier].SetValue(value);
}

void CCalculator::DefineFunction(const std::string& identifier, const std::string& leftOperand)
{
}

void CCalculator::DefineFunction(const std::string& identifier, const std::string& leftOperand, Operation operation, const std::string& rightOperand)
{
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

std::shared_ptr<double> CCalculator::GetIdentifierValue(const std::string& identifier) const
{
	auto variableIt = m_variablesMap.find(identifier);
	auto functionIt = m_functionsMap.find(identifier);

	if (variableIt != m_variablesMap.end())
	{
		return variableIt->second.GetValue();
	}
	if (functionIt != m_functionsMap.end())
	{
		return functionIt->second.GetValue();
	}

	throw std::runtime_error("Unknown identifier");
}
