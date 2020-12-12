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

SampledSpectrum::SampledSpectrum(const double* lambda, const double* v, int count)
{
    if (!IsSamplesSorted(lambda, count))
        return;

    for (int i = 0; i < NUM_SPECTRUM_SAMPLES; ++i)
    {
        double sampleiLambdaStart, sampleiLambdaEnd;
        ComputeWavelengthRange(i, sampleiLambdaStart, sampleiLambdaEnd);
        m_Coefficients[i] = ComputeAverageSamples(lambda, v, count, sampleiLambdaStart, sampleiLambdaEnd);
    }
}

bool SampledSpectrum::IsSamplesSorted(const double* lambda, int count) const
{
    if (count <= 1)
        return true;

    for (int i = 0; i < count - 1; ++i)
        if (lambda[i] > lambda[i + 1])
            return false;
            
    return true;
}

bool SampledSpectrum::IsInputOutsideLowerBounds(const double* lambda, int n, double rangeStart) const
{
    return lambda[n - 1] <= rangeStart;
}

bool SampledSpectrum::IsInputOutsideUpperRange(const double* lambda, double rangeEnd) const
{
    return lambda[0] >= rangeEnd;
}

void SampledSpectrum::ComputeWavelengthRange(int i, double& start, double& end) const
{
    double binWidth = (END_WAVELENGTH - START_WAVELENGTH) / double(NUM_SPECTRUM_SAMPLES - 1);
    start = START_WAVELENGTH + i * binWidth - (binWidth / 2.0);
    end = START_WAVELENGTH + i * binWidth + (binWidth / 2.0);
}

double SampledSpectrum::ComputeBoundaryArea(const double* lambda, const double* v, int n, double rangeStart, double rangeEnd) const
{
    double lowerBoundaryArea = (lambda[0] > rangeStart) ? v[0] * (lambda[0] - rangeStart) : 0;
    double upperBoundaryArea = (lambda[n - 1] < rangeEnd) ? v[n - 1] * (rangeEnd - lambda[n - 1]) : 0;
    return lowerBoundaryArea + upperBoundaryArea;
}

double SampledSpectrum::ComputeSegmentArea(const double* lambda, const double* v, int i, double rangeStart, double rangeEnd) const
{
    double startPoint = lambda[i] < rangeStart ? rangeStart : lambda[i];
    double endPoint = lambda[i + 1] > rangeEnd ? rangeEnd : lambda[i + 1];
    double startVal = std::lerp(v[i], v[i + 1], (startPoint - lambda[i]) / (lambda[i + 1] - lambda[i]));
    double endVal = std::lerp(v[i], v[i + 1], (endPoint - lambda[i]) / (lambda[i + 1] - lambda[i]));
    return  0.5 * (startVal + endVal) * (endPoint - startPoint);
}

double SampledSpectrum::ComputeAreaSum(const double* lambda, const double* v, int n, double rangeStart, double rangeEnd) const
{
    double sum = 0;

    int startIndex = 0;
    while (lambda[startIndex + 1] < rangeStart) ++startIndex;

    for (int i = startIndex; i + 1 < n && rangeEnd >= lambda[i]; ++i)
        sum +=  ComputeSegmentArea(lambda, v, i, rangeStart, rangeEnd);

    sum += ComputeBoundaryArea(lambda, v, n, rangeStart, rangeEnd);
    return sum;
}

double SampledSpectrum::ComputeAverageSamples(const double* lambda, const double* v, int n, double rangeStart, double rangeEnd) const
{
    if (IsInputOutsideUpperRange(lambda, rangeEnd))
        return v[0];

    if (IsInputOutsideLowerBounds(lambda, n, rangeStart))
        return v[n - 1];

    if (n == 1)
        return v[0];

    double sum = ComputeAreaSum(lambda, v, n, rangeStart, rangeEnd);
    double average = sum / (rangeEnd - rangeStart);
    return average;
}

