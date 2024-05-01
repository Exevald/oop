#pragma once
#include "Car.h"

#include <functional>
#include <map>
#include <sstream>
#include <string>

class CCarController
{
public:
	CCarController(CCar& car);
	bool HandleCommand() const;

private:
	bool WriteCarInfo() const;
	bool HandleTurnOnEngine() const;
	bool HandleTurnOffEngine() const;
	bool HandleSetGear(std::istream& args) const;
	bool HandleSetSpeed(std::istream& args) const;

	bool StringToInt(const std::string& arg, int& number) const;
	std::string MapDirectionToString(const Direction& carDirection) const;

private:
	using ActionMap = std::map<std::string, std::function<bool(std::istream& args)>>;

	CCar& m_car;
	ActionMap m_actionMap;
};