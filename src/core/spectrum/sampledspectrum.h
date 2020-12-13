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
#include "sample.h"
#include "spectralcoefficients.h"
#include "math/vector4.h"

#define START_WAVELENGTH 400
#define END_WAVELENGTH 700

class SampledSpectrum : public Spectrum
{
public:
    SampledSpectrum(double v = 0.0) : Spectrum(v) {}
    SampledSpectrum(const SampleArray& samples);
    ~SampledSpectrum() = default;

    static void Init();
    static void InitCieReferenceCurves();
    static SampledSpectrum FromRawSamples(const double* lambda, const double* power, int numSamples);

    static RGBCoefficients XYZToRGB(XYZCoefficients xyz);
    static XYZCoefficients RGBToXYZ(RGBCoefficients rgb);

    XYZCoefficients ToXYZ() const;
    RGBCoefficients ToRGB() const;

private:
    bool IsSamplesSorted(const SampleArray& samples) const;
    bool IsInputOutsideLeftBoundary(const SampleArray& samples, double leftBound) const;
    bool IsInputOutsideRightBoundary(const SampleArray& samples, double rightBound) const;

    void ComputeRangeAtIndex(int index, double& start, double& end) const;
    double ComputeBoundaryArea(const SampleArray& samples, double leftBound, double rightBound) const;
    double ComputeSegmentArea(const Sample& s1, const Sample& s2, double leftBound, double rightBound) const;
    double ComputeAreaSum(const SampleArray& samples, double leftBound, double rightBound) const;
    double ComputeAverageInRange(const SampleArray& samples, double leftBound, double rightBound) const;

private:
    friend class SampledSpectrumTest_CanComputeWavelengthRange_Test;
    friend class SampledSpectrumTest_CanComputeAreaSum_Test;
    friend class SampledSpectrumTest_CanComputeAverageSamples_Test;
    friend class SampledSpectrumTest_CanInitCIECurves_Test;

    static SampledSpectrum CIE_X;
    static SampledSpectrum CIE_Y;
    static SampledSpectrum CIE_Z;
};