#include "platform.h"
#include "map/map.h"
#include "player/player.h"
#include "3dView/view.h"

static void updateMap(RenderWindow& pwnd, RectangleShape* pShapes, size_t shapesCount, CircleShape& player, PMap& map)
{
	float mapScale = (float)map.getHeight() / 240.0f;

	Vector2f playerPos;
	playerPos = map.getPlayerPos();
	playerPos.x /= mapScale;
	playerPos.y /= mapScale;
	player.setPosition(playerPos);
	player.setRotation(map.getPlayerAngle());

	pwnd.clear(Color(50, 50, 50, 0));
	for (size_t i = 0; i < shapesCount; i++)
	{
		pwnd.draw(pShapes[i]);
	}
	pwnd.draw(player);
	pwnd.display();
}

static void updateView(RenderWindow& pwnd)
{

}

int main()
{
	Log::file("log.txt");
	Log::write("program started");

	ContextSettings settings;
	settings.antialiasingLevel = 0;
	RenderWindow window(VideoMode(1280, 600), "FPS", Style::Close, settings);
	window.setFramerateLimit(60);
	
	//ConvexShape poly(5);
	//poly.setPoint(0, Vector2f(0.f, 0.f));
	//poly.setPoint(1, Vector2f(150.f, 10.f));
	//poly.setPoint(2, Vector2f(120.f, 90.f));
	//poly.setPoint(3, Vector2f(30.f, 100.f));
	//poly.setPoint(4, Vector2f(0.f, 50.f));
	//poly.setFillColor(Color::Red);
	//poly.setPosition(200, 10);

	// player
	PPlayer player(20, 50);

	// map routine
	PMap map("res/color_map.jpg");
	map.addPlayer(&player);
	int mapHeight = 480;
	float mapScale = (float)map.getHeight() / (float)mapHeight;
	int mapWidth = (int)((float)map.getWidth() / mapScale);
	//RenderWindow mapWnd(VideoMode(mapWidth, mapHeight), "Map", Style::Close);

	static RectangleShape* pMapShapes = new RectangleShape[map.getCellCount()];
	static CircleShape mapPlayer(15, 3);
	mapPlayer.setFillColor(Color::Blue);
	mapPlayer.setOrigin(mapPlayer.getRadius(), mapPlayer.getRadius());

	//for (int y = 0; y < map.getHeight(); y++)
	//{
	//	for (int x = 0; x < map.getWidth(); x++)
	//	{
	//		PMapCell cell = map.getCell(x, y);
	//		pMapShapes[x + y * map.getWidth()].setSize(Vector2f(1.0f / mapScale, 1.0f / mapScale));
	//		pMapShapes[x + y * map.getWidth()].setFillColor(cell.color);
	//		pMapShapes[x + y * map.getWidth()].setPosition(x / mapScale, y / mapScale);
	//		//pMapShapes[x + y * map.getWidth()].setOutlineColor(Color::Black);
	//		//pMapShapes[x + y * map.getWidth()].setOutlineThickness(1.0f);
	//	}
	//}
	// 3d view
	P3DView view(&window, &map);

	Log::write("window created");

	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				//mapWnd.close();
			}
		}
		//while (mapWnd.pollEvent(event))
		//{
		//	if (event.type == Event::Closed)
		//	{
		//		window.close();
		//		mapWnd.close();
		//	}
		//}

		player.update();
		view.update();

		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
		
		
		

		Log::write("Fps: %f, frameTime: %f", floor(fps), currentTime.asSeconds() - previousTime.asSeconds());
		previousTime = currentTime;
		
		//updateMap(mapWnd, pMapShapes, map.getCellCount(), mapPlayer, map);
	}
}