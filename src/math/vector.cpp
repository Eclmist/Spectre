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

#include "vector.h"

Vector4::Vector4()
{
    m_Data = _mm256_setzero_pd();
}

Vector4::Vector4(double v)
{
    m_Data = _mm256_set1_pd(v);
}

Vector4::Vector4(double _x, double _y, double _z, double _w)
{
    m_Data = _mm256_set_pd(_x, _y, _z, _w);
}

Vector4::Vector4(__m256d data)
{
    m_Data = data;
}

Vector4 Vector4::operator+(const Vector4& b)
{
    return Vector4(_mm256_add_pd(m_Data, b.m_Data));
}

Vector4 Vector4::operator-(const Vector4& b)
{
    return Vector4(_mm256_sub_pd(m_Data, b.m_Data));
}

void Vector4::operator+=(const Vector4& b)
{
    m_Data = _mm256_add_pd(m_Data, b.m_Data);
}

void Vector4::operator-=(const Vector4& b)
{
    m_Data = _mm256_sub_pd(m_Data, b.m_Data);
}

const Vector4 Vector4::operator+()
{
    return Vector4(m_Data);
}

const Vector4 Vector4::operator-()
{
    return Vector4(_mm256_mul_pd(m_Data, _mm256_set1_pd(-1.0)));
}

