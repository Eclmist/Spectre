/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.

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

#include "matrix4x4.h"
#include "tsimd/tsimd.h"

using namespace tsimd;

Matrix4x4::Matrix4x4()
{
    m_Data[0]  = 1.0; m_Data[1]  = 0.0; m_Data[2]  = 0.0; m_Data[3]  = 0.0;
    m_Data[4]  = 0.0; m_Data[5]  = 1.0; m_Data[6]  = 0.0; m_Data[7]  = 0.0;
    m_Data[8]  = 0.0; m_Data[9]  = 0.0; m_Data[10] = 1.0; m_Data[11] = 0.0;
    m_Data[12] = 0.0; m_Data[13] = 0.0; m_Data[14] = 0.0; m_Data[15] = 1.0;
}

Matrix4x4::Matrix4x4(const double m[16])
{
    for (int i = 0; i < 16; ++i)
        m_Data[i] = m[i];
}

Matrix4x4::Matrix4x4(const double data[4][4])
{
    for (int s = 0; s < 4; ++s)
    {
        for (int t = 0; t < 4; ++t)
        {
            m_Data2D[s][t] = data[s][t];
        }
    }
}

Matrix4x4::Matrix4x4(
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

bool Matrix4x4::operator==(const Matrix4x4& m2) const
{
    vdoublen<16> data1 = load<vdoublen<16>>(m_Data);
    vdoublen<16> data2 = load<vdoublen<16>>(m2.m_Data);
    return all(near_equal(data1, data2));
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m2) const
{
    double data[4][4] = {0};

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            vdouble4 row = load<vdouble4>(m_Data2D[i]);
            vdouble4 col(m2.m_Data2D[0][j], m2.m_Data2D[1][j], m2.m_Data2D[2][j], m2.m_Data2D[3][j]);
            vdouble4 mult = row * col;
            foreach(mult, [&](double& v, int) {data[i][j] += v; });
        }
    }

    return Matrix4x4(data);
}

bool Matrix4x4::IsIdentity() const
{
    return *this == Matrix4x4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
}

Matrix4x4 Matrix4x4::Transposed() const
{
    return Matrix4x4(m_Data[0], m_Data[4], m_Data[8], m_Data[12],
                     m_Data[1], m_Data[5], m_Data[9], m_Data[13],
                     m_Data[2], m_Data[6], m_Data[10], m_Data[14],
                     m_Data[3], m_Data[7], m_Data[11], m_Data[15]);
}

