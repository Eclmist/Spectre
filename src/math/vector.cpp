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

#include "vector.h"

Vector4::Vector4()
    : x(0)
    , y(0)
    , z(0)
    , w(0)
{
}

Vector4::Vector4(double v)
    : x(v)
    , y(v)
    , z(v)
    , w(v)
{
}

Vector4::Vector4(double _x, double _y, double _z, double _w)
    : x(_x)
    , y(_y)
    , z(_z)
    , w(_w)
{
}
