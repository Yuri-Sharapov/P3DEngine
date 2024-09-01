#include "platform.h"
#include "map/map.h"


static void updateMap(RenderWindow& pwnd, RectangleShape* pShapes, size_t shapesCount)
{
	pwnd.clear(Color(50, 50, 50, 0));
	for (size_t i = 0; i < shapesCount; i++)
	{
		pwnd.draw(pShapes[i]);
	}
	pwnd.display();
}

int main()
{
	Log::file("log.txt");
	Log::write("program started");

	ContextSettings settings;
	settings.antialiasingLevel = 0;

	RenderWindow window(VideoMode(800, 480), "FPS", Style::Close, settings);
	window.setFramerateLimit(60);
	RectangleShape rect(Vector2f(120, 50));
	rect.setFillColor(Color::Blue);
	rect.setPosition(50, 50);

	ConvexShape poly(5);
	poly.setPoint(0, Vector2f(0.f, 0.f));
	poly.setPoint(1, Vector2f(150.f, 10.f));
	poly.setPoint(2, Vector2f(120.f, 90.f));
	poly.setPoint(3, Vector2f(30.f, 100.f));
	poly.setPoint(4, Vector2f(0.f, 50.f));
	poly.setFillColor(Color::Red);
	poly.setPosition(200, 10);

	// map routine
	PMap map("res/map.png");

	int mapHeight = 240;
	float mapScale = (float)map.getHeight() / (float)mapHeight;
	int mapWidth = (int)((float)map.getWidth() / mapScale);
	RenderWindow mapWnd(VideoMode(mapWidth, mapHeight), "Map", Style::Close);

	static RectangleShape* pMapShapes = new RectangleShape[map.getCellCount()];
	
	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++)
		{
			PMapCell cell = map.getCell(x, y);
			pMapShapes[x + y * map.getWidth()].setSize(Vector2f(1.0f / mapScale, 1.0f / mapScale));
			pMapShapes[x + y * map.getWidth()].setFillColor(cell.color);
			pMapShapes[x + y * map.getWidth()].setPosition(x / mapScale, y / mapScale);
			pMapShapes[x + y * map.getWidth()].setOutlineColor(Color::Black);
			pMapShapes[x + y * map.getWidth()].setOutlineThickness(1.0f);
		}
	}


	Log::write("window created");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				mapWnd.close();
			}
		}
		while (mapWnd.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				mapWnd.close();
			}
		}

		window.clear(Color(50, 50, 50, 0));
		window.draw(poly);
		window.draw(rect);
		window.display();

		updateMap(mapWnd, pMapShapes, map.getCellCount());
	}
}