/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "tsimd/tsimd.h"
#include <algorithm>

template<typename T, int N>
Vector<T, N>::Vector(T v)
{
    for (int i = 0; i < N; ++i)
        this->m_Data[i] = v;

    for (int i = N; i < 4; ++i)
        this->m_Data[i] = 0;
}

template<typename T, int N>
Vector<T, N>::Vector(T x, T y)
{
    static_assert(N == 2, "2 component constructor only available for N = 2");
    this->m_Data[0] = x;
    this->m_Data[1] = y;
}

template<typename T, int N>
Vector<T, N>::Vector(T x, T y, T z)
{
    static_assert(N == 3, "3 component constructor only available for N = 3");
    this->m_Data[0] = x;
    this->m_Data[1] = y;
    this->m_Data[2] = z;
}

template<typename T, int N>
Vector<T, N>::Vector(T x, T y, T z, T w)
{
    static_assert(N == 4, "4 component constructor only available for N = 4");
    this->m_Data[0] = x;
    this->m_Data[1] = y;
    this->m_Data[2] = z;
    this->m_Data[3] = w;
}

template<typename T, int N>
Vector<T, N>::Vector(T data[N])
{
    for (int i = 0; i < N; ++i)
        this->m_Data[i] = data[i];
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator+() const
{
    return *this;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator-() const
{
    using namespace tsimd;
    T data[4];
    store(load<pack<T, 4>>(this->m_Data) * -1, data);
    return data;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator+(const Vector& b) const
{
    using namespace tsimd;
    T data[4];
    store(load<pack<T, 4>>(this->m_Data) + load<pack<T, 4>>(b.m_Data), data);
    return data;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator-(const Vector& b) const
{
    using namespace tsimd;
    T data[4];
    store(load<pack<T, 4>>(this->m_Data) - load<pack<T, 4>>(b.m_Data), data);
    return data;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator*(const Vector& b) const
{
    using namespace tsimd;
    T data[4];
    store(load<pack<T, 4>>(this->m_Data) * load<pack<T, 4>>(b.m_Data), data);
    return data;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator/(const Vector& b) const
{
    using namespace tsimd;
    T data[4];
    store(load<pack<T, 4>>(this->m_Data) / load<pack<T, 4>>(b.m_Data), data);
    this->RemoveNans(data);
    return data;
}

template<typename T, int N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector& b)
{
    using namespace tsimd;
    store(load<pack<T, 4>>(this->m_Data) + load<pack<T, 4>>(b.m_Data), this->m_Data);
    return *this;
}

template<typename T, int N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector& b)
{
    using namespace tsimd;
    store(load<pack<T, 4>>(this->m_Data) - load<pack<T, 4>>(b.m_Data), this->m_Data);
    return *this;
}

template<typename T, int N>
Vector<T, N>& Vector<T, N>::operator*=(const Vector& b)
{
    using namespace tsimd;
    store(load<pack<T, 4>>(this->m_Data) * load<pack<T, 4>>(b.m_Data), this->m_Data);
    return *this;
}

template<typename T, int N>
Vector<T, N>& Vector<T, N>::operator/=(const Vector& b)
{
    using namespace tsimd;
    store(load<pack<T, 4>>(this->m_Data) / load<pack<T, 4>>(b.m_Data), this->m_Data);
    this->RemoveNans();
    return *this;
}

template<typename T, int N>
bool Vector<T, N>::operator==(const Vector& b) const
{
    using namespace tsimd;

    if constexpr (std::is_floating_point_v<T>)
        return all(near_equal(load<pack<T, 4>>(this->m_Data), load<pack<T, 4>>(b.m_Data)));
    else
        return all(load<pack<T, 4>>(this->m_Data) == load<pack<T, 4>>(b.m_Data));
}

template<typename T, int N>
bool Vector<T, N>::operator!=(const Vector& b) const
{
    return !(*this == b);
}

template<typename T, int N>
double Vector<T, N>::Magnitude() const
{
    return sqrt(Dot(*this, *this));
}

template<typename T, int N>
T Vector<T, N>::SquareMagnitude() const
{
    return Dot(*this, *this);
}

template<typename T, int N>
T Vector<T, N>::Dot(const Vector& a, const Vector& b)
{
    using namespace tsimd;
    T dot = 0;
    pack<T, 4> axb = load<pack<T, 4>>(a.m_Data) * load<pack<T, 4>>(b.m_Data);
    for (int i = 0; i < N; ++i) dot += axb[i];
    return dot;
}

template<typename T, int N>
T Vector<T, N>::AbsDot(const Vector& a, const Vector& b)
{
    return fabs(Dot(a, b));
}

template<typename T, int N>
void Vector<T, N>::Normalize()
{
    using namespace tsimd;
    store(load<pack<T, 4>>(this->m_Data) / Magnitude(), this->m_Data);
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::Normalized() const
{
    return *this * (1.0 / Magnitude());
}

template<typename T, int N>
double Vector<T, N>::Angle(const Vector& a, const Vector& b)
{
    return acos(std::clamp(CosAngle(a, b), -1.0, 1.0));
}

template<typename T, int N>
double Vector<T, N>::CosAngle(const Vector& a, const Vector& b)
{
    return Dot(a, b) / (a.Magnitude() * b.Magnitude());
}

template<typename T, int N>
Vector<T, 3> Vector<T, N>::Cross(const Vector& a, const Vector& b)
{
    static_assert(N == 3, "Cross product only available for 3 dimensional vectors");
    using namespace tsimd;
    T data[4];
    pack<T, 4> tmp0 = pack<T, 4>(a[1], a[2], a[0], 0) * load<pack<T, 4>>(b.m_Data);
    pack<T, 4> tmp1 = pack<T, 4>(b[1], b[2], b[0], 0) * load<pack<T, 4>>(a.m_Data);
    store(tmp1 - tmp0, data);
    return { data[1], data[2], data[0] };
}

