/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
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

#pragma once

#include "resolution.h"
#include "filmtile.h"
#include "core/spectrum/spectralcoefficients.h"

class Film
{
public:
    Film();
    ~Film() = default;

public:
    inline const Resolution& GetResolution() const { return m_Resolution; }
    inline int GetNumPixels() const { return m_Resolution.GetArea(); }
    inline int GetTileSize() const { return m_TileSize; }

public:
    void SetResolution(const Resolution& resolution);

    FilmTile& GetTile(int index);
    FilmTile& GetTile(const Point2i& position);
	int GetNumTiles() const;

private:
    void SetupTiles();
    int GetTileIndex(const Point2i& position) const;

private:
    Resolution m_Resolution;
    std::vector<FilmTile> m_Tiles;

    const int m_TileSize;
};

