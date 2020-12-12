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

#pragma once

#include "spectrum.h"

#define START_WAVELENGTH 400
#define END_WAVELENGTH 700

class SampledSpectrum : public Spectrum
{
public:
    SampledSpectrum(double v = 0.0) : Spectrum(v) {}
    SampledSpectrum(const double* lambda, const double* v, int count);
    ~SampledSpectrum() = default;

private:
    bool IsSamplesSorted(const double* lambda, int count) const;
    bool IsInputOutsideLowerBounds(const double* lambda, int n, double rangeStart) const;
    bool IsInputOutsideUpperRange(const double* lambda, double rangeEnd) const;

    void ComputeWavelengthRange(int i, double& start, double& end) const;
    double ComputeBoundaryArea(const double* lambda, const double* v, int n, double rangeStart, double rangeEnd) const;
    double ComputeSegmentArea(const double* lambda, const double* v, int i, double rangeStart, double rangeEnd) const;
    double ComputeAreaSum(const double* lambda, const double* v, int n, double rangeStart, double rangeEnd) const;
    double ComputeAverageSamples(const double* lambda, const double* v, int n, double rangeStart, double rangeEnd) const;

private:
    friend class SampledSpectrumTest_CanComputeWavelengthRange_Test;
    friend class SampledSpectrumTest_CanComputeAreaSum_Test;
    friend class SampledSpectrumTest_CanComputeAverageSamples_Test;
};