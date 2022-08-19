/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "film.h"

Film::Film()
    : m_TileSize(128)
{
    SetupTiles();
}

FilmTile& Film::GetTile(int index)
{
    return m_Tiles[index];
}

FilmTile& Film::GetTile(const Vector2i& position)
{
    return GetTile(GetTileIndex(position));
}

void Film::SetResolution(const Resolution& resolution)
{
	m_Resolution = resolution;
	SetupTiles();
}

void Film::SetupTiles()
{
    m_Tiles.clear();

    for (int y = 0; y < m_Resolution.GetHeight(); y += m_TileSize)
    {
        for (int x = 0; x < m_Resolution.GetWidth(); x += m_TileSize)
        {
            int sizeX = std::min(m_TileSize, m_Resolution.GetWidth() - x);
            int sizeY = std::min(m_TileSize, m_Resolution.GetHeight() - y);
            m_Tiles.push_back(FilmTile({ x, y }, { sizeX, sizeY }));
        }
    }
}

int Film::GetTileIndex(const Vector2i& position) const
{
    if (!m_Resolution.IsWithinBounds(position))
        throw std::invalid_argument("Position is outside film bounds");

    int x = position.x / m_TileSize;
    int y = position.y / m_TileSize;
    int numTilesX = m_Resolution.GetWidth() / m_TileSize + 1;
    return x + y * numTilesX;
}

int Film::GetNumTiles() const
{
    double numTilesX = m_Resolution.GetWidth() / (double)m_TileSize;
    double numTilesY = m_Resolution.GetHeight() / (double)m_TileSize;
    return (int)std::ceil(numTilesX) * (int)std::ceil(numTilesY);
}

