#include "player.h"

PPlayer::PPlayer(float x, float y)
	: m_posX(x)
	, m_posY(y)
{
	setAngle(0.f);
	m_angleVertical = 0;
	m_height = 500;
}

PPlayer::~PPlayer()
{

}

void PPlayer::update()
{
	float stepX = 0;
	float stepY = 0;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		stepX += MOVEMENT_SPEED * cos(m_angleRad);
		stepY -= MOVEMENT_SPEED * sin(m_angleRad);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		stepX -= MOVEMENT_SPEED * cos(m_angleRad);
		stepY += MOVEMENT_SPEED * sin(m_angleRad);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_angleDeg -= MOVEMENT_SPEED;
		m_angleRad = Math::deg2Rad(m_angleDeg);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_angleDeg += MOVEMENT_SPEED;
		m_angleRad = Math::deg2Rad(m_angleDeg);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		m_angleVertical -= 15;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		m_angleVertical += 15;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_height -= 10;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_height += 10;
	}
	//Log::write("x: %.2f, y: %.2f ang: %.2f", m_posX, m_posY, m_angleDeg);
	m_posX += stepX;
	m_posY += stepY;
}

void PPlayer::setPosition(float x, float y)
{
	m_posX = x;
	m_posY = y;
}

void PPlayer::setAngle(float angleDeg)
{
	m_angleDeg = angleDeg;
	m_angleRad = Math::deg2Rad(angleDeg);
}