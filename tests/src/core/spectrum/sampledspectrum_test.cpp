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

#include "gtest.h"
#include "core/spectrum/sampledspectrum.h"
#include "core/spectrum/spectralconstants.h"

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
    double binSize = (MaxWavelength - MinWavelength) / double(numSpectralSamples - 1);

    s.ComputeRangeAtIndex(0, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, MinWavelength - (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, MinWavelength + (binSize / 2));

    s.ComputeRangeAtIndex(1, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, MinWavelength + (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, MinWavelength + (binSize / 2) + binSize);

    s.ComputeRangeAtIndex(numSpectralSamples - 1, rangeStart, rangeEnd);
    EXPECT_DOUBLE_EQ(rangeStart, MaxWavelength - (binSize / 2));
    EXPECT_DOUBLE_EQ(rangeEnd, MaxWavelength + (binSize / 2));
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

TEST(SampledSpectrumTest, CanBeCreatedFromRawSamples)
{
    const double lambda[5] = { 100, 200, 300, 400, 500 };
    const double power[5] = { 10, 20, 30, 40, 50 };
    ASSERT_NO_THROW(SampledSpectrum::FromSortedRawSamples(lambda, power, 5));
    SampledSpectrum s = SampledSpectrum::FromSortedRawSamples(lambda, power, 5);
    EXPECT_EQ(s, SampledSpectrum({ {100, 10}, {200, 20}, {300, 30}, {400, 40}, {500, 50} }));
}

TEST(SampledSpectrumTest, CanPopulateStandardCurves)
{
    ASSERT_FALSE(SampledSpectrum::cieX.IsBlack());
    ASSERT_FALSE(SampledSpectrum::cieY.IsBlack());
    ASSERT_FALSE(SampledSpectrum::cieZ.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflW.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflC.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflM.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflY.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflR.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflG.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdReflB.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumW.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumC.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumM.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumY.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumR.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumG.IsBlack());
    ASSERT_FALSE(SampledSpectrum::stdIllumB.IsBlack());

    double xSum = 0, ySum = 0, zSum = 0;
    for (int i = 0; i < numCieSamples; ++i)
    {
        xSum += cieSamplesX[i];
        ySum += cieSamplesY[i];
        zSum += cieSamplesZ[i];
    }

    static const double tolerance = 0.01;

    EXPECT_LT(abs(1.0 - xSum / cieIntegralY), tolerance);
    EXPECT_LT(abs(1.0 - ySum / cieIntegralY), tolerance);
    EXPECT_LT(abs(1.0 - zSum / cieIntegralY), tolerance);
}

TEST(SampledSpectrumTest, CanConvertBetweenRgbandXyz)
{
    RgbCoefficients rgb(1.2, 3.4, 5.6);
    XyzCoefficients xyz = SampledSpectrum::RgbToXyz(rgb);
    RgbCoefficients rgb2 = SampledSpectrum::XyzToRgb(xyz);

    static const double tolerance = 0.0005;
    EXPECT_LT(abs(rgb[0] - rgb2[0]), tolerance);
    EXPECT_LT(abs(rgb[1] - rgb2[1]), tolerance);
    EXPECT_LT(abs(rgb[2] - rgb2[2]), tolerance);

    xyz = SampledSpectrum::RgbToXyz({1, 1, 1});
    EXPECT_LT(abs(xyz[0] - 0.950), tolerance);
    EXPECT_LT(abs(xyz[1] - 1.000), tolerance);
    EXPECT_LT(abs(xyz[2] - 1.089), tolerance);
}

TEST(SampledSpectrumTest, CanConvertToXyz)
{
    SampledSpectrum s(1.0);

    XyzCoefficients trueXyz;
    for (int i = 0; i < numCieSamples; ++i)
    {
        trueXyz[0] += cieSamplesX[i];
        trueXyz[1] += cieSamplesY[i];
        trueXyz[2] += cieSamplesZ[i];
    }
    trueXyz = trueXyz / cieIntegralY;
    static const double tolerance = 0.1;
    EXPECT_LT(abs(s.ToXyz()[0] - trueXyz[0]), tolerance);
    EXPECT_LT(abs(s.ToXyz()[1] - trueXyz[1]), tolerance);
    EXPECT_LT(abs(s.ToXyz()[2] - trueXyz[2]), tolerance);
}

TEST(SampledSpectrumTest, CanConvertToRgb)
{
    SampledSpectrum s(1.0);

    RgbCoefficients rgb = s.ToRgb();
    static const double tolerance = 0.1;
    EXPECT_LT(abs(rgb[0] - 1.205), tolerance);
    EXPECT_LT(abs(rgb[1] - 0.94), tolerance);
    EXPECT_LT(abs(rgb[2] - 0.909), tolerance);
}

