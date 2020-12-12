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

#include "googletest/gtest.h"
#include "core/spectrum/sampledspectrum.h"

TEST(SampledSpectrumTest, CanBeCreated)
{
    double wavelength[] = { 400, 410, 420, 430, 440 };
    double v[] = { 0.1, 0.1, 0.1, 0.1, 0.1 };
    ASSERT_NO_THROW(SampledSpectrum(wavelength, v, 5));

    double l[] = { 400, 410, 420, 430, 440 };
    double u[] = { 0.2, 0.3, 0.4, 0.5, 0.6 };
    ASSERT_NO_THROW(SampledSpectrum(l, u, 5));

    double s[] = { 400, 410, 420, 430, 440, 500, 600, 650, 700 };
    double t[] = { 0.2, 0.3, 0.4, 0.5, 0.6, 0.3, 0.2, 0.5, 0.9 };
    ASSERT_NO_THROW(SampledSpectrum(s, t, 9));
}

TEST(SampledSpectrumTest, InvalidInputsDefaultToBlack)
{
    double unsortedWavelength[] = { 400, 420, 410, 430, 440 };
    double v[] = { 0.1, 0.1, 0.1, 0.1, 0.1 };
    EXPECT_TRUE(SampledSpectrum(unsortedWavelength, v, 5).IsBlack());
}

TEST(SampledSpectrumTest, CanComputeWavelengthRange)
{
    SampledSpectrum s;

    double rangeStart;
    double rangeEnd;
    double binSize = (END_WAVELENGTH - START_WAVELENGTH) / double(NUM_SPECTRUM_SAMPLES - 1);

    s.ComputeWavelengthRange(0, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, START_WAVELENGTH - (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, START_WAVELENGTH + (binSize / 2));

    s.ComputeWavelengthRange(1, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, START_WAVELENGTH + (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, START_WAVELENGTH + (binSize / 2) + binSize);

    s.ComputeWavelengthRange(NUM_SPECTRUM_SAMPLES - 1, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, END_WAVELENGTH - (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, END_WAVELENGTH + (binSize / 2));
}

TEST(SampledSpectrumTest, CanComputeAreaSum)
{
    SampledSpectrum s;
    double wavelength[] = { 400, 410, 420, 430, 440 };
    double v[] = { 1, 2, 5, 3, 8 };

    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(wavelength, v, 5, 400, 410), 15);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(wavelength, v, 5, 390, 410), 25);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(wavelength, v, 5, 405, 410), 1.75 * 5);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(wavelength, v, 5, 410, 430), 75);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(wavelength, v, 5, 430, 440), 55);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(wavelength, v, 5, 435, 445), 40 + 6.75 * 5);
}

TEST(SampledSpectrumTest, CanComputeAverageSamples)
{
    double s[] = { 400, 410, 420, 430, 440, 500, 600, 650, 700 };
    double t[] = { 0.2, 0.3, 0.4, 0.5, 0.6, 0.3, 0.2, 0.5, 0.9 };
    SampledSpectrum a;

    EXPECT_DOUBLE_EQ(a.ComputeAverageSamples(s, t, 9, 300, 400), 0.2);
    EXPECT_DOUBLE_EQ(a.ComputeAverageSamples(s, t, 9, 400, 410), 0.25);
    EXPECT_DOUBLE_EQ(a.ComputeAverageSamples(s, t, 9, 400, 420), 0.3);
    EXPECT_DOUBLE_EQ(a.ComputeAverageSamples(s, t, 9, 415, 425), 0.4);
    EXPECT_DOUBLE_EQ(a.ComputeAverageSamples(s, t, 9, 440, 500), 0.45);
    EXPECT_DOUBLE_EQ(a.ComputeAverageSamples(s, t, 9, 700, 800), 0.9);
}
