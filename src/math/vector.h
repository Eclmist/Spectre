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
#include "system/platform/platformutils.h"

class Vector4
{
public:
    Vector4();
    Vector4(double v);
    Vector4(double x, double y, double z, double w);
    ~Vector4() = default;

    Vector4 operator+(const Vector4& b);
    Vector4 operator-(const Vector4& b);
    void operator+=(const Vector4& b);
    void operator-=(const Vector4& b);
    const Vector4 operator+();
    const Vector4 operator-();

    inline double x() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[3], m_Data[3]); }
    inline double y() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[2], m_Data[2]); }
    inline double z() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[1], m_Data[1]); }
    inline double w() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[0], m_Data[0]); }

    inline void x(double x) { RTC_WIN32_ONLY(m_Data.m256d_f64[3], m_Data[3]) = x; }
    inline void y(double y) { RTC_WIN32_ONLY(m_Data.m256d_f64[2], m_Data[2]) = y; }
    inline void z(double z) { RTC_WIN32_ONLY(m_Data.m256d_f64[1], m_Data[1]) = z; }
    inline void w(double w) { RTC_WIN32_ONLY(m_Data.m256d_f64[0], m_Data[0]) = w; }

private:
    Vector4(__m256d data);

private:
    __m256d m_Data;
};

