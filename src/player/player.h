#pragma once

#include "platform.h"

class PPlayer
{
	const float MOVEMENT_SPEED = 5.2f;
public:
	PPlayer(float x, float y);
	~PPlayer();

	void update();

	void	setPosition(float x, float y);
	void	setAngle(float angleDeg);

	float	getAngleVertical() { return m_angleVertical; }

	float	getAngleDeg() { return m_angleDeg; }
	float	getAngleRad() { return m_angleRad; }
	Vector2f getPosition() { Vector2f vect; vect.x = m_posX; vect.y = m_posY; return vect; }

	float	geHeight() { return m_height; }
private:
	float	m_posX;
	float	m_posY;
	float	m_angleDeg;
	float	m_angleRad;

	float	m_height;

	float	m_angleVertical;
};