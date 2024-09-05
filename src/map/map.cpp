#include "map.h"

PMap::PMap(const char* szMapFile)
{
	Image mapFile;
	if (!mapFile.loadFromFile(szMapFile))
	{
		Log::write("Error in map file");
		return;
	}
	Log::write("map file open sucessfull");
	Vector2u mapSize = mapFile.getSize();
	m_width = mapSize.x;
	m_height = mapSize.y;

	m_pData = new PMapCell[m_width * m_height];
	
	Image heightFile;
	heightFile.loadFromFile("res/height_map.jpg");

	for (size_t y = 0; y < m_height; y++)
	{
		for (size_t x = 0; x < m_width; x++)
		{
			Color pixel = mapFile.getPixel(x, y);
			int height = heightFile.getPixel(x, y).r + heightFile.getPixel(x, y).g + heightFile.getPixel(x, y).b;
			setCell(x, y, height, pixel);
		}
	}
	Log::write("map created");
}

PMap::~PMap()
{
	delete[] m_pData;
}

void PMap::addPlayer(PPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

PMapCell PMap::getCell(int x, int y)
{
	PMapCell cell = { 0 };
	if (x < m_width && y < m_height)
		cell =  m_pData[x + y * m_width];
	
	return cell;
}

void PMap::setCell(int x, int y, int height, Color color)
{
	if (x < m_width && y < m_height)
	{
		PMapCell cell;
		cell.height = height;
		cell.color = color;
		m_pData[x + y * m_width] = cell;
	}
}
