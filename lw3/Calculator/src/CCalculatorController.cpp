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
		try
		{
			it->second();
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
		}
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
		std::string variableValue = variableInfo.second.HasValue() ? std::to_string(*variableInfo.second.GetValue()) : "nan";
		m_output << variableInfo.first << ":" << std::fixed << std::setprecision(2) << variableValue << std::endl;
	}
}

void CCalculatorController::PrintAvailableFunctions() const
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);

	for (const auto& functionInfo : m_calculator.GetAvailableFunctions())
	{
		std::string functionValue = functionInfo.second.HasValue() ? std::to_string(*functionInfo.second.GetValue()) : "nan";
		m_output << functionInfo.first << ":" << std::fixed << std::setprecision(2) << functionValue << std::endl;
	}
}

void CCalculatorController::PrintIdentifier()
{
	std::string name;
	m_input >> name;
	m_output.setf(std::ios::fixed);
	m_output.precision(2);
	std::string identifierValue;

	try
	{
		if (m_calculator.GetIdentifierValue(name) == nullptr)
		{
			identifierValue = "nan";
		}
		else
		{
			identifierValue = std::to_string(*m_calculator.GetIdentifierValue(name));
		}
		m_output << identifierValue << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}
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
	std::string expression;
	m_input >> expression;

	std::string leftOperand, rightOperand, functionName;
	std::shared_ptr<Operation> operation;

	CCalculatorController::ParseFunctionDefinition(expression, functionName, leftOperand, operation, rightOperand);

	if (operation != nullptr)
	{
		m_calculator.DefineFunction(functionName, leftOperand, *operation, rightOperand);
	}
	else
	{
		m_calculator.DefineFunction(functionName, leftOperand);
	}
}

void CCalculatorController::ParseVariableDefinition(const std::string& expression, std::string& leftOperand, std::string& rightOperand)
{
	const std::regex regex(R"(([\w]+)=([\w]+))");
	std::smatch matchString;
	if (!std::regex_match(expression, matchString, regex))
	{
		throw std::runtime_error("Invalid variable definition");
	}

	leftOperand = matchString[1];
	rightOperand = matchString[2];
}

void CCalculatorController::ParseFunctionDefinition(const std::string& expression, std::string& functionName, std::string& leftOperand, std::shared_ptr<Operation>& operation, std::string& rightOperand)
{
	const std::regex regex(R"(([\w]+)=([\w]+)(([\+\-\*\/])([\w]+))?)");
	std::smatch matchResult;
	if (!std::regex_match(expression, matchResult, regex))
	{
		throw std::runtime_error("Invalid function declaration");
	}

	functionName = matchResult[1];
	leftOperand = matchResult[2];
	operation = std::make_shared<Operation>(CCalculatorController::ConvertOperation(matchResult[4]));
	rightOperand = matchResult[5];
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

Operation CCalculatorController::ConvertOperation(const std::string& operationString)
{
	if (operationString == "+")
	{
		return Operation::Plus;
	}
	if (operationString == "-")
	{
		return Operation::Minus;
	}
	if (operationString == "*")
	{
		return Operation::Mult;
	}
	if (operationString == "-")
	{
		return Operation::Minus;
	}

	throw std::runtime_error("invalid m_operation string");
}
