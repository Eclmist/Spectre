/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.

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

#include "film.h"

Film::Film()
{
    ResizePixelData();
}

Pixel Film::GetPixel(unsigned int x, unsigned int y) const
{
    if (!m_Resolution.IsWithinBounds(x, y))
        throw std::invalid_argument("Pixel position out of bounds");

    return m_Pixels[GetIndex(x, y)];
}

void Film::SetResolution(const Resolution& resolution)
{
    m_Resolution = resolution;
    ResizePixelData();
}

void Film::SetPixel(unsigned int x, unsigned int y, float r, float g, float b)
{
    m_Pixels[GetIndex(x, y)].m_RGB[0] = r;
    m_Pixels[GetIndex(x, y)].m_RGB[1] = g;
    m_Pixels[GetIndex(x, y)].m_RGB[2] = b;
}

void Film::ResizePixelData()
{
    m_Pixels = std::make_unique<Pixel[]>(m_Resolution.GetWidth() * m_Resolution.GetHeight());
}

