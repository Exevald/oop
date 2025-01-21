#include "CVariable.h"
#include <cmath>
#include <iostream>

void CVariable::SetValue(const std::shared_ptr<double>& value)
{
	m_value = value;
}

std::shared_ptr<double> CVariable::GetValue() const
{
	return m_value;
}

bool CVariable::IsDefined() const
{
	return m_value != nullptr;
}

void CVariable::CalculateValue()
{
}
