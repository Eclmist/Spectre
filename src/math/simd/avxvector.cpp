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

#include "avxvector.h"
#include <stdexcept>

bool AvxVector::Equal(const AvxVector& b) const
{
    __m256d diff = _mm256_sub_pd(m_Data, b.m_Data);
    __m256d cmpRes = _mm256_cmp_pd(diff, _mm256_setzero_pd(), _CMP_NEQ_UQ);
    return _mm256_movemask_pd(cmpRes) == 0;
}

AvxVector AvxVector::Normalized() const
{
    return *this * (1.0 / Magnitude());
}

void AvxVector::Normalize()
{
    m_Data = _mm256_mul_pd(m_Data, _mm256_set1_pd(1.0 / Magnitude()));
}

double AvxVector::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

double AvxVector::MagnitudeSquared() const
{
    return Dot(*this, *this);
}

double AvxVector::Dot(const AvxVector& a, const AvxVector& b)
{
    __m256d dot = _mm256_mul_pd(a.m_Data, b.m_Data);
    __m256d hsum = _mm256_hadd_pd(dot, dot);
    return RTC_WIN32_ONLY(hsum.m256d_f64[0] + hsum.m256d_f64[2], hsum[0] + hsum[2]);
}

double AvxVector::AbsDot(const AvxVector& a, const AvxVector& b)
{
    return fabs(Dot(a, b));
}

double AvxVector::Angle(const AvxVector& a, const AvxVector& b)
{
    return acos(CosAngle(a, b));
}

double AvxVector::CosAngle(const AvxVector& a, const AvxVector& b)
{
    return Dot(a, b) / (a.Magnitude() * b.Magnitude());
}

AvxVector AvxVector::Cross(const AvxVector& a, const AvxVector& b)
{
    if (a.w != 0.0 || b.w != 0.0)
        throw std::invalid_argument("Cross product does not exist for 4D vectors");

    __m256d tmp0 = _mm256_set_pd(a.y, a.z, a.x, 0.0);
    __m256d tmp1 = _mm256_set_pd(b.y, b.z, b.x, 0.0);
    tmp0 = _mm256_mul_pd(tmp0, b.m_Data);
    tmp1 = _mm256_mul_pd(tmp1, a.m_Data);
    AvxVector result = _mm256_sub_pd(tmp1, tmp0);
    return AvxVector(result.y, result.z, result.x);
}

