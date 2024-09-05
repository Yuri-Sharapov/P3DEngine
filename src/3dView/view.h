#pragma once

#include "platform.h"
#include "map/map.h"
#include "player/player.h"

class P3DView
{
	const float FOV_HORIZONTAL	= 90.0f;
	const float FOV_VERTICAL	= 60.0f;
	const float CAM_HEIGHT		= 2.0f;
public:
	P3DView(RenderWindow* pWnd, PMap* pMap);
	~P3DView();

	void update();
private:
	RenderWindow*	m_pWnd = nullptr;
	PMap*			m_pMap = nullptr;

	Image			m_imageBuf;
};