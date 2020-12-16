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

#include "vector4.h"
#include <stdexcept>
#include "tsimd/tsimd.h"

using namespace tsimd;

Vector4::Vector4(double v)
{
    for (int i = 0; i < 4; ++i)
        m_Data[i] = v;
}

Vector4::Vector4(double x, double y, double z, double w)
{
    m_Data[0] = x;
    m_Data[1] = y;
    m_Data[2] = z;
    m_Data[3] = w;
}

Vector4::Vector4(const double data[4])
{
    for (int i = 0; i < 4; ++i)
        m_Data[i] = data[i];
}

Vector4 Vector4::operator+() const
{
    return *this;
}

Vector4 Vector4::operator-() const
{
    double data[4];
    store(load<vdouble4>(m_Data) * -1, data);
    return Vector4(data);
}

Vector4 Vector4::operator+(const Vector4& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) + load<vdouble4>(b.m_Data), data);
    return data;
}

Vector4& Vector4::operator+=(const Vector4& b)
{
    store(load<vdouble4>(m_Data) + load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

Vector4 Vector4::operator-(const Vector4& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) - load<vdouble4>(b.m_Data), data);
    return data;
}

Vector4& Vector4::operator-=(const Vector4& b)
{
    store(load<vdouble4>(m_Data) - load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

Vector4 Vector4::operator*(const Vector4& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) * load<vdouble4>(b.m_Data), data);
    return data;
}

Vector4& Vector4::operator*=(const Vector4& b)
{
    store(load<vdouble4>(m_Data) * load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

Vector4 Vector4::operator/(const Vector4& b) const
{
    double data[4];
    store(load<vdouble4>(m_Data) / load<vdouble4>(b.m_Data), data);
    return data;
}

Vector4& Vector4::operator/=(const Vector4& b)
{
    store(load<vdouble4>(m_Data) / load<vdouble4>(b.m_Data), m_Data);
    return *this;
}

bool Vector4::operator==(const Vector4& b) const
{
    return all(load<vdouble4>(m_Data) == load<vdouble4>(b.m_Data));
}

bool Vector4::operator!=(const Vector4& b) const
{
    return !(*this == b);
}

Vector4 Vector4::Normalized() const
{
    return *this * (1.0 / Magnitude());
}

void Vector4::Normalize()
{
    store(load<vdouble4>(m_Data) / Magnitude(), m_Data);
}

double Vector4::Magnitude() const
{
    return sqrt(MagnitudeSquared());
}

double Vector4::MagnitudeSquared() const
{
    return Dot(*this, *this);
}

double Vector4::Dot(const Vector4& a, const Vector4& b)
{
    double dot = 0;
    vdouble4 axb = load<vdouble4>(a.m_Data) * load<vdouble4>(b.m_Data);
    foreach(axb, [&](double& v, int) { dot += v; });
    return dot;
}

double Vector4::AbsDot(const Vector4& a, const Vector4& b)
{
    return fabs(Dot(a, b));
}

double Vector4::Angle(const Vector4& a, const Vector4& b)
{
    return acos(CosAngle(a, b));
}

double Vector4::CosAngle(const Vector4& a, const Vector4& b)
{
    return Dot(a, b) / (a.Magnitude() * b.Magnitude());
}

Vector4 Vector4::Cross(const Vector4& a, const Vector4& b)
{
    if (a[3] != 0.0 || b[3] != 0.0)
        throw std::invalid_argument("Cross product does not exist for 4D vectors");

    double data[4];
    vdouble4 tmp0 = vdouble4(a[1], a[2], a[0], 0) * load<vdouble4>(b.m_Data);
    vdouble4 tmp1 = vdouble4(b[1], b[2], b[0], 0) * load<vdouble4>(a.m_Data);
    store(tmp1 - tmp0, data);
    return { data[1], data[2], data[0] };
}

