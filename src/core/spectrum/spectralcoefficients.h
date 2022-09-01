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

struct SpectralCoefficients
{
    SpectralCoefficients(double v = 0)
    {
        m_Data[0] = v;
        m_Data[1] = v;
        m_Data[2] = v;
    }

    SpectralCoefficients(double r, double g, double b) {
        m_Data[0] = r;
        m_Data[1] = g;
        m_Data[2] = b;
    }

    inline double operator[](int i) const { return m_Data[i]; }
    inline double& operator[](int i) { return m_Data[i]; }

    inline SpectralCoefficients operator+(const SpectralCoefficients& v) const { return { m_Data[0] + v[0], m_Data[1] + v[1], m_Data[2] + v[2] }; }
    inline SpectralCoefficients operator-(const SpectralCoefficients& v) const { return { m_Data[0] - v[0], m_Data[1] - v[1], m_Data[2] - v[2] }; }
    inline SpectralCoefficients operator*(const SpectralCoefficients& v) const { return { m_Data[0] * v[0], m_Data[1] * v[1], m_Data[2] * v[2] }; }
    inline SpectralCoefficients operator/(const SpectralCoefficients& v) const { return { m_Data[0] / v[0], m_Data[1] / v[1], m_Data[2] / v[2] }; }

    inline void operator+=(const SpectralCoefficients& v) { m_Data[0] += v.m_Data[0]; m_Data[1] += v.m_Data[1]; m_Data[2] += v.m_Data[2]; }
    inline void operator-=(const SpectralCoefficients& v) { m_Data[0] -= v.m_Data[0]; m_Data[1] -= v.m_Data[1]; m_Data[2] -= v.m_Data[2]; }
    inline void operator*=(const SpectralCoefficients& v) { m_Data[0] *= v.m_Data[0]; m_Data[1] *= v.m_Data[1]; m_Data[2] *= v.m_Data[2]; }
    inline void operator/=(const SpectralCoefficients& v) { m_Data[0] /= v.m_Data[0]; m_Data[1] /= v.m_Data[1]; m_Data[2] /= v.m_Data[2]; }

    double m_Data[3];
};

typedef SpectralCoefficients RgbCoefficients;
typedef SpectralCoefficients XyzCoefficients;

