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

#include "film.h"

Film::Film()
{
    ResizePixelData();
}

Pixel Film::GetPixel(const Vector2u& point) const
{
    if (!m_Resolution.IsWithinBounds(point))
        throw std::invalid_argument("Pixel position out of bounds");

    return m_Pixels[GetIndex(point)];
}

void Film::SetResolution(const Resolution& resolution)
{
    m_Resolution = resolution;
    ResizePixelData();
}

void Film::SetPixel(const Vector2u& point, const XYZCoefficients& xyz)
{
    m_Pixels[GetIndex(point)].m_XYZ = xyz;
}

void Film::SplatPixel(const Vector2u& point, const XYZCoefficients& xyz, double deltaArea)
{
    if (!m_Resolution.IsWithinBounds(point))
        throw std::invalid_argument("Pixel position out of bounds");

    if (deltaArea > 1.0 || deltaArea <= 0.0)
        throw std::invalid_argument("A greater than 1 or smaller than 0 deltaArea is invalid ");

    if (deltaArea + m_Pixels[GetIndex(point)].m_TotalSplat > 1.0)
        throw std::invalid_argument("Total splat area for this pixel exceeds 1 given the current delta area");
    
    m_Pixels[GetIndex(point)].m_XYZ += xyz * deltaArea;
    m_Pixels[GetIndex(point)].m_TotalSplat += deltaArea;
}

void Film::ResizePixelData()
{
    m_Pixels = std::make_unique<Pixel[]>(m_Resolution.GetWidth() * m_Resolution.GetHeight());
}

