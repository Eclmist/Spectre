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

#include "sampledspectrum.h"
#include "spectralconstants.h"

const SampledSpectrum SampledSpectrum::cieX = SampledSpectrum::FromSortedRawSamples(cieLambda, cieSamplesX, numCieSamples);
const SampledSpectrum SampledSpectrum::cieY = SampledSpectrum::FromSortedRawSamples(cieLambda, cieSamplesY, numCieSamples);
const SampledSpectrum SampledSpectrum::cieZ = SampledSpectrum::FromSortedRawSamples(cieLambda, cieSamplesZ, numCieSamples);

const SampledSpectrum SampledSpectrum::stdReflW = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesW, numStdSamples);
const SampledSpectrum SampledSpectrum::stdReflC = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesC, numStdSamples);
const SampledSpectrum SampledSpectrum::stdReflM = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesM, numStdSamples);
const SampledSpectrum SampledSpectrum::stdReflY = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesY, numStdSamples);
const SampledSpectrum SampledSpectrum::stdReflR = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesR, numStdSamples);
const SampledSpectrum SampledSpectrum::stdReflG = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesG, numStdSamples);
const SampledSpectrum SampledSpectrum::stdReflB = SampledSpectrum::FromSortedRawSamples(stdLambda, stdReflSamplesB, numStdSamples);

const SampledSpectrum SampledSpectrum::stdIllumW = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesW, numStdSamples);
const SampledSpectrum SampledSpectrum::stdIllumC = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesC, numStdSamples);
const SampledSpectrum SampledSpectrum::stdIllumM = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesM, numStdSamples);
const SampledSpectrum SampledSpectrum::stdIllumY = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesY, numStdSamples);
const SampledSpectrum SampledSpectrum::stdIllumR = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesR, numStdSamples);
const SampledSpectrum SampledSpectrum::stdIllumG = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesG, numStdSamples);
const SampledSpectrum SampledSpectrum::stdIllumB = SampledSpectrum::FromSortedRawSamples(stdLambda, stdIllumSamplesB, numStdSamples);

SampledSpectrum::SampledSpectrum(const std::vector<SpectralSample>& samples)
{
    if (IsSamplesSorted(samples))
    {
        for (int i = 0; i < numSpectralSamples; ++i)
        {
            double startLambda, endLambda;
            ComputeRangeAtIndex(i, startLambda, endLambda);
            m_Coefficients[i] = ComputeAverageInRange(samples, startLambda, endLambda);
        }
    }
}

SampledSpectrum SampledSpectrum::FromSortedRawSamples(const double* lambda, const double* power, int numSamples)
{
    SampleArray sampleArray(numSamples);

    for (int i = 0; i < numSamples; ++i)
        sampleArray[i] = { lambda[i], power[i] };

    return sampleArray;
}

RgbCoefficients SampledSpectrum::XyzToRgb(const XyzCoefficients& xyz)
{
    RgbCoefficients rgb;
    rgb[0] = 3.240479 * xyz[0] - 1.537150 * xyz[1] - 0.498535 * xyz[2];
    rgb[1] =-0.969256 * xyz[0] + 1.875991 * xyz[1] + 0.041556 * xyz[2];
    rgb[2] = 0.055648 * xyz[0] - 0.204043 * xyz[1] + 1.057311 * xyz[2];
    return rgb;
}

XyzCoefficients SampledSpectrum::RgbToXyz(const RgbCoefficients& rgb)
{
    XyzCoefficients xyz;
    xyz[0] = 0.412453 * rgb[0] + 0.357580 * rgb[1] + 0.180423 * rgb[2];
    xyz[1] = 0.212671 * rgb[0] + 0.715160 * rgb[1] + 0.072169 * rgb[2];
    xyz[2] = 0.019334 * rgb[0] + 0.119193 * rgb[1] + 0.950227 * rgb[2];
    return xyz;
}

XyzCoefficients SampledSpectrum::ToXyz() const
{
    XyzCoefficients result;
    for (int i = 0; i < numSpectralSamples; ++i)
    {
        result[0] += cieX.m_Coefficients[i] * m_Coefficients[i];
        result[1] += cieY.m_Coefficients[i] * m_Coefficients[i];
        result[2] += cieZ.m_Coefficients[i] * m_Coefficients[i];
    }

    return result * GetXyzNormalizationConstant();
}

