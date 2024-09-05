#pragma once

#include "platform.h"
#include "../player/player.h"

struct PMapCell
{
    int     height;
    Color   color;
};

class PMap
{
public:
    PMap(const char* szMapFile);
    ~PMap();

    void        addPlayer(PPlayer* pPlayer);
    void        setPlayerPos(float x, float y)  { m_pPlayer->setPosition(x, y); }
    void        setPlayerAngle(float angleDeg)  { m_pPlayer->setAngle(angleDeg); }
    Vector2f    getPlayerPos()                  { return m_pPlayer->getPosition(); }
    float       getPlayerAngle()                { return m_pPlayer->getAngleDeg(); }
    float       getPlayerAngleVertical()        { return m_pPlayer->getAngleVertical(); }

    float       getPlayerHeight() { return m_pPlayer->geHeight(); }

    PMapCell    getCell(int x, int y);
    void        setCell(int x, int y, int height, Color color);

    int         getWidth()                      { return m_width; };
    int         getHeight()                     { return m_height; }
    int         getCellCount()                  { return m_width * m_height; }
private:
    int                     m_width;
    int                     m_height;
    PMapCell*               m_pData;

    PPlayer*                m_pPlayer;
};