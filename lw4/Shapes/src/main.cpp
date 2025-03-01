#include "CShapesController.h"
#include <SFML/Graphics.hpp>
#include <iostream>

struct WindowSettings
{
	std::string windowTitle = "Shapes";
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 800;
};

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	CShapesController shapesController(std::cin, std::cout);
	WindowSettings windowSettings;
	sf::RenderWindow window(sf::VideoMode(windowSettings.windowWidth, windowSettings.windowHeight),
		windowSettings.windowTitle,
		sf::Style::Default, settings);

	bool isInputFinished = false;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!isInputFinished)
		{
			shapesController.HandleCommand();

			if (std::cin.eof())
			{
				isInputFinished = true;
				shapesController.PrintResult();
			}
		}

		window.clear(sf::Color::White);
		shapesController.DrawShapes(window);
		window.display();
	}

	return EXIT_SUCCESS;
}