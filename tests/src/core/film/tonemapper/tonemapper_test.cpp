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
#include "core/film/tonemapper/tonemapper.h"

class TonemapperStub : public Tonemapper
{
public:
    RgbCoefficients ApplyTonemap(const RgbCoefficients& linearSpaceColor) override { return {}; }
};

TEST(TonemapperTest, CanApplyGammaCorrection)
{
    TonemapperStub stub;
    RgbCoefficients col = 0.5;

    EXPECT_DOUBLE_EQ(stub.ApplyGammaCorrection(col)[0], std::pow(col[0], 1.0 / 2.2));
    EXPECT_DOUBLE_EQ(stub.ApplyGammaCorrection(col)[1], std::pow(col[1], 1.0 / 2.2));
    EXPECT_DOUBLE_EQ(stub.ApplyGammaCorrection(col)[2], std::pow(col[2], 1.0 / 2.2));

    EXPECT_DOUBLE_EQ(stub.ApplyGammaCorrection(col, 2.0)[0], std::sqrt(col[0]));
    EXPECT_DOUBLE_EQ(stub.ApplyGammaCorrection(col, 2.0)[1], std::sqrt(col[1]));
    EXPECT_DOUBLE_EQ(stub.ApplyGammaCorrection(col, 2.0)[2], std::sqrt(col[2]));
}

