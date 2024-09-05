#include "view.h"

P3DView::P3DView(RenderWindow* pWnd, PMap* pMap)
	: m_pWnd(pWnd)
	, m_pMap(pMap)
{
	m_imageBuf.create(m_pWnd->getSize().x, m_pWnd->getSize().y, Color(0, 0, 0));
}

P3DView::~P3DView()
{

}

void P3DView::update()
{
	if (m_pWnd == nullptr || m_pMap == nullptr)
		return;
	
	Vector2u screenSize = m_pWnd->getSize();

	// draw sky
	m_pWnd->clear(Color(73, 255, 255));
	// draw floor
	//float direction_vertical = m_pMap->getPlayerAngleVertical();
	//float floor_level = round(0.5f * screenSize.y * (1 + tan(Math::deg2Rad(direction_vertical)) / tan(Math::deg2Rad(0.5f * FOV_VERTICAL))));
	//RectangleShape floor_shape(Vector2f(screenSize.x, screenSize.y - floor_level));
	//floor_shape.setFillColor(Color(36, 219, 0));
	//floor_shape.setPosition(0, floor_level);
	//m_pWnd->draw(floor_shape);


	unsigned int screenWidth = screenSize.x;
	unsigned int screenHeight = screenSize.y;

	Texture texture;
	texture.create(screenWidth, screenHeight);
	texture.loadFromImage(m_imageBuf);
	Sprite sprite(texture);

	float rayAngle = Math::deg2Rad(-m_pMap->getPlayerAngle() - (FOV_HORIZONTAL) + 90);


	float rayDistance = 2000;
	float delta_angle = Math::deg2Rad(FOV_HORIZONTAL) / screenWidth;

	int* zBuffer = new int[screenWidth * screenHeight];

	for (unsigned int i = 0; i < screenHeight - 1; i++)
	{
		for (unsigned int j = 0; j < screenWidth - 1; j++)
		{
			m_imageBuf.setPixel(j, i, Color(73, 255, 255));
		}
	}

	for (unsigned int num_ray = 0; num_ray < screenWidth; num_ray++)
	{
		rayAngle = Math::deg2Rad(FOV_HORIZONTAL * (floor(0.5f * screenWidth) - num_ray) / (screenWidth - 1)) + Math::deg2Rad(-m_pMap->getPlayerAngle());
		bool isFirstContact = false;

		float sinA = sin(rayAngle);
		float cosA = cos(rayAngle);

		float playerHeight = m_pMap->getPlayerHeight();
		float scaleHeight = 500;

		for (unsigned int depth = 1; depth < rayDistance; depth++)
		{
			int x = (int)(m_pMap->getPlayerPos().x + depth * cosA);
			// if 0 < x < map_width:
			if (x > 0 && x < m_pMap->getWidth())
			{
				int y = (int)(m_pMap->getPlayerPos().y + depth * sinA);
				// if 0 < y < map_height:
				if (y > 0 && y < m_pMap->getHeight())
				{
					// remove fish eye and get height on screen
					float ndepth = depth * cos(Math::deg2Rad(m_pMap->getPlayerAngle()) + rayAngle);

					int height_on_screen = (int)((playerHeight - m_pMap->getCell(x, y).height) 
									/ ndepth * scaleHeight + (m_pMap->getPlayerAngleVertical()));

					// remove unnecessary drawing
					if (!isFirstContact)
					{
						zBuffer[num_ray] = MIN(height_on_screen, (int)screenHeight);
						isFirstContact = true;
					}
					// remove mirror bug
					if (height_on_screen < 0)
						height_on_screen = 0;
					// draw vert line
					if (height_on_screen < zBuffer[num_ray])
					{
						/* for screen_y in range(height_on_screen, y_buffer[num_ray]):
                             screen_array[num_ray, screen_y] = color_map[x, y]
                           y_buffer[num_ray] = height_on_screen*/
						for (int screenY = height_on_screen; screenY < zBuffer[num_ray]; screenY++)
						{
							m_imageBuf.setPixel(num_ray, screenY, m_pMap->getCell(x, y).color);
						}
						zBuffer[num_ray] = height_on_screen;
					}
				}
			}
		}

		rayAngle += delta_angle;
	}

	delete[] zBuffer;
	m_pWnd->draw(sprite);
	
	m_pWnd->display();

}