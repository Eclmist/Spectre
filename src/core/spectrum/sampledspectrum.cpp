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

#include "sampledspectrum.h"
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <vector>

#include "cieconstants.h"

SampledSpectrum SampledSpectrum::CIE_X;
SampledSpectrum SampledSpectrum::CIE_Y;
SampledSpectrum SampledSpectrum::CIE_Z;

SampledSpectrum::SampledSpectrum(const std::vector<Sample>& samples)
{
    if (IsSamplesSorted(samples))
    {
        for (int i = 0; i < NUM_SPECTRUM_SAMPLES; ++i)
        {
            double startLambda, endLambda;
            ComputeRangeAtIndex(i, startLambda, endLambda);
            m_Coefficients[i] = ComputeAverageInRange(samples, startLambda, endLambda);
        }
    }
}

void SampledSpectrum::Init()
{
    InitCieReferenceCurves();
}

void SampledSpectrum::InitCieReferenceCurves()
{
    CIE_X = FromRawSamples(CIE_X_Samples, CIE_Lambda, numCIESamples);
    CIE_Y = FromRawSamples(CIE_Y_Samples, CIE_Lambda, numCIESamples);
    CIE_Z = FromRawSamples(CIE_Z_Samples, CIE_Lambda, numCIESamples);
}

SampledSpectrum SampledSpectrum::FromRawSamples(const double* lambda, const double* power, int numSamples)
{
    SampleArray sampleArray(numSamples);

    for (int i = 0; i < numSamples; ++i)
        sampleArray[i] = { power[i], lambda[i] };

    return sampleArray;
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
    double binWidth = (END_WAVELENGTH - START_WAVELENGTH) / double(NUM_SPECTRUM_SAMPLES - 1);
    double halfBinWidth = binWidth / 2.0;
    start = START_WAVELENGTH + (index * binWidth) - halfBinWidth;
    end = START_WAVELENGTH + (index * binWidth) + halfBinWidth;
}

double SampledSpectrum::ComputeBoundaryArea(const SampleArray& samples, double leftBound, double rightBound) const
{
    double leftBoundaryRange = std::max<double>(0.0, samples.front().m_Wavelength - leftBound);
    double rightBoundRange = std::max<double>(0.0, rightBound - samples.back().m_Wavelength);
    double leftBoundArea = samples.front().m_Power * leftBoundaryRange;
    double rightBoundArea = samples.back().m_Power * rightBoundRange;

    return leftBoundArea + rightBoundArea;
}

double SampledSpectrum::ComputeSegmentArea(const Sample& s1, const Sample& s2, double leftBound, double rightBound) const
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

    for (; i + 1 < samples.size() && samples[i].m_Wavelength <= rightBound; ++i)
        sum +=  ComputeSegmentArea(samples[i], samples[i + 1], leftBound, rightBound);

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