RgbCoefficients SampledSpectrum::ToRgb() const
{
    XyzCoefficients xyz = ToXyz();
    return XyzToRgb(xyz);
}

bool SampledSpectrum::IsSamplesSorted(const SampleArray& samples) const
{
    if (samples.size() <= 1)
        return true;

    for (int i = 0; i + 1 < samples.size(); ++i)
        if (samples[i].m_Wavelength > samples[i + 1].m_Wavelength)
            return false;
            
    return true;
}

bool SampledSpectrum::IsInputOutsideLeftBoundary(const SampleArray& samples, double leftBound) const
{
    return samples.back().m_Wavelength <= leftBound;
}

bool SampledSpectrum::IsInputOutsideRightBoundary(const SampleArray& samples, double rightBound) const
{
    return samples.front().m_Wavelength >= rightBound;
}

void SampledSpectrum::ComputeRangeAtIndex(int index, double& start, double& end) const
{
    double binWidth = (MaxWavelength - MinWavelength) / double(numSpectralSamples - 1);
    double halfBinWidth = binWidth / 2.0;
    start = MinWavelength + (index * binWidth) - halfBinWidth;
    end = MinWavelength + (index * binWidth) + halfBinWidth;
}

double SampledSpectrum::ComputeBoundaryArea(const SampleArray& samples, double leftBound, double rightBound) const
{
    double leftBoundaryRange = std::max<double>(0.0, samples.front().m_Wavelength - leftBound);
    double rightBoundRange = std::max<double>(0.0, rightBound - samples.back().m_Wavelength);
    double leftBoundArea = samples.front().m_Power * leftBoundaryRange;
    double rightBoundArea = samples.back().m_Power * rightBoundRange;

    return leftBoundArea + rightBoundArea;
}

double SampledSpectrum::ComputeSegmentArea(const SpectralSample& s1, const SpectralSample& s2, double leftBound, double rightBound) const
{
    double sampleRangeL = s1.m_Wavelength;
    double sampleRangeR = s2.m_Wavelength;

    if (sampleRangeL < leftBound)
        sampleRangeL = leftBound;

    if (sampleRangeR > rightBound)
        sampleRangeR = rightBound;

    double unclampedRange = s2.m_Wavelength - s1.m_Wavelength;
    double clampedRange = sampleRangeR - sampleRangeL;

    double lerpFactorL = (sampleRangeL - s1.m_Wavelength) / unclampedRange;
    double lerpFactorR = (sampleRangeR - s1.m_Wavelength) / unclampedRange;

    double powerL = std::lerp(s1.m_Power, s2.m_Power, lerpFactorL);
    double powerR = std::lerp(s1.m_Power, s2.m_Power, lerpFactorR);
    return ((powerL + powerR) / 2) * clampedRange;
}

double SampledSpectrum::ComputeAreaSum(const SampleArray& samples, double leftBound, double rightBound) const
{
    double sum = 0;
    int i = 0;
    while (samples[i + 1].m_Wavelength < leftBound) ++i;

    for (; i + 1 < samples.size(); ++i)
    {
        if (samples[i].m_Wavelength > rightBound)
            break;

        sum +=  ComputeSegmentArea(samples[i], samples[i + 1], leftBound, rightBound);
    }

    sum += ComputeBoundaryArea(samples, leftBound, rightBound);
    return sum;
}

double SampledSpectrum::ComputeAverageInRange(const SampleArray& samples, double leftBound, double rightBound) const
{
    if (samples.size() == 1)
        return samples.front().m_Power;

    if (IsInputOutsideRightBoundary(samples, rightBound))
        return samples.front().m_Power;

    if (IsInputOutsideLeftBoundary(samples, leftBound))
        return samples.back().m_Power;

    double sum = ComputeAreaSum(samples, leftBound, rightBound);
    double range = rightBound - leftBound;
    return sum / range;
}

double SampledSpectrum::GetXyzNormalizationConstant() const
{
    double scale = (MaxWavelength - MinWavelength + 1) / double(numSpectralSamples);
    return scale / cieIntegralY;
}

