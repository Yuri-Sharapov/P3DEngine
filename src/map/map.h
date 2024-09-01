#pragma once

#include "platform.h"

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

    PMapCell    getCell(int x, int y);
    void        setCell(int x, int y, int height, Color color);

    int         getWidth() { return m_width; };
    int         getHeight() { return m_height; }
    int         getCellCount() { return m_width * m_height; }
private:
    int                     m_width;
    int                     m_height;
    PMapCell*               m_pData;
};