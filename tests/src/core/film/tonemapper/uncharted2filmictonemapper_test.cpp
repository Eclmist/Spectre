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
#include "core/film/tonemapper/uncharted2filmictonemapper.h"

TEST(Uncharted2FilmicTonemapperTest, FilmicCurveValues0To1)
{
    double a = 0.0;
    double b = 0.5;
    double c = 1.0;

    double d = -0.001;
    double e = 999999999;

    Uncharted2FilmicTonemapper tonemapper;

    EXPECT_LE(tonemapper.FilmicCurve(a)[0], 1.0);
    EXPECT_LE(tonemapper.FilmicCurve(a)[1], 1.0);
    EXPECT_LE(tonemapper.FilmicCurve(a)[2], 1.0);
    EXPECT_GE(tonemapper.FilmicCurve(a)[0], 0.0);
    EXPECT_GE(tonemapper.FilmicCurve(a)[1], 0.0);
    EXPECT_GE(tonemapper.FilmicCurve(a)[2], 0.0);

    EXPECT_LE(tonemapper.FilmicCurve(b)[0], 1.0);
    EXPECT_LE(tonemapper.FilmicCurve(b)[1], 1.0);
    EXPECT_LE(tonemapper.FilmicCurve(b)[2], 1.0);
    EXPECT_GE(tonemapper.FilmicCurve(b)[0], 0.0);
    EXPECT_GE(tonemapper.FilmicCurve(b)[1], 0.0);
    EXPECT_GE(tonemapper.FilmicCurve(b)[2], 0.0);

    EXPECT_LE(tonemapper.FilmicCurve(c)[0], 1.0);
    EXPECT_LE(tonemapper.FilmicCurve(c)[1], 1.0);
    EXPECT_LE(tonemapper.FilmicCurve(c)[2], 1.0);
    EXPECT_GE(tonemapper.FilmicCurve(c)[0], 0.0);
    EXPECT_GE(tonemapper.FilmicCurve(c)[1], 0.0);
    EXPECT_GE(tonemapper.FilmicCurve(c)[2], 0.0);

    EXPECT_LT(tonemapper.FilmicCurve(d)[0], 0.0);
    EXPECT_LT(tonemapper.FilmicCurve(d)[1], 0.0);
    EXPECT_LT(tonemapper.FilmicCurve(d)[2], 0.0);
    EXPECT_LT(tonemapper.FilmicCurve(e)[0], 1.0);
    EXPECT_LT(tonemapper.FilmicCurve(e)[1], 1.0);
    EXPECT_LT(tonemapper.FilmicCurve(e)[2], 1.0);

}

TEST(Uncharted2FilmicTonemapperTest, Values0To1AfterTonemapping)
{

    double whitePoint = 20;
    double gamma = 2.2;
    double gammaCorrectedWhitePoint = std::pow(whitePoint, 2.2);

    double a = 0.0;
    double d = -0.001;
    double e = whitePoint;
    double f = whitePoint + 0.001;

    Uncharted2FilmicTonemapper tonemapper(20);

    EXPECT_LE(tonemapper.ApplyTonemap(a)[0], 1.0);
    EXPECT_LE(tonemapper.ApplyTonemap(a)[1], 1.0);
    EXPECT_LE(tonemapper.ApplyTonemap(a)[2], 1.0);
    EXPECT_GE(tonemapper.ApplyTonemap(a)[0], 0.0);
    EXPECT_GE(tonemapper.ApplyTonemap(a)[1], 0.0);
    EXPECT_GE(tonemapper.ApplyTonemap(a)[2], 0.0);

    EXPECT_TRUE(std::isnan(tonemapper.ApplyTonemap(d)[0]));
    EXPECT_TRUE(std::isnan(tonemapper.ApplyTonemap(d)[1]));
    EXPECT_TRUE(std::isnan(tonemapper.ApplyTonemap(d)[2]));

    EXPECT_GT(tonemapper.ApplyTonemap(f)[0], 1.0);
    EXPECT_GT(tonemapper.ApplyTonemap(f)[1], 1.0);
    EXPECT_GT(tonemapper.ApplyTonemap(f)[2], 1.0);

    EXPECT_DOUBLE_EQ(tonemapper.ApplyTonemap(e)[0], 1.0);
    EXPECT_DOUBLE_EQ(tonemapper.ApplyTonemap(e)[1], 1.0);
    EXPECT_DOUBLE_EQ(tonemapper.ApplyTonemap(e)[2], 1.0);
}



