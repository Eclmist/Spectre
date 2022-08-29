/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "vector.h"
#include "matrix.h"

typedef Vector<double, 2> Vector2;
typedef Vector<double, 3> Vector3;
typedef Vector<double, 4> Vector4;

typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;

typedef Matrix<double, 2> Matrix2x2;
typedef Matrix<double, 3> Matrix3x3;
typedef Matrix<double, 4> Matrix4x4;

typedef Matrix<int, 2> Matrix2x2i;
typedef Matrix<int, 3> Matrix3x3i;
typedef Matrix<int, 4> Matrix4x4i;

template<typename T, int N>
inline Vector<T, N> operator*(const Matrix<T, N>& mat, const Vector<T, N>& vec)
{
    Vector<T, N> result;
    // TODO: SIMD this

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            result.m_Data[i] += mat.m_Data2D[i][j] * vec.m_Data[j];
        }
    }

    return result;
}

