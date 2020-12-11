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

const double Vector4::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

const double Vector4::MagnitudeSquared() const
{
    __m256d dot = _mm256_mul_pd(m_Data, m_Data);
    __m256d hsum = _mm256_hadd_pd(dot, dot);
    return RTC_WIN32_ONLY(hsum.m256d_f64[0] + hsum.m256d_f64[2], hsum[0] + hsum[2]);
}
