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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest.h"
#include "core/spectrum/spectrum.h"


TEST(SpectrumTest, CanBeCreated)
{
    ASSERT_NO_THROW(Spectrum spectrum);
}

TEST(SpectrumTest, CanCheckIfBlack)
{
    EXPECT_TRUE(Spectrum(0).IsBlack());
    EXPECT_FALSE(Spectrum(0.001).IsBlack());
    EXPECT_FALSE(Spectrum(-0.001).IsBlack());
}

TEST(SpectrumTest, CanCheckHasNans)
{
    EXPECT_TRUE(Spectrum(std::numeric_limits<double>::quiet_NaN()).HasNans());
    EXPECT_FALSE(Spectrum().HasNans());
    EXPECT_FALSE(Spectrum(0).HasNans());
    EXPECT_FALSE(Spectrum(0.001).HasNans());
    EXPECT_FALSE(Spectrum(-0.001).HasNans());
}

TEST(SpectrumTest, DefaultsToBlack)
{
    EXPECT_TRUE(Spectrum().IsBlack());
}

TEST(SpectrumTest, CanCheckEquality)
{
    EXPECT_EQ(Spectrum(), Spectrum());
    EXPECT_EQ(Spectrum(0), Spectrum(0));
    EXPECT_EQ(Spectrum(1), Spectrum(1));
    EXPECT_EQ(Spectrum(-1), Spectrum(-1));
    EXPECT_NE(Spectrum(1), Spectrum(-1));
    EXPECT_NE(Spectrum(0), Spectrum(1));
}

TEST(SpectrumTest, CanBeAdded)
{
    EXPECT_EQ(Spectrum(0) + Spectrum(1), Spectrum(1));
    EXPECT_EQ(Spectrum(1) + Spectrum(1), Spectrum(2));
}

TEST(SpectrumTest, CanBeAddAssigned)
{
    Spectrum a;
    Spectrum b(1);
    a += b;
    EXPECT_EQ(a, b);
    a += 1;
    EXPECT_EQ(a, Spectrum(2));
}

TEST(SpectrumTest, CanBeSubtracted)
{
    EXPECT_EQ(Spectrum(0) - Spectrum(1), Spectrum(-1));
    EXPECT_EQ(Spectrum(1) - Spectrum(1), Spectrum(0));
}

TEST(SpectrumTest, CanBeSubtractAssigned)
{
    Spectrum a;
    Spectrum b(1);
    a -= b;
    EXPECT_EQ(a, Spectrum(-1));
    a -= 1;
    EXPECT_EQ(a, Spectrum(-2));
}

TEST(SpectrumTest, CanBeMultiplied)
{
    EXPECT_EQ(Spectrum(0) * Spectrum(1), Spectrum(0));
    EXPECT_EQ(Spectrum(1) * Spectrum(1), Spectrum(1));
}

TEST(SpectrumTest, CanBeMultiplyAssigned)
{
    Spectrum a(2);
    Spectrum b(3);
    a *= b;
    EXPECT_EQ(a, Spectrum(6));
    a *= 3;
    EXPECT_EQ(a, Spectrum(18));
}

TEST(SpectrumTest, CanBeDivided)
{
    EXPECT_EQ(Spectrum(0) / Spectrum(1), Spectrum(0));
    EXPECT_EQ(Spectrum(1) / Spectrum(1), Spectrum(1));
    EXPECT_EQ(Spectrum(32) / Spectrum(2), Spectrum(16));
}

TEST(SpectrumTest, CanBeDivideAssigned)
{
    Spectrum a(32);
    Spectrum b(2);
    a /= b;
    EXPECT_EQ(a, Spectrum(16));
    a /= 2;
    EXPECT_EQ(a, Spectrum(8));
}

TEST(SpectrumTest, CanComputeSqrt)
{
    EXPECT_EQ(Spectrum::Sqrt(0), Spectrum(0));
    EXPECT_EQ(Spectrum::Sqrt(4), Spectrum(2));
    EXPECT_EQ(Spectrum::Sqrt(16), Spectrum(4));
}

TEST(SpectrumTest, CanComputePow)
{
    EXPECT_EQ(Spectrum::Pow(1, 0), Spectrum(1));
    EXPECT_EQ(Spectrum::Pow(4, 2), Spectrum(16));
    EXPECT_EQ(Spectrum::Pow(2, 2), Spectrum(4));
}

TEST(SpectrumTest, CanLerp)
{
    EXPECT_EQ(Spectrum::Lerp(0, 2, 0.5), Spectrum(1));
    EXPECT_EQ(Spectrum::Lerp(0, 1, 0), Spectrum(0));
    EXPECT_EQ(Spectrum::Lerp(0, 1, 1), Spectrum(1));
}

TEST(SpectrumTest, CanBeClamped)
{
    EXPECT_EQ(Spectrum::Clamp(5, 0, 5), Spectrum(5));
    EXPECT_EQ(Spectrum::Clamp(0, 0, 1), Spectrum(0));
    EXPECT_EQ(Spectrum::Clamp(-0.01, 0, 1), Spectrum(0));
    EXPECT_EQ(Spectrum::Clamp(5, 0, 1), Spectrum(1));
    EXPECT_EQ(Spectrum::Clamp(2.1, 0, 2), Spectrum(2));
}

TEST(SpectrumTest, CanComputeMin)
{
    EXPECT_EQ(Spectrum::Min(0, 1), Spectrum(0));
    EXPECT_EQ(Spectrum::Min(-1, 1), Spectrum(-1));
    EXPECT_EQ(Spectrum::Min(2, 1), Spectrum(1));
}

TEST(SpectrumTest, CanComputeMax)
{
    EXPECT_EQ(Spectrum::Max(0, 1), Spectrum(1));
    EXPECT_EQ(Spectrum::Max(-1, 1), Spectrum(1));
    EXPECT_EQ(Spectrum::Max(2, 1), Spectrum(2));
}

