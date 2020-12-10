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

#include <immintrin.h>

class Vector4
{
public:
    Vector4();
    Vector4(double v);
    Vector4(double x, double y, double z, double w);
    ~Vector4() = default;

    Vector4 operator+(const Vector4& b);
    void operator+=(const Vector4& b);

    double x() const;
    double y() const;
    double z() const;
    double w() const;

    inline void x(double _x) { m_Data = _mm256_set_pd(_x, y(), z(), w()); }
    inline void y(double _y) { m_Data = _mm256_set_pd(x(), _y, z(), w()); }
    inline void z(double _z) { m_Data = _mm256_set_pd(x(), y(), _z, w()); }
    inline void w(double _w) { m_Data = _mm256_set_pd(x(), y(), z(), _w); }

private:
    Vector4(__m256d data);

private:
    __m256d m_Data;
};

