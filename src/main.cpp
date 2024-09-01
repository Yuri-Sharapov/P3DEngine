#include "platform.h"

int main()
{
	Log::file("log.txt");
	Log::write("program started");
	//I called this project "FPS" even though there's no "S".
	sf::RenderWindow window(sf::VideoMode(800, 480), "FPS", sf::Style::Close);

	sf::RectangleShape rect(sf::Vector2f(120, 50));
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(50, 50);
	
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
		window.draw(rect);
		window.display();
	}
}