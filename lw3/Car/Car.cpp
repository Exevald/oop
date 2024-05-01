#include "Car.h"

#include <optional>
#include <string>

namespace
{
const int MIN_GEAR = -1;
const int MIN_SPEED = 0;
const int MAX_SPEED = 150;
} // namespace

CCar::CCar()
{
	m_isTurnedOn = false;
	m_speed = 0;
	m_gear = 0;
	m_direction = Direction::StandingStill;

	m_gearboxLimits.push_back(GearLimit{ 0, 20, -1 });
	m_gearboxLimits.push_back(GearLimit{ 0, 150, 0 });
	m_gearboxLimits.push_back(GearLimit{ 0, 30, 1 });
	m_gearboxLimits.push_back(GearLimit{ 20, 50, 2 });
	m_gearboxLimits.push_back(GearLimit{ 30, 60, 3 });
	m_gearboxLimits.push_back(GearLimit{ 40, 90, 4 });
	m_gearboxLimits.push_back(GearLimit{ 50, 150, 5 });
}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

int CCar::GetGear() const
{
	return m_gear;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::TurnOnEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}

	m_isTurnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}

	m_isTurnedOn = false;
	return true;
}

std::optional<GearLimit> CCar::GetGearLimitInfo(int gearNum) const
{
	auto it = std::find_if(m_gearboxLimits.begin(), m_gearboxLimits.end(),
		[gearNum](const GearLimit& gear) { return gear.number == gearNum; });
	if (it != m_gearboxLimits.end())
	{
		return *it;
	}
	return std::nullopt;
}

int CCar::GetMaxGearCount() const
{
	return m_gearboxLimits.size();
}

bool CCar::SetGear(int gearNum)
{
	if (!m_isTurnedOn || gearNum < MIN_GEAR || gearNum > GetMaxGearCount())
	{
		return false;
	}
	auto newGearInfo = GetGearLimitInfo(gearNum);
	if (!newGearInfo)
	{
		return false;
	}
	if (gearNum == -1 && m_speed != 0)
	{
		return false;
	}
	if ((m_speed < newGearInfo->minSpeed || m_speed > newGearInfo->maxSpeed) && gearNum != 0)
	{
		return false;
	}
	if (m_direction == Direction::Backward && gearNum != 0)
	{
		return false;
	}
	m_gear = gearNum;
	return true;
}

bool CCar::SetSpeed(int speed)
{
	auto currentGearInfo = GetGearLimitInfo(m_gear);
	if (!currentGearInfo)
	{
		return false;
	}
	if (speed > MAX_SPEED || speed < MIN_SPEED || !m_isTurnedOn)
	{
		return false;
	}
	if (m_gear == 0 && speed > m_speed)
	{
		return false;
	}
	if ((speed < currentGearInfo->minSpeed || speed > currentGearInfo->maxSpeed) && m_gear != 0)
	{
		return false;
	}
	if (speed == 0)
	{
		m_direction = Direction::StandingStill;
	}
	else if (speed != 0 && m_gear >= 1)
	{
		m_direction = Direction::Forward;
	}
	else if (speed != 0 && m_gear == -1)
	{
		m_direction = Direction::Backward;
	}

	m_speed = speed;
	return true;
}