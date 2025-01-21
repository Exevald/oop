#pragma once

#include "CFunction.h"
#include "CVariable.h"
#include "IValueProvider.h"
#include <map>
#include <string>
#include <unordered_map>

using VariablesMap = std::map<std::string, CVariable>;
using FunctionsMap = std::map<std::string, CFunction>;

class CCalculator
{
public:
	void DefineVariable(const std::string& identifier);
	void UpdateVariable(const std::string& identifier, const std::shared_ptr<double>& value);
	void DefineFunction(const std::string& identifier, const std::string& operand);
	void DefineFunction(const std::string& identifier, const std::string& leftOperand, Operation operation, const std::string& rightOperand);
	[[nodiscard]] std::shared_ptr<double> GetIdentifierValue(const std::string& identifier) const;
	[[nodiscard]] VariablesMap GetAvailableVariables() const;
	[[nodiscard]] FunctionsMap GetAvailableFunctions() const;

private:
	void ValidateIdentifier(const std::string& identifier);

	VariablesMap m_variablesMap;
	FunctionsMap m_functionsMap;
};
