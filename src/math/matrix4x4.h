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

#pragma once

#include "math.h"

class Matrix4x4
{
public:
    Matrix4x4();
    Matrix4x4(const double data[16]);
    Matrix4x4(const double data[4][4]);
    Matrix4x4(double _11, double _12, double _13, double _14,
              double _21, double _22, double _23, double _24,
              double _31, double _32, double _33, double _34,
              double _41, double _42, double _43, double _44);

    inline double operator[](int i) const { return m_Data[i]; }
    inline double& operator[](int i) { return m_Data[i]; }

    bool operator==(const Matrix4x4& m2) const;
    Matrix4x4 operator*(const Matrix4x4& m2) const;

    bool IsIdentity() const;
    Matrix4x4 Transposed() const;

public:
    union
    {
        struct { double m_Data[16]; };
        struct { double m_Data2D[4][4]; };
        struct 
        {
            double m_11, m_12, m_13, m_14;
            double m_21, m_22, m_23, m_24;
            double m_31, m_32, m_33, m_34;
            double m_41, m_42, m_43, m_44;
        };
    };
};

