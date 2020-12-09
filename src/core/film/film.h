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

#pragma once

#include "resolution.h"
#include "pixel.h"

class Film
{
public:
    Film();
    ~Film() = default;

    inline const Resolution& GetResolution() const { return m_Resolution; }
    inline int GetIndex(unsigned int x, unsigned int y) const { return x + y * m_Resolution.GetWidth(); }
    inline int GetNumPixels() const { return m_Resolution.GetWidth() * m_Resolution.GetHeight(); }
    Pixel GetPixel(unsigned int x, unsigned int y) const;

    void SetResolution(const Resolution& resolution);
    void SetPixel(unsigned int x, unsigned int y, float r, float g, float b);

private:
    void ResizePixelData();

private:
    Resolution m_Resolution;
    std::unique_ptr<Pixel[]> m_Pixels;
};

