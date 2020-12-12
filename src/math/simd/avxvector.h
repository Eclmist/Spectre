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
    AvxVector(double v = 0) { m_Data = _mm256_set1_pd(v); }
    AvxVector(double x, double y, double z = 0, double w = 0) { m_Data = _mm256_set_pd(x, y, z, w); }
    ~AvxVector() = default;

    inline const AvxVector operator-() const { return _mm256_mul_pd(m_Data, _mm256_set1_pd(-1.0)); }
    inline const AvxVector operator+() const { return m_Data; }

    inline AvxVector operator+(const AvxVector& b) const { return _mm256_add_pd(m_Data, b.m_Data); }
    inline AvxVector& operator+=(const AvxVector& b) { m_Data = _mm256_add_pd(m_Data, b.m_Data); return *this; }

    inline AvxVector operator-(const AvxVector& b) const { return _mm256_sub_pd(m_Data, b.m_Data); }
    inline AvxVector& operator-=(const AvxVector& b) { m_Data = _mm256_sub_pd(m_Data, b.m_Data); return *this; }

    inline AvxVector operator*(const AvxVector& s) const { return _mm256_mul_pd(m_Data, s.m_Data); }
    inline AvxVector& operator*=(const AvxVector& s) { m_Data = _mm256_mul_pd(m_Data, s.m_Data); return *this; }

    /* Don't implement division until there is a good way to check for NaNs */

    inline double operator[](int i) const { return RTC_WIN32_ONLY(m_Data.m256d_f64[3 - i], m_Data[3 - i]); }
    inline bool operator==(const AvxVector& b) const { return Equal(b); }
    inline bool operator!=(const AvxVector& b) const { return !Equal(b); }

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

    static double Dot(const AvxVector& a, const AvxVector& b);
    static double AbsDot(const AvxVector& a, const AvxVector& b);
    static double Angle(const AvxVector& a, const AvxVector& b);
    static double CosAngle(const AvxVector& a, const AvxVector& b);
    static AvxVector Cross(const AvxVector& a, const AvxVector& b);

    union
    {
        struct { double w, z, y, x; };
        struct { __m256d m_Data; };
    };

private:
    AvxVector(__m256d data) { m_Data = data; }
};

