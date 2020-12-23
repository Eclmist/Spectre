/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "resolution.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 480
#define MAX_WIDTH 3840
#define MAX_HEIGHT 2160

Resolution::Resolution()
    : m_Width(DEFAULT_WIDTH)
    , m_Height(DEFAULT_HEIGHT)
{
}

bool Resolution::operator==(const Resolution& resolution) const
{
    return m_Width == resolution.m_Width && m_Height == resolution.m_Height;
}

bool Resolution::operator!=(const Resolution& resolution) const
{
    return !(*this == resolution);
}

bool Resolution::IsWithinBounds(const Vector2i& point) const
{
    return point.x >= 0 && point.x < m_Width && point.y >= 0 && point.y < m_Height;
}

void Resolution::SetWidth(int width)
{
    if (width > MAX_WIDTH || width <= 0)
        throw std::invalid_argument("Film width is invalid");

    m_Width = width;
}

void Resolution::SetHeight(int height)
{
    if (height > MAX_HEIGHT || height <= 0)
        throw std::invalid_argument("Film height is invalid");

    m_Height = height;
}

