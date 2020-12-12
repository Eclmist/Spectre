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
    SampleArray samples = { {400, 0.1}, {410, 0.1}, {420, 0.1}, {430, 0.1}, {440, 0.1} };
    ASSERT_NO_THROW(SampledSpectrum s1(samples));

    samples = { {400, 0.2}, {410, 0.3}, {420, 0.4}, {430, 0.5}, {440, 0.6} };
    ASSERT_NO_THROW(SampledSpectrum s2(samples));

    samples = { {400, 0.2}, {410, 0.3}, {420, 0.4}, {430, 0.5}, {440, 0.6}, {500, 0.3}, {600, 0.2}, {650, 0.5}, {700, 0.9} };
    ASSERT_NO_THROW(SampledSpectrum s3(samples));
}

TEST(SampledSpectrumTest, InvalidInputsDefaultToBlack)
{
    SampleArray unsortedSamples = { {400, 0.1}, {420, 0.1}, {410, 0.1}, {430, 0.1}, {440, 0.1} };
    SampledSpectrum s1(unsortedSamples);
    EXPECT_TRUE(s1.IsBlack());
}

TEST(SampledSpectrumTest, CanComputeWavelengthRange)
{
    SampledSpectrum s;

    double rangeStart;
    double rangeEnd;
    double binSize = (END_WAVELENGTH - START_WAVELENGTH) / double(NUM_SPECTRUM_SAMPLES - 1);

    s.ComputeRangeAtIndex(0, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, START_WAVELENGTH - (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, START_WAVELENGTH + (binSize / 2));

    s.ComputeRangeAtIndex(1, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, START_WAVELENGTH + (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, START_WAVELENGTH + (binSize / 2) + binSize);

    s.ComputeRangeAtIndex(NUM_SPECTRUM_SAMPLES - 1, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, END_WAVELENGTH - (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, END_WAVELENGTH + (binSize / 2));
}

TEST(SampledSpectrumTest, CanComputeAreaSum)
{
    SampledSpectrum s;
    SampleArray samples = { {400, 1}, {410, 2}, {420, 5}, {430, 3}, {440, 8} };

    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(samples, 400, 410), 15);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(samples, 390, 410), 25);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(samples, 405, 410), 1.75 * 5);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(samples, 410, 430), 75);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(samples, 430, 440), 55);
    EXPECT_DOUBLE_EQ(s.ComputeAreaSum(samples, 435, 445), 40 + 6.75 * 5);
}

TEST(SampledSpectrumTest, CanComputeAverageSamples)
{
    SampledSpectrum a;
    SampleArray samples = { {400, 0.2}, {410, 0.3}, {420, 0.4}, {430, 0.5}, {440, 0.6}, {500, 0.3}, {600, 0.2}, {650, 0.5}, {700, 0.9} };

    EXPECT_DOUBLE_EQ(a.ComputeAverageInRange(samples, 300, 400), 0.2);
    EXPECT_DOUBLE_EQ(a.ComputeAverageInRange(samples, 400, 410), 0.25);
    EXPECT_DOUBLE_EQ(a.ComputeAverageInRange(samples, 400, 420), 0.3);
    EXPECT_DOUBLE_EQ(a.ComputeAverageInRange(samples, 415, 425), 0.4);
    EXPECT_DOUBLE_EQ(a.ComputeAverageInRange(samples, 440, 500), 0.45);
    EXPECT_DOUBLE_EQ(a.ComputeAverageInRange(samples, 700, 800), 0.9);
}

