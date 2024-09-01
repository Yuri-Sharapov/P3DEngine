#include "platform.h"

int main()
{
	Log::file("log.txt");
	Log::write("program started");

	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(800, 480), "FPS", sf::Style::Close, settings);

	sf::RectangleShape rect(sf::Vector2f(120, 50));
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(50, 50);

	sf::ConvexShape poly(5);
	poly.setPoint(0, sf::Vector2f(0.f, 0.f));
	poly.setPoint(1, sf::Vector2f(150.f, 10.f));
	poly.setPoint(2, sf::Vector2f(120.f, 90.f));
	poly.setPoint(3, sf::Vector2f(30.f, 100.f));
	poly.setPoint(4, sf::Vector2f(0.f, 50.f));
	poly.setFillColor(sf::Color::Red);
	poly.setPosition(200, 10);

	
	Log::write("window created");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(50, 50, 50, 0));
		window.draw(poly);
		window.draw(rect);
		window.display();
	}
}