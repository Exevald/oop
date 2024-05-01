#include "../Car/Car.h"

#include <../../catch2/catch.hpp>

SCENARIO("Turning on and turing off engine with zero speed and neutral gear")
{
	GIVEN("New car")
	{
		CCar car;

		WHEN("We turning on engine")
		{
			bool res = car.TurnOnEngine();
			THEN("We got that engine is turned on")
			{
				REQUIRE(res == true);
				REQUIRE(car.IsTurnedOn() == true);
			}

			AND_WHEN("We turning off engine")
			{
				bool res = car.TurnOffEngine();
				THEN("We got that engine is turned off")
				{
					REQUIRE(res == true);
					REQUIRE(car.IsTurnedOn() == false);
				}
			}
		}
	}
}

SCENARIO("Turning on engine and start riding on first gear with valid speed")
{
	GIVEN("New car")
	{
		CCar car;

		WHEN("We turning on engine")
		{
			bool res = car.TurnOnEngine();
			THEN("We got that engine is turned on")
			{
				REQUIRE(res == true);
				REQUIRE(car.IsTurnedOn() == true);
			}

			AND_WHEN("We try to set valid speed")
			{
				bool res = car.SetSpeed(25);
				THEN("We got that speed is still zero")
				{
					REQUIRE(res == false);
					REQUIRE(car.GetSpeed() == 0);
				}
			}

			AND_WHEN("We set first gear")
			{
				bool res = car.SetGear(1);
				THEN("We got that gear is 1")
				{
					REQUIRE(res == true);
					REQUIRE(car.GetGear() == 1);
				}

				AND_WHEN("We set valid speed")
				{
					bool res = car.SetSpeed(20);
					THEN("We got that speed is set and direction is forward")
					{
						REQUIRE(res == true);
						REQUIRE(car.GetSpeed() == 20);
						REQUIRE(car.GetDirection() == Direction::Forward);
					}
				}

				AND_WHEN("We try to set invalid speed")
				{
					bool res = car.SetSpeed(40);
					THEN("We got that speed is 0 and gear is 1")
					{
						REQUIRE(res == false);
						REQUIRE(car.GetSpeed() == 0);
						REQUIRE(car.GetGear() == 1);
					}
				}
			}
		}
	}
}

SCENARIO("Stopping car and turning off engine")
{
	GIVEN("Car with second gear and valid speed")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);

		WHEN("We set speed at zero")
		{
			bool res = car.SetSpeed(0);

			THEN("We got that gear is 2")
			{
				REQUIRE(res == false);
				REQUIRE(car.GetSpeed() == 50);
				REQUIRE(car.GetGear() == 2);
			}
		}

		WHEN("We set first gear")
		{
			bool res = car.SetGear(1);
			THEN("We that car didn`t change speed and gear")
			{
				REQUIRE(res == false);
				REQUIRE(car.GetSpeed() == 50);
				REQUIRE(car.GetGear() == 2);
			}
		}

		WHEN("We set valid speed and second gear")
		{
			bool res = car.SetSpeed(25);
			THEN("We got speed now id set")
			{
				REQUIRE(res == true);
				REQUIRE(car.GetSpeed() == 25);
				REQUIRE(car.GetGear() == 2);
			}

			AND_WHEN("We set first gear")
			{
				bool res = car.SetGear(1);
				car.SetSpeed(15);
				THEN("We got true from car and gear is 1")
				{
					REQUIRE(res == true);
					REQUIRE(car.GetGear() == 1);
					REQUIRE(car.GetSpeed() == 15);
				}

				AND_WHEN("We set neutral gear and zero speed")
				{
					bool res = car.SetSpeed(0);
					car.SetGear(0);
					THEN("We got true from car and car stopped")
					{
						REQUIRE(res == true);
						REQUIRE(car.GetSpeed() == 0);
					}

					AND_WHEN("We turning off engine")
					{
						bool res = car.TurnOffEngine();
						THEN("We got true from car and engine is turned off")
						{
							REQUIRE(res == true);
							REQUIRE(car.IsTurnedOn() == false);
						}
					}
				}
			}
		}
	}
}

SCENARIO("Riding with backward gear and stopping")
{
	GIVEN("Car with turned on engine")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("We set -1 gear")
		{
			bool res = car.SetGear(-1);
			THEN("We got that gear is -1")
			{
				REQUIRE(res == true);
				REQUIRE(car.GetGear() == -1);
			}

			AND_WHEN("We set a valid speed")
			{
				bool res = car.SetSpeed(10);
				THEN("We got that direction is backward")
				{
					REQUIRE(res == true);
					REQUIRE(car.GetSpeed() == 10);
					REQUIRE(car.GetDirection() == Direction::Backward);
				}

				AND_WHEN("We turning off engine")
				{
					bool res = car.TurnOffEngine();
					THEN("We got false and engine still on")
					{
						REQUIRE(res == false);
						REQUIRE(car.IsTurnedOn() == true);
						REQUIRE(car.GetSpeed() == 10);
					}
				}

				AND_WHEN("We stopped car")
				{
					bool res = car.SetSpeed(0);
					THEN("We got true and speed is 0")
					{
						REQUIRE(res == true);
						REQUIRE(car.GetSpeed() == 0);
					}

					AND_WHEN("We turned off engine")
					{
						bool res = car.TurnOffEngine();
						THEN("We got false and engine still on")
						{
							REQUIRE(res == false);
							REQUIRE(car.IsTurnedOn());
						}
					}

					AND_WHEN("We set neutral gear and turning off engine")
					{
						car.SetGear(0);
						bool res = car.TurnOffEngine();
						THEN("We got true and engine is turned off")
						{
							REQUIRE(res == true);
							REQUIRE(!car.IsTurnedOn());
						}
					}
				}
			}

			AND_WHEN("We set speed at 30")
			{
				bool res = car.SetSpeed(30);
				THEN("We got false and speed is 0")
				{
					REQUIRE(res == false);
					REQUIRE(car.GetSpeed() == 0);
				}
			}
		}
	}
}

SCENARIO("Changing gears on differnt speeds")
{
	GIVEN("New car with turned on engine")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("We set gear at -1 and valid speed")
		{
			car.SetGear(-1);
			car.SetSpeed(15);

			AND_WHEN("We set neutral gear")
			{
				car.SetGear(0);
				THEN("We got that gear was set")
				{
					REQUIRE(car.GetGear() == 0);
				}
				AND_WHEN("We set zero speed")
				{
					car.SetSpeed(0);
					THEN("We can set -1 gear")
					{
						REQUIRE(car.SetGear(-1));
					}
					THEN("We can set 1 gear")
					{
						REQUIRE(car.SetGear(1));
					}
				}
				AND_WHEN("We try to set -1 gear")
				{
					car.SetGear(-1);
					THEN("We got that we can't do it")
					{
						REQUIRE(car.GetGear() == 0);
					}
				}
				AND_WHEN("We try to increase speed")
				{
					car.SetSpeed(20);
					THEN("We got that we can't do it")
					{
						REQUIRE(car.GetSpeed() != 20);
					}
				}
				AND_WHEN("We try to decrease speed")
				{
					car.SetSpeed(10);
					THEN("We got that we was set")
					{
						REQUIRE(car.GetSpeed() == 10);
					}
				}
			}
		}

		WHEN("We set first gear and valid speed")
		{
			car.SetGear(1);
			car.SetSpeed(15);

			THEN("We got that we can`t set -1 gear")
			{
				REQUIRE(!car.SetGear(-1));
			}

			AND_WHEN("We set neutral gear")
			{
				car.SetGear(0);
				THEN("We got that gear is neutral and direction is forward")
				{
					REQUIRE(car.GetGear() == 0);
					REQUIRE(car.GetDirection() == Direction::Forward);
				}

				AND_WHEN("We set speed 13 km/h")
				{
					car.SetSpeed(13);
					THEN("We got that speed is 13 km/h")
					{
						REQUIRE(car.GetSpeed() == 13);
					}

					AND_WHEN("We set speed 14 km/h")
					{
						bool res = car.SetSpeed(14);
						THEN("We got that speed is 13 km/h")
						{
							REQUIRE(res == false);
							REQUIRE(car.GetSpeed() == 13);
						}
					}
				}
			}
		}

		WHEN("We trying to set -2 gear")
		{
			bool res = car.SetGear(-2);
			THEN("We got that we can`t do it")
			{
				REQUIRE(!res);
			}
		}

		WHEN("We trying to set invalid speed")
		{
			bool res = car.SetSpeed(-20);
			THEN("We got that we can`t do it")
			{
				REQUIRE(!res);
			}
		}
	}
}

SCENARIO("Changing direction with different gears")
{
	GIVEN("New car with turned on engine")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("We set gear -1")
		{
			bool res = car.SetGear(-1);
			THEN("We got that gear is -1 and direction is standing still")
			{
				REQUIRE(res == true);
				REQUIRE(car.GetDirection() == Direction::StandingStill);
			}

			AND_WHEN("We set valid speed")
			{
				car.SetSpeed(10);
				THEN("We got that speed is set and direction is backward")
				{
					REQUIRE(car.GetSpeed() == 10);
					REQUIRE(car.GetDirection() == Direction::Backward);
				}
			}
		}
		WHEN("We set gear 1")
		{
			bool res = car.SetGear(1);
			THEN("We got that gear is 1 and direction is standing still")
			{
				REQUIRE(res == true);
				REQUIRE(car.GetDirection() == Direction::StandingStill);
			}

			AND_WHEN("We set valid speed")
			{
				car.SetSpeed(10);
				THEN("We got that speed is set and direction is forward")
				{
					REQUIRE(car.GetSpeed() == 10);
					REQUIRE(car.GetDirection() == Direction::Forward);
				}

				AND_WHEN("We set neutral gear")
				{
					car.SetGear(0);
					THEN("We got that gear is neutral and direction is forward")
					{
						REQUIRE(car.GetGear() == 0);
						REQUIRE(car.GetDirection() == Direction::Forward);
					}
				}
			}
		}
	}
}

SCENARIO("Changing gears with different speeds")
{
	GIVEN("New car with turned on engine")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("We set valid speed and valid gear")
		{
			car.SetGear(1);
			car.SetSpeed(10);
			AND_WHEN("We set zero speed and try to change gear to -1")
			{
				car.SetSpeed(0);
				car.SetGear(-1);
				THEN("We got that direction is standing still and gear is -1")
				{
					REQUIRE(car.GetDirection() == Direction::StandingStill);
					REQUIRE(car.GetGear() == -1);
				}
			}
		}
		WHEN("We set gear to -1 and valid speed")
		{
			car.SetGear(-1);
			car.SetSpeed(20);
			AND_WHEN("We try to change gear to 2")
			{
				car.SetGear(2);
				THEN("We got that gear is -1")
				{
					REQUIRE(car.GetGear() == -1);
				}
			}
		}
	}
}