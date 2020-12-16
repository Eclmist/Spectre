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

#include "avxmatrix.h"
#include <immintrin.h>
#include "system/platform/platformutils.h"

AvxMatrix::AvxMatrix()
{
    m_Data[0]  = 1.0; m_Data[1]  = 0.0; m_Data[2]  = 0.0; m_Data[3]  = 0.0;
    m_Data[4]  = 0.0; m_Data[5]  = 1.0; m_Data[6]  = 0.0; m_Data[7]  = 0.0;
    m_Data[8]  = 0.0; m_Data[9]  = 0.0; m_Data[10] = 1.0; m_Data[11] = 0.0;
    m_Data[12] = 0.0; m_Data[13] = 0.0; m_Data[14] = 0.0; m_Data[15] = 1.0;
}

AvxMatrix::AvxMatrix(const double m[16])
{
    for (int i = 0; i < 16; ++i)
        m_Data[i] = m[i];
}

AvxMatrix::AvxMatrix(const double data[4][4])
{
    for (int s = 0; s < 4; ++s)
    {
        for (int t = 0; t < 4; ++t)
        {
            m_Data2D[s][t] = data[s][t];
        }
    }
}

AvxMatrix::AvxMatrix(
    double _11, double _12, double _13, double _14,
    double _21, double _22, double _23, double _24,
    double _31, double _32, double _33, double _34,
    double _41, double _42, double _43, double _44)
{
    m_Data[0]  = _11; m_Data[1]  = _12; m_Data[2]  = _13; m_Data[3]  = _14;
    m_Data[4]  = _21; m_Data[5]  = _22; m_Data[6]  = _23; m_Data[7]  = _24;
    m_Data[8]  = _31; m_Data[9]  = _32; m_Data[10] = _33; m_Data[11] = _34;
    m_Data[12] = _41; m_Data[13] = _42; m_Data[14] = _43; m_Data[15] = _44;
}

bool AvxMatrix::operator==(const AvxMatrix& m2) const
{
    __m256d row0 = _mm256_load_pd(m_Data2D[0]);
    __m256d row1 = _mm256_load_pd(m_Data2D[1]);
    __m256d row2 = _mm256_load_pd(m_Data2D[2]);
    __m256d row3 = _mm256_load_pd(m_Data2D[3]);

    __m256d cmp0 = _mm256_cmp_pd(row0, _mm256_load_pd(m2.m_Data2D[0]), _CMP_NEQ_OQ);
    __m256d cmp1 = _mm256_cmp_pd(row1, _mm256_load_pd(m2.m_Data2D[1]), _CMP_NEQ_OQ);
    __m256d cmp2 = _mm256_cmp_pd(row2, _mm256_load_pd(m2.m_Data2D[2]), _CMP_NEQ_OQ);
    __m256d cmp3 = _mm256_cmp_pd(row3, _mm256_load_pd(m2.m_Data2D[3]), _CMP_NEQ_OQ);

    __m256d mask = _mm256_or_pd(cmp0, cmp1);
    mask = _mm256_or_pd(mask, cmp2);
    mask = _mm256_or_pd(mask, cmp3);

    return _mm256_movemask_pd(mask) == 0;
}

AvxMatrix AvxMatrix::operator*(const AvxMatrix& m2) const
{
    double data[4][4];

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            __m256d row = _mm256_load_pd(m_Data2D[i]);
            __m256d col = _mm256_set_pd(m2.m_Data2D[3][j], m2.m_Data2D[2][j], m2.m_Data2D[1][j], m2.m_Data2D[0][j]);
            __m256d mult = _mm256_mul_pd(row, col);
            __m256d hsum = _mm256_hadd_pd(mult, mult);

            data[i][j] = RTC_WIN32_ONLY(hsum.m256d_f64[0] + hsum.m256d_f64[2], hsum[0] + hsum[2]);
        }
    }

    return AvxMatrix(data);
}

bool AvxMatrix::IsIdentity() const
{
    return *this == AvxMatrix(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
}

double AvxMatrix::GetDeterminant() const
{
    return (m_Data[0] * m_Data[5] - m_Data[1] * m_Data[4]) * (m_Data[10] * m_Data[15] - m_Data[11] * m_Data[14]) -
           (m_Data[0] * m_Data[6] - m_Data[2] * m_Data[4]) * (m_Data[9]  * m_Data[15] - m_Data[11] * m_Data[13]) +
           (m_Data[0] * m_Data[7] - m_Data[3] * m_Data[4]) * (m_Data[9]  * m_Data[14] - m_Data[10] * m_Data[13]) +
           (m_Data[1] * m_Data[6] - m_Data[2] * m_Data[5]) * (m_Data[8]  * m_Data[15] - m_Data[11] * m_Data[12]) -
           (m_Data[1] * m_Data[7] - m_Data[3] * m_Data[5]) * (m_Data[8]  * m_Data[14] - m_Data[10] * m_Data[12]) +
           (m_Data[2] * m_Data[7] - m_Data[3] * m_Data[6]) * (m_Data[8]  * m_Data[13] - m_Data[9]  * m_Data[12]);
}

AvxMatrix AvxMatrix::Transposed() const
{
    return AvxMatrix(m_Data[0], m_Data[4], m_Data[8], m_Data[12],
                     m_Data[1], m_Data[5], m_Data[9], m_Data[13],
                     m_Data[2], m_Data[6], m_Data[10], m_Data[14],
                     m_Data[3], m_Data[7], m_Data[11], m_Data[15]);
}

AvxMatrix AvxMatrix::Inversed() const
{
    double d = GetDeterminant();
    if (fabs(d) < 0.0001)
        return AvxMatrix();

    // use Cramer's rule
    d = 1.0f / d;
    AvxMatrix out;
    out.m_Data[0]  = d * (m_Data[5]  * (m_Data[10] * m_Data[15] - m_Data[11] * m_Data[14]) + m_Data[6]  * (m_Data[11] * m_Data[13] - m_Data[9]  * m_Data[15]) + m_Data[7]  * (m_Data[9]  * m_Data[14] - m_Data[10] * m_Data[13]));
    out.m_Data[1]  = d * (m_Data[9]  * (m_Data[2]  * m_Data[15] - m_Data[3]  * m_Data[14]) + m_Data[10] * (m_Data[3]  * m_Data[13] - m_Data[1]  * m_Data[15]) + m_Data[11] * (m_Data[1]  * m_Data[14] - m_Data[2]  * m_Data[13]));
    out.m_Data[2]  = d * (m_Data[13] * (m_Data[2]  * m_Data[7]  - m_Data[3]  * m_Data[6])  + m_Data[14] * (m_Data[3]  * m_Data[5]  - m_Data[1]  * m_Data[7])  + m_Data[15] * (m_Data[1]  * m_Data[6]  - m_Data[2]  * m_Data[5]));
    out.m_Data[3]  = d * (m_Data[1]  * (m_Data[7]  * m_Data[10] - m_Data[6]  * m_Data[11]) + m_Data[2]  * (m_Data[5]  * m_Data[11] - m_Data[7]  * m_Data[9])  + m_Data[3]  * (m_Data[6]  * m_Data[9]  - m_Data[5]  * m_Data[10]));
    out.m_Data[4]  = d * (m_Data[6]  * (m_Data[8]  * m_Data[15] - m_Data[11] * m_Data[12]) + m_Data[7]  * (m_Data[10] * m_Data[12] - m_Data[8]  * m_Data[14]) + m_Data[4]  * (m_Data[11] * m_Data[14] - m_Data[10] * m_Data[15]));
    out.m_Data[5]  = d * (m_Data[10] * (m_Data[0]  * m_Data[15] - m_Data[3]  * m_Data[12]) + m_Data[11] * (m_Data[2]  * m_Data[12] - m_Data[0]  * m_Data[14]) + m_Data[8]  * (m_Data[3]  * m_Data[14] - m_Data[2]  * m_Data[15]));
    out.m_Data[6]  = d * (m_Data[14] * (m_Data[0]  * m_Data[7]  - m_Data[3]  * m_Data[4])  + m_Data[15] * (m_Data[2]  * m_Data[4]  - m_Data[0]  * m_Data[6])  + m_Data[12] * (m_Data[3]  * m_Data[6]  - m_Data[2]  * m_Data[7]));
    out.m_Data[7]  = d * (m_Data[2]  * (m_Data[7]  * m_Data[8]  - m_Data[4]  * m_Data[11]) + m_Data[3]  * (m_Data[4]  * m_Data[10] - m_Data[6]  * m_Data[8])  + m_Data[0]  * (m_Data[6]  * m_Data[11] - m_Data[7]  * m_Data[10]));
    out.m_Data[8]  = d * (m_Data[7]  * (m_Data[8]  * m_Data[13] - m_Data[9]  * m_Data[12]) + m_Data[4]  * (m_Data[9]  * m_Data[15] - m_Data[11] * m_Data[13]) + m_Data[5]  * (m_Data[11] * m_Data[12] - m_Data[8]  * m_Data[15]));
    out.m_Data[9]  = d * (m_Data[11] * (m_Data[0]  * m_Data[13] - m_Data[1]  * m_Data[12]) + m_Data[8]  * (m_Data[1]  * m_Data[15] - m_Data[3]  * m_Data[13]) + m_Data[9]  * (m_Data[3]  * m_Data[12] - m_Data[0]  * m_Data[15]));
    out.m_Data[10] = d * (m_Data[15] * (m_Data[0]  * m_Data[5]  - m_Data[1]  * m_Data[4])  + m_Data[12] * (m_Data[1]  * m_Data[7]  - m_Data[3]  * m_Data[5])  + m_Data[13] * (m_Data[3]  * m_Data[4]  - m_Data[0]  * m_Data[7]));
    out.m_Data[11] = d * (m_Data[3]  * (m_Data[5]  * m_Data[8]  - m_Data[4]  * m_Data[9])  + m_Data[0]  * (m_Data[7]  * m_Data[9]  - m_Data[5]  * m_Data[11]) + m_Data[1]  * (m_Data[4]  * m_Data[11] - m_Data[7]  * m_Data[8]));
    out.m_Data[12] = d * (m_Data[4]  * (m_Data[10] * m_Data[13] - m_Data[9]  * m_Data[14]) + m_Data[5]  * (m_Data[8]  * m_Data[14] - m_Data[10] * m_Data[12]) + m_Data[6]  * (m_Data[9]  * m_Data[12] - m_Data[8]  * m_Data[13]));
    out.m_Data[13] = d * (m_Data[8]  * (m_Data[2]  * m_Data[13] - m_Data[1]  * m_Data[14]) + m_Data[9]  * (m_Data[0]  * m_Data[14] - m_Data[2]  * m_Data[12]) + m_Data[10] * (m_Data[1]  * m_Data[12] - m_Data[0]  * m_Data[13]));
    out.m_Data[14] = d * (m_Data[12] * (m_Data[2]  * m_Data[5]  - m_Data[1]  * m_Data[6])  + m_Data[13] * (m_Data[0]  * m_Data[6]  - m_Data[2]  * m_Data[4])  + m_Data[14] * (m_Data[1]  * m_Data[4]  - m_Data[0]  * m_Data[5]));
    out.m_Data[15] = d * (m_Data[0]  * (m_Data[5]  * m_Data[10] - m_Data[6]  * m_Data[9])  + m_Data[1]  * (m_Data[6]  * m_Data[8]  - m_Data[4]  * m_Data[10]) + m_Data[2]  * (m_Data[4]  * m_Data[9]  - m_Data[5]  * m_Data[8]));

    return out;
}

