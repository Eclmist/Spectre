/*
    This file is part of RTCore, an open-source physically based
    renderer.

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

FilmTile::FilmTile(const Vector2i& pos, const Vector2i& size)
    : m_Rect(pos.x, pos.y, size.x, size.y)
{
    if (size.x <= 0 || size.y <= 0)
        throw std::invalid_argument("Film tile cannot have zero size");

    if (pos.x < 0 || pos.y < 0)
        throw std::invalid_argument("Film tile cannot have negative position");

    m_Pixels.resize(size.x * size.y);
}

Vector2i FilmTile::TileToFilmSpace(const Vector2i& tileSpacePos) const
{
    return { tileSpacePos.x + m_Rect.x, tileSpacePos.y + m_Rect.y };
}

Vector2i FilmTile::FilmToTileSpace(const Vector2i& filmSpacePos) const
{
    return { filmSpacePos.x - m_Rect.x, filmSpacePos.y - m_Rect.y };
}

int FilmTile::GetIndex(const Vector2i& tileSpacePos) const
{
    Vector2i filmSpacePos = TileToFilmSpace(tileSpacePos);

    if (!m_Rect.IsWithinBounds(filmSpacePos.x, filmSpacePos.y))
        throw std::invalid_argument("Point is outside of this film tile");

    return tileSpacePos.x + tileSpacePos.y * m_Rect.w;
}

const Pixel& FilmTile::GetTileSpacePixel(const Vector2i& tileSpacePos) const
{
    return m_Pixels[GetIndex(tileSpacePos)];
}

const Pixel& FilmTile::GetFilmSpacePixel(const Vector2i& filmSpacePos) const
{
    return GetTileSpacePixel(FilmToTileSpace(filmSpacePos));
}

void FilmTile::SetPixel(const Vector2i& tileSpacePoint, const XyzCoefficients& xyz)
{
    SplatPixel(tileSpacePoint, xyz, 1.0);
}

void FilmTile::SplatPixel(const Vector2i& tileSpacePoint, const XyzCoefficients& xyz, double deltaArea)
{
    if (deltaArea > 1.0 || deltaArea <= 0.0)
        throw std::invalid_argument("A greater than 1 or smaller than 0 deltaArea is invalid");

    if (deltaArea + m_Pixels[GetIndex(tileSpacePoint)].m_TotalSplat > 1.0 + Math::Epsilon)
        throw std::invalid_argument("Total splat area for this pixel exceeds 1 given the current delta area");

    m_Pixels[GetIndex(tileSpacePoint)].m_Xyz += xyz * deltaArea;
    m_Pixels[GetIndex(tileSpacePoint)].m_TotalSplat += deltaArea;
}

