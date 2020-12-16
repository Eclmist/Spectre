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
#include "tsimd/tsimd.h"

using namespace tsimd;

AvxVector::AvxVector(double v)
{
    for (int i = 0; i < 4; ++i)
        m_Data[i] = v;
}

AvxVector::AvxVector(double x, double y, double z, double w)
{
    m_Data[0] = x;
    m_Data[1] = y;
    m_Data[2] = z;
    m_Data[3] = w;
}

AvxVector::AvxVector(const double data[4])
{
    for (int i = 0; i < 4; ++i)
        m_Data[i] = data[i];
}

AvxVector AvxVector::operator+() const
{
    return *this;
}

AvxVector AvxVector::operator-() const
{
    double data[4];
    store(load<vdouble4>(m_Data) * -1, data);
    return AvxVector(data);
}

AvxVector AvxVector::operator+(const AvxVector& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) + load<vdouble4>(b.m_Data), data);
    return data;
}

AvxVector& AvxVector::operator+=(const AvxVector& b)
{
    store(load<vdouble4>(m_Data) + load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

AvxVector AvxVector::operator-(const AvxVector& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) - load<vdouble4>(b.m_Data), data);
    return data;
}

AvxVector& AvxVector::operator-=(const AvxVector& b)
{
    store(load<vdouble4>(m_Data) - load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

AvxVector AvxVector::operator*(const AvxVector& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) * load<vdouble4>(b.m_Data), data);
    return data;
}

AvxVector& AvxVector::operator*=(const AvxVector& b)
{
    store(load<vdouble4>(m_Data) * load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

AvxVector AvxVector::operator/(const AvxVector& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) / load<vdouble4>(b.m_Data), data);
    return data;
}

AvxVector& AvxVector::operator/=(const AvxVector& b)
{
    store(load<vdouble4>(m_Data) / load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

bool AvxVector::operator==(const AvxVector& b) const
{
    return all(load<vdouble4>(m_Data) == load<vdouble4>(b.m_Data));
}

bool AvxVector::operator!=(const AvxVector& b) const
{
    return !(*this == b);
}

AvxVector AvxVector::Normalized() const
{
    return *this * (1.0 / Magnitude());
}

void AvxVector::Normalize()
{
    store(load<vdouble4>(m_Data) / Magnitude(), m_Data);
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
    double dot = 0;
    vdouble4 axb = load<vdouble4>(a.m_Data) * load<vdouble4>(b.m_Data);
    foreach(axb, [&](double& v, int) { dot += v; });
    return dot;
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
    if (a[3] != 0.0 || b[3] != 0.0)
        throw std::invalid_argument("Cross product does not exist for 4D vectors");

    double data[4];
    vdouble4 tmp0 = vdouble4(a[1], a[2], a[0], 0) * load<vdouble4>(b.m_Data);
    vdouble4 tmp1 = vdouble4(b[1], b[2], b[0], 0) * load<vdouble4>(a.m_Data);
    store(tmp1 - tmp0, data);
    return { data[1], data[2], data[0] };
}

