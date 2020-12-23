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
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

struct Coefficients
{
    Coefficients(double r = 0, double g = 0, double b = 0)
    {
        m_Data[0] = r;
        m_Data[1] = g;
        m_Data[2] = b;
    }

    inline double operator[](int i) const { return m_Data[i]; }
    inline double& operator[](int i) { return m_Data[i]; }

    inline Coefficients operator*(double scale) const { return { m_Data[0] * scale, m_Data[1] * scale, m_Data[2] * scale }; }
    inline Coefficients operator/(double div) const { return { m_Data[0] / div, m_Data[1] / div, m_Data[2] / div }; }

    inline void operator+=(const Coefficients& v) { m_Data[0] += v.m_Data[0]; m_Data[1] += v.m_Data[1]; m_Data[2] += v.m_Data[2]; }
    inline void operator-=(const Coefficients& v) { m_Data[0] -= v.m_Data[0]; m_Data[1] -= v.m_Data[1]; m_Data[2] -= v.m_Data[2]; }
    inline void operator*=(double scale) { m_Data[0] *= scale; m_Data[1] *= scale; m_Data[2] *= scale; }
    inline void operator/=(double scale) { m_Data[0] /= scale; m_Data[1] /= scale; m_Data[2] /= scale; }

    double m_Data[3];
};

typedef Coefficients RGBCoefficients;
typedef Coefficients XYZCoefficients;

