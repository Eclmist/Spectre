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

const bool AvxVector::Equal(const AvxVector& b) const
{
    __m256d diff = _mm256_sub_pd(m_Data, b.m_Data);
    __m256d cmpRes = _mm256_cmp_pd(diff, _mm256_setzero_pd(), _CMP_NEQ_UQ);
    return _mm256_movemask_pd(cmpRes) == 0;
}

const AvxVector AvxVector::Normalized() const
{
    return *this * (1.0 / Magnitude());
}

const void AvxVector::Normalize()
{
    m_Data = _mm256_mul_pd(m_Data, _mm256_set1_pd(1.0 / Magnitude()));
}

const double AvxVector::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

const double AvxVector::MagnitudeSquared() const
{
    __m256d dot = _mm256_mul_pd(m_Data, m_Data);
    __m256d hsum = _mm256_hadd_pd(dot, dot);
    return RTC_WIN32_ONLY(hsum.m256d_f64[0] + hsum.m256d_f64[2], hsum[0] + hsum[2]);
}

