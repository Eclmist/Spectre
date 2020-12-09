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

#include "system/parallel/atomicfloat.h"

struct Pixel
{
    Pixel(float r = 0, float g = 0, float b = 0)
    {
        m_RGB[0] = r;
        m_RGB[1] = g;
        m_RGB[2] = b;
    }

    Pixel(const Pixel& copy)
    {
        m_RGB[0].Add(copy.m_RGB[0]);
        m_RGB[1].Add(copy.m_RGB[1]);
        m_RGB[2].Add(copy.m_RGB[2]);
    }

    inline Pixel operator=(Pixel p) { return Pixel(p.m_RGB[0], p.m_RGB[1], p.m_RGB[2]); }

    AtomicFloat m_RGB[3];
};

