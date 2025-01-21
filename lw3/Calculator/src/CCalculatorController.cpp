#include "CCalculatorController.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <regex>

CCalculatorController::CCalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
{
	m_actionMap.emplace("printvars", [this]() { PrintAvailableVariables(); });
	m_actionMap.emplace("printfns", [this]() { PrintAvailableFunctions(); });
	m_actionMap.emplace("print", [this]() { PrintIdentifier(); });
	m_actionMap.emplace("var", [this]() { DefineVariable(); });
	m_actionMap.emplace("let", [this]() { UpdateVariable(); });
	m_actionMap.emplace("fn", [this]() { DefineFunction(); });
}

void CCalculatorController::HandleCommand()
{
	std::string command;
	m_input >> command;

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.end())
	{
		it->second();
		return;
	}
	else
	{
		m_output << "Unknown command!" << std::endl;
	}
}

void CCalculatorController::PrintAvailableVariables() const
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);

	for (const auto& variableInfo : m_calculator.GetAvailableVariables())
	{
		std::string variableValue = variableInfo.second.IsDefined() ? std::to_string(*variableInfo.second.GetValue()) : "nan";
		m_output << variableInfo.first << ":" << std::fixed << std::setprecision(2) << variableValue << std::endl;
	}
}

void CCalculatorController::PrintAvailableFunctions() const
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);

	for (const auto& functionInfo : m_calculator.GetAvailableFunctions())
	{
		m_output << functionInfo.first << ":" << functionInfo.second.GetValue() << std::endl;
	}
}

void CCalculatorController::PrintIdentifier()
{
}

void CCalculatorController::DefineVariable()
{
	std::string name;
	m_input >> name;

	if (IsIdentifierCorrect(name))
	{
		m_calculator.DefineVariable(name);
	}
}

void CCalculatorController::UpdateVariable()
{
	std::string expression;
	m_input >> expression;
	std::string leftOperand;
	std::string rightOperand;
	std::shared_ptr<double> value;

	ParseVariableDefinition(expression, leftOperand, rightOperand);
	if (CCalculatorController::IsIdentifierCorrect(rightOperand))
	{
		value = m_calculator.GetIdentifierValue(rightOperand);
	}
	else
	{
		value = std::make_shared<double>(round(stod(rightOperand) * 100) / 100);
	}
	m_calculator.UpdateVariable(leftOperand, value);
}

void CCalculatorController::DefineFunction()
{
}

void CCalculatorController::ParseVariableDefinition(const std::string& expression, std::string& leftOperand, std::string& rightOperand)
{
	std::regex regex(R"(([\w]+)=([\w]+))");
	std::smatch matchString;
	if (!std::regex_match(expression, matchString, regex))
	{
		throw std::runtime_error("Invalid variable definition");
	}

	leftOperand = matchString[1];
	rightOperand = matchString[2];
}

bool CCalculatorController::IsIdentifierCorrect(const std::string& identifier)
{
	if (std::isdigit(identifier[0]))
	{
		return false;
	}

	std::regex regex(R"([\w]+)");
	std::smatch matchString;
	if (!std::regex_match(identifier, matchString, regex))
	{
		throw std::runtime_error("Invalid identifier");
	}

	return true;
}
