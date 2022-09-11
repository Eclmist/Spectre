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

#include "system/platform/platformutils.h"

#include <cmath>
#include "math/constants.h"
#include "math/mathutils.h"
#include "math/linalg.h"
#include "math/transform.h"
#include "math/ray.h"
#include "math/rect.h"
#include "math/random.h"

#include "core/spectrum/spectralcoefficients.h"
#include "core/spectrum/reflectantspectrum.h"
#include "core/spectrum/illuminantspectrum.h"

