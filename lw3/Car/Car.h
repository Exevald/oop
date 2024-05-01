#pragma once
#include <optional>
#include <string>
#include <vector>

enum class Direction
{
	Forward,
	Backward,
	StandingStill
};

struct GearLimit
{
	int minSpeed;
	int maxSpeed;
	int number;
};

class CCar
{
public:
	CCar();

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isTurnedOn;
	int m_speed;
	int m_gear;
	Direction m_direction;
	std::vector<GearLimit> m_gearboxLimits;

	int GetMaxGearCount() const;
	std::optional<GearLimit> GetGearLimitInfo(int gearNum) const;
};