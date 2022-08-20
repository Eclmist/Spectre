/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
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

#include <cmath>

namespace Math
{
	const double E        = 2.71828182845904523536;     // e
	const double Pi       = 3.14159265358979323846;     // pi
	const double PiOver2  = 1.57079632679489661923;     // pi/2
	const double PiOver4  = 0.785398163397448309616;    // pi/4
	const double InvPi    = 0.318309886183790671538;    // 1/pi
	const double Inv2Pi   = 0.636619772367581343076;    // 2/pi

    const double Epsilon  = 0.00000000000001;

	inline double DegToRad(double deg)
    {
        return deg * (Pi / 180);
	}

	inline double RadToDeg(double rad)
    {
        return rad * (180.0 / Pi);
	}
}

#include "vector.h"
#include "matrix.h"
#include "rect.h"
#include "random.h"

