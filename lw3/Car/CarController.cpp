#include "CarController.h"
#include "Car.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

CCarController::CCarController(CCar& car)
	: m_car(car)
{
	m_actionMap.emplace("Info", std::bind(&CCarController::WriteCarInfo, this));
	m_actionMap.emplace("EngineOn", std::bind(&CCarController::HandleTurnOnEngine, this));
	m_actionMap.emplace("EngineOff", std::bind(&CCarController::HandleTurnOffEngine, this));
	m_actionMap.emplace("SetGear", std::bind(&CCarController::HandleSetGear, this, std::placeholders::_1));
	m_actionMap.emplace("SetSpeed", std::bind(&CCarController::HandleSetSpeed, this, std::placeholders::_1));
}

bool CCarController::HandleCommand() const
{
	std::string commandLine;
	std::getline(std::cin, commandLine);
	std::istringstream inputStream(commandLine);

	std::string action;
	inputStream >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(inputStream);
	}
	else
	{
		std::cout << "Unknown command!" << std::endl;
		return false;
	}
}

bool CCarController::WriteCarInfo() const
{
	std::cout << "Engine state: " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl
			  << "Current gear: " << m_car.GetGear() << std::endl
			  << "Current speed: " << m_car.GetSpeed() << std::endl
			  << "Current direction: " << MapDirectionToString(m_car.GetDirection()) << std::endl;
	return true;
}

bool CCarController::HandleSetGear(std::istream& args) const
{
	int gear;
	std::string arg;
	args >> arg;
	if (StringToInt(arg, gear))
	{
		if (m_car.SetGear(gear))
		{
			std::cout << "Gear is set" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Failed to set gear" << std::endl;
		}
	}
	return false;
}

bool CCarController::HandleSetSpeed(std::istream& args) const
{
	int speed;
	std::string arg;
	args >> arg;
	if (StringToInt(arg, speed))
	{
		if (m_car.SetSpeed(speed))
		{
			std::cout << "Speed is set" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Failed to set speed" << std::endl;
		}
	}
	return false;
}

bool CCarController::HandleTurnOnEngine() const
{
	if (m_car.IsTurnedOn())
	{
		std::cout << "Engine is already turned on" << std::endl;
		return true;
	}
	if (m_car.TurnOnEngine())
	{
		std::cout << "Engine turned on" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed to turn on engine" << std::endl;
		return false;
	}
}

bool CCarController::HandleTurnOffEngine() const
{
	if (!m_car.IsTurnedOn())
	{
		std::cout << "Engine is already turned off" << std::endl;
		return true;
	}
	if (m_car.TurnOffEngine())
	{
		std::cout << "Engine turned off" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed to turn off engine" << std::endl;
		return false;
	}
}

bool CCarController::StringToInt(const std::string& arg, int& number) const
{
	try
	{
		number = stoi(arg);
	}
	catch (...)
	{
		std::cout << "Invalid argument" << std::endl;
		return false;
	}
	return true;
}

std::string CCarController::MapDirectionToString(const Direction& carDirection) const
{
	switch (carDirection)
	{
	case Direction::Forward:
		return "forward";
	case Direction::Backward:
		return "backward";
	case Direction::StandingStill:
		return "standing still";
	}
}