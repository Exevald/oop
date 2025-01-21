#pragma once

#include "CCalculator.h"
#include <functional>
#include <string>
#include <unordered_map>

using ActionMap = std::unordered_map<std::string, std::function<void()>>;

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& calculator, std::istream& m_input, std::ostream& m_output);
	void HandleCommand();

private:
	void PrintAvailableVariables() const;
	void PrintAvailableFunctions() const;
	void PrintIdentifier();
	void DefineVariable();
	void UpdateVariable();
	void DefineFunction();
	static void ParseVariableDefinition(const std::string& expression, std::string& leftOperand, std::string& rightOperand);
	static bool IsIdentifierCorrect(const std::string& identifier);

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
};