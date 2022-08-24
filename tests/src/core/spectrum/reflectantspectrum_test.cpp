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

#include "gtest.h"
#include "core/spectrum/reflectantspectrum.h"

TEST(ReflectantSpectrumTest, CanBeCreated)
{
    ASSERT_NO_THROW(ReflectantSpectrum({ 0.2, 0.3, 0.4 }));
}

TEST(ReflectantSpectrumTest, HasCorrectValues)
{
    ReflectantSpectrum white({ 1, 1, 1 });
    RgbCoefficients rgb = white.ToRgb();
    static const double tolerance = 0.15;
    EXPECT_LT(abs(rgb[0] - 1.205), tolerance);
    EXPECT_LT(abs(rgb[1] - 0.94), tolerance);
    EXPECT_LT(abs(rgb[2] - 0.909), tolerance);
}

