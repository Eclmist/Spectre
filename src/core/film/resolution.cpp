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

#include "resolution.h"

constexpr int DefaultWidth = 800;
constexpr int DefaultHeight = 480;
constexpr int MaxWidth = 3840;
constexpr int MaxHeight = 2160;

Resolution::Resolution()
    : m_Width(DefaultWidth)
    , m_Height(DefaultHeight)
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

void Resolution::SetWidth(int width)
{
    if (width > MaxWidth || width <= 0)
        throw std::invalid_argument("Film width is invalid");

    m_Width = width;
}

void Resolution::SetHeight(int height)
{
    if (height > MaxHeight || height <= 0)
        throw std::invalid_argument("Film height is invalid");

    m_Height = height;
}

bool Resolution::IsWithinBounds(const Point2i& point) const
{
    return point.x >= 0 && point.x < m_Width && point.y >= 0 && point.y < m_Height;
}

