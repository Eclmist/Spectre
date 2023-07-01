/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
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

#include "pixel.h"

class FilmTile
{
public:
    FilmTile(const Point2i& pos, const Vector2i& size);
    ~FilmTile() = default;

public:
    inline Point2i GetPosition() const { return { m_Rect.x, m_Rect.y }; }
    inline Vector2i GetSize() const { return { m_Rect.w, m_Rect.h }; }

public:
    Point2i TileToFilmSpace(const Point2i& tileSpacePos) const;
    Point2i FilmToTileSpace(const Point2i& filmSpacePos) const;

    const Pixel& GetTileSpacePixel(const Point2i& tileSpacePos) const;
    const Pixel& GetFilmSpacePixel(const Point2i& filmSpacePos) const;

    void SetPixel(const Point2i& tileSpacePoint, const XyzCoefficients& xyz);
    void SplatPixel(const Point2i& tileSpacePoint, const XyzCoefficients& xyz, double deltaArea);

private:
    friend class FilmTileTest_CanGetIndex_Test;
    int GetIndex(const Point2i& tileSpacePos) const;

private:
    const SMath::Rect<int> m_Rect;
    std::vector<Pixel> m_Pixels;
};