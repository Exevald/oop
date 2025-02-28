#pragma once

#include "CFunction.h"
#include "CVariable.h"
#include "IValueProvider.h"
#include <map>
#include <string>
#include <unordered_map>

using VariablesMap = std::map<std::string, std::shared_ptr<CVariable>>;
using FunctionsMap = std::map<std::string, std::shared_ptr<CFunction>>;

class CCalculator
{
public:
	void DefineVariable(const std::string& identifier);
	void UpdateVariable(const std::string& identifierName, const std::shared_ptr<double>& value);
	void DefineFunction(const std::string& identifier, const std::string& operand);
	void DefineFunction(const std::string& identifier, const std::string& leftOperandName, Operation operation, const std::string& rightOperandName);
	[[nodiscard]] std::shared_ptr<IValueProvider> GetIdentifier(const std::string& identifierName) const;
	[[nodiscard]] std::shared_ptr<double> GetIdentifierValue(const std::string& identifierName) const;
	[[nodiscard]] VariablesMap GetAvailableVariables() const;
	[[nodiscard]] FunctionsMap GetAvailableFunctions() const;

private:
	void ValidateIdentifier(const std::string& identifier);

	VariablesMap m_variablesMap;
	FunctionsMap m_functionsMap;
};
