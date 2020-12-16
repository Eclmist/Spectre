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
#include "tsimd/tsimd.h"

class Vector4
{
public:
    Vector4(double v = 0);
    Vector4(double x, double y, double z = 0, double w = 0);
    Vector4(const double data[4]);
    ~Vector4() = default;

    Vector4 operator+() const;
    Vector4 operator-() const;

    // Component-wise arithmetics
    Vector4 operator+(const Vector4& b) const;
    Vector4& operator+=(const Vector4& b);
    Vector4 operator-(const Vector4& b) const;
    Vector4& operator-=(const Vector4& b);
    Vector4 operator*(const Vector4& b) const;
    Vector4& operator*=(const Vector4& b);
    Vector4 operator/(const Vector4& b) const;
    Vector4& operator/=(const Vector4& b);
    bool operator==(const Vector4& b) const;
    bool operator!=(const Vector4& b) const;

    inline double operator[](int i) const { return m_Data[i]; }
    inline double& operator[](int i) { return m_Data[i]; }

public:
    void Normalize();
    Vector4 Normalized() const;
    double Magnitude() const;
    double MagnitudeSquared() const;

public:
    static Vector4 Zero()    { return {0.0, 0.0, 0.0, 0.0}; }
    static Vector4 Up()      { return {0.0, 1.0, 0.0, 0.0}; }
    static Vector4 Right()   { return {1.0, 0.0, 0.0, 0.0}; }
    static Vector4 Forward() { return {0.0, 0.0, -1.0, 0.0}; }

    static double Dot(const Vector4& a, const Vector4& b);
    static double AbsDot(const Vector4& a, const Vector4& b);
    static double Angle(const Vector4& a, const Vector4& b);
    static double CosAngle(const Vector4& a, const Vector4& b);
    static Vector4 Cross(const Vector4& a, const Vector4& b);

    double m_Data[4];
};

