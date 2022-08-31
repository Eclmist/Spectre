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
#include "point.h"
#include "matrix.h"

typedef Vector<double, 2> Vector2;
typedef Vector<double, 3> Vector3;
typedef Vector<double, 4> Vector4;

typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;

typedef Point<double, 2> Point2;
typedef Point<double, 3> Point3;
typedef Point<double, 4> Point4;

typedef Point<int, 2> Point2i;
typedef Point<int, 3> Point3i;
typedef Point<int, 4> Point4i;

typedef Matrix<double, 2> Matrix2x2;
typedef Matrix<double, 3> Matrix3x3;
typedef Matrix<double, 4> Matrix4x4;

typedef Matrix<int, 2> Matrix2x2i;
typedef Matrix<int, 3> Matrix3x3i;
typedef Matrix<int, 4> Matrix4x4i;

template<typename T, int N>
inline Vector<T, N> operator*(const Matrix<T, N>& m, const Vector<T, N>& v)
{
    Vector<T, N> result;
    // TODO: SIMD this

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            result.m_Data[i] += m.m_Data2D[i][j] * v.m_Data[j];
        }
    }

    return result;
}

template<typename T, int N>
inline Point<T, N> operator+(const Point<T, N>& p, const Vector<T, N>& v)
{

}

