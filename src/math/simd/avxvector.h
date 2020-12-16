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

class AvxVector
{
public:
    AvxVector(double v = 0);
    AvxVector(double x, double y, double z = 0, double w = 0);
    AvxVector(const double data[4]);
    ~AvxVector() = default;

    AvxVector operator+() const;
    AvxVector operator-() const;

    // Component-wise arithmetics
    AvxVector operator+(const AvxVector& b) const;
    AvxVector& operator+=(const AvxVector& b);
    AvxVector operator-(const AvxVector& b) const;
    AvxVector& operator-=(const AvxVector& b);
    AvxVector operator*(const AvxVector& b) const;
    AvxVector& operator*=(const AvxVector& b);
    AvxVector operator/(const AvxVector& b) const;
    AvxVector& operator/=(const AvxVector& b);
    bool operator==(const AvxVector& b) const;
    bool operator!=(const AvxVector& b) const;

    inline double operator[](int i) const { return m_Data[i]; }
    inline double& operator[](int i) { return m_Data[i]; }

public:
    void Normalize();
    AvxVector Normalized() const;
    double Magnitude() const;
    double MagnitudeSquared() const;

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

    double m_Data[4];
};

