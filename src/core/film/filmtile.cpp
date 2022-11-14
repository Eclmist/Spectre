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

#include "filmtile.h"

FilmTile::FilmTile(const Point2i& pos, const Vector2i& size)
    : m_Rect(pos.x, pos.y, size.x, size.y)
{
    if (size.x <= 0 || size.y <= 0)
        throw std::invalid_argument("Film tile cannot have zero size");

    if (pos.x < 0 || pos.y < 0)
        throw std::invalid_argument("Film tile cannot have negative position");

    m_Pixels.resize(size.x * size.y);
}

Point2i FilmTile::TileToFilmSpace(const Point2i& tileSpacePos) const
{
    return { tileSpacePos.x + m_Rect.x, tileSpacePos.y + m_Rect.y };
}

Point2i FilmTile::FilmToTileSpace(const Point2i& filmSpacePos) const
{
    return { filmSpacePos.x - m_Rect.x, filmSpacePos.y - m_Rect.y };
}

int FilmTile::GetIndex(const Point2i& tileSpacePos) const
{
    Point2i filmSpacePos = TileToFilmSpace(tileSpacePos);

    if (!m_Rect.IsWithinBounds(filmSpacePos.x, filmSpacePos.y))
        throw std::invalid_argument("Point is outside of this film tile");

    return tileSpacePos.x + tileSpacePos.y * m_Rect.w;
}

const Pixel& FilmTile::GetTileSpacePixel(const Point2i& tileSpacePos) const
{
    return m_Pixels[GetIndex(tileSpacePos)];
}

const Pixel& FilmTile::GetFilmSpacePixel(const Point2i& filmSpacePos) const
{
    return GetTileSpacePixel(FilmToTileSpace(filmSpacePos));
}

void FilmTile::SetPixel(const Point2i& tileSpacePoint, const XyzCoefficients& xyz)
{
    SplatPixel(tileSpacePoint, xyz, 1.0);
}

void FilmTile::SplatPixel(const Point2i& tileSpacePoint, const XyzCoefficients& xyz, double deltaArea)
{
    if (deltaArea > 1.0 || deltaArea <= 0.0)
        throw std::invalid_argument("A greater than 1 or smaller than 0 deltaArea is invalid");

    if (deltaArea + m_Pixels[GetIndex(tileSpacePoint)].m_TotalSplat > 1.0 + SMath::Epsilon)
        throw std::invalid_argument("Total splat area for this pixel exceeds 1 given the current delta area");

    m_Pixels[GetIndex(tileSpacePoint)].m_Xyz += xyz * deltaArea;
    m_Pixels[GetIndex(tileSpacePoint)].m_TotalSplat += deltaArea;
}

