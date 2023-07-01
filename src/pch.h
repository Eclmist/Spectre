/*
    This file is part of Spectre, an open-source physically based
    renderer.

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

#include <algorithm>
#include <assert.h>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "smath/include/smath.h"

#include "system/platform/platformutils.h"

#include "core/spectrum/spectralcoefficients.h"
#include "core/spectrum/reflectantspectrum.h"
#include "core/spectrum/illuminantspectrum.h"

typedef SMath::Vector<double, 2>    Vector2;
typedef SMath::Vector<double, 3>    Vector3;
typedef SMath::Vector<double, 4>    Vector4;
typedef SMath::Vector<int, 2>       Vector2i;
typedef SMath::Vector<int, 3>       Vector3i;
typedef SMath::Vector<int, 4>       Vector4i;
typedef SMath::Point<double, 2>     Point2;
typedef SMath::Point<double, 3>     Point3;
typedef SMath::Point<double, 4>     Point4;
typedef SMath::Point<int, 2>        Point2i;
typedef SMath::Point<int, 3>        Point3i;
typedef SMath::Point<int, 4>        Point4i;
typedef SMath::Normal<double, 3>    Normal3;
typedef SMath::Matrix<double, 3>    Matrix3x3;
typedef SMath::Matrix<double, 4>    Matrix4x4;
typedef SMath::Matrix<int, 3>       Matrix3x3i;
typedef SMath::Matrix<int, 4>       Matrix4x4i;

typedef SMath::Ray<double>          Ray;
typedef SMath::Transform<double>    Transform;
typedef SMath::Box<double>          BoundingBox;
