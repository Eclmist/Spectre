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

#include "math.h"
#include <immintrin.h>
#include "system/platform/platformutils.h"

class AvxVector
{
public:
    AvxVector() { m_Data = _mm256_setzero_pd(); }
    AvxVector(double v) { m_Data = _mm256_set1_pd(v); }
    AvxVector(double x, double y, double z, double w) { m_Data = _mm256_set_pd(x, y, z, w); }
    ~AvxVector() = default;

    inline AvxVector operator+(const AvxVector& b) const { return _mm256_add_pd(m_Data, b.m_Data); }
    inline const AvxVector operator+() const { return m_Data; }
    inline void operator+=(const AvxVector& b) { m_Data = _mm256_add_pd(m_Data, b.m_Data); }

    inline AvxVector operator-(const AvxVector& b) const { return _mm256_sub_pd(m_Data, b.m_Data); }
    inline const AvxVector operator-() const { return _mm256_mul_pd(m_Data, _mm256_set1_pd(-1.0)); }
    inline void operator-=(const AvxVector& b) { m_Data = _mm256_sub_pd(m_Data, b.m_Data); }

    inline AvxVector operator*(const AvxVector& scale) const { return _mm256_mul_pd(m_Data, scale.m_Data); }
    inline void operator*=(const AvxVector& scale) { m_Data = _mm256_mul_pd(m_Data, scale.m_Data); }

    /* Don't implement division until there is a good way to check for NaNs */

    inline double operator[](int i) const { return RTC_WIN32_ONLY(m_Data.m256d_f64[3 - i], m_Data[3 - i]); }
    inline bool operator==(const AvxVector& b) const { return Equal(b); }
    inline bool operator!=(const AvxVector& b) const { return !Equal(b); }

    inline double x() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[3], m_Data[3]); }
    inline double y() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[2], m_Data[2]); }
    inline double z() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[1], m_Data[1]); }
    inline double w() const { return RTC_WIN32_ONLY(m_Data.m256d_f64[0], m_Data[0]); }

    inline void x(double x) { RTC_WIN32_ONLY(m_Data.m256d_f64[3], m_Data[3]) = x; }
    inline void y(double y) { RTC_WIN32_ONLY(m_Data.m256d_f64[2], m_Data[2]) = y; }
    inline void z(double z) { RTC_WIN32_ONLY(m_Data.m256d_f64[1], m_Data[1]) = z; }
    inline void w(double w) { RTC_WIN32_ONLY(m_Data.m256d_f64[0], m_Data[0]) = w; }

public:
    const bool Equal(const AvxVector& b) const;
    const void Normalize();
    const AvxVector Normalized() const;
    const double Magnitude() const;
    const double MagnitudeSquared() const;

public:
    static AvxVector Zero()    { return {0.0, 0.0, 0.0, 0.0}; }
    static AvxVector Up()      { return {0.0, 1.0, 0.0, 0.0}; }
    static AvxVector Right()   { return {1.0, 0.0, 0.0, 0.0}; }
    static AvxVector Forward() { return {0.0, 0.0, -1.0, 0.0}; }

private:
    AvxVector(__m256d data) { m_Data = data; }

private:
    __m256d m_Data;
};

