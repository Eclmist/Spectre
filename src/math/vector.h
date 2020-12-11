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
    Vector4() { m_Data = _mm256_setzero_pd(); }
    Vector4(double v) { m_Data = _mm256_set1_pd(v); }
    Vector4(double x, double y, double z, double w) { m_Data = _mm256_set_pd(x, y, z, w); }
    ~Vector4() = default;

    inline Vector4 operator+(const Vector4& b) const { return Vector4(_mm256_add_pd(m_Data, b.m_Data)); }
    inline Vector4 operator-(const Vector4& b) const { return Vector4(_mm256_sub_pd(m_Data, b.m_Data)); }
    inline const Vector4 operator+() const { return Vector4(m_Data); }
    inline const Vector4 operator-() const { return Vector4(_mm256_mul_pd(m_Data, _mm256_set1_pd(-1.0))); }
    inline void operator+=(const Vector4& b) { m_Data = _mm256_add_pd(m_Data, b.m_Data); }
    inline void operator-=(const Vector4& b) { m_Data = _mm256_sub_pd(m_Data, b.m_Data); }

    inline double operator[](int i) const { return RTC_WIN32_ONLY(m_Data.m256d_f64[3 - i], m_Data[3 - i]); }

    inline double x() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[3], m_Data[3]); }
    inline double y() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[2], m_Data[2]); }
    inline double z() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[1], m_Data[1]); }
    inline double w() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[0], m_Data[0]); }

    inline void x(double x) { RTC_WIN32_ONLY(m_Data.m256d_f64[3], m_Data[3]) = x; }
    inline void y(double y) { RTC_WIN32_ONLY(m_Data.m256d_f64[2], m_Data[2]) = y; }
    inline void z(double z) { RTC_WIN32_ONLY(m_Data.m256d_f64[1], m_Data[1]) = z; }
    inline void w(double w) { RTC_WIN32_ONLY(m_Data.m256d_f64[0], m_Data[0]) = w; }

private:
    Vector4(__m256d data) { m_Data = data; }

private:
    __m256d m_Data;
};

