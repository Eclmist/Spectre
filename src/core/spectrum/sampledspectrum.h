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

#pragma once

#include "spectrum.h"
#include "spectralsample.h"
#include "spectralcoefficients.h"

const int MinWavelength = 360;
const int MaxWavelength = 830;

class SampledSpectrum : public Spectrum
{
public:
    SampledSpectrum(double v = 0.0) : Spectrum(v) {}
    SampledSpectrum(const SampleArray& samples);
    SampledSpectrum(Spectrum& v) : Spectrum(v) {}
    ~SampledSpectrum() = default;

    static SampledSpectrum FromSortedRawSamples(const double* lambda, const double* power, int numSamples);
    static RgbCoefficients XyzToRgb(const XyzCoefficients& xyz);
    static XyzCoefficients RgbToXyz(const RgbCoefficients& rgb);

    XyzCoefficients ToXyz() const;
    RgbCoefficients ToRgb() const;

protected:
    bool IsSamplesSorted(const SampleArray& samples) const;
    bool IsInputOutsideLeftBoundary(const SampleArray& samples, double leftBound) const;
    bool IsInputOutsideRightBoundary(const SampleArray& samples, double rightBound) const;

    void ComputeRangeAtIndex(int index, double& start, double& end) const;
    double ComputeBoundaryArea(const SampleArray& samples, double leftBound, double rightBound) const;
    double ComputeSegmentArea(const SpectralSample& s1, const SpectralSample& s2, double leftBound, double rightBound) const;
    double ComputeAreaSum(const SampleArray& samples, double leftBound, double rightBound) const;
    double ComputeAverageInRange(const SampleArray& samples, double leftBound, double rightBound) const;

    virtual double GetXyzNormalizationConstant() const;

protected:
    friend class SampledSpectrumTest_CanComputeWavelengthRange_Test;
    friend class SampledSpectrumTest_CanComputeAreaSum_Test;
    friend class SampledSpectrumTest_CanComputeAverageSamples_Test;
    friend class SampledSpectrumTest_CanPopulateStandardCurves_Test;

    static const SampledSpectrum cieX;
    static const SampledSpectrum cieY;
    static const SampledSpectrum cieZ;

    static const SampledSpectrum stdReflW, stdIllumW;
    static const SampledSpectrum stdReflC, stdIllumC;
    static const SampledSpectrum stdReflM, stdIllumM;
    static const SampledSpectrum stdReflY, stdIllumY;
    static const SampledSpectrum stdReflR, stdIllumR;
    static const SampledSpectrum stdReflG, stdIllumG;
    static const SampledSpectrum stdReflB, stdIllumB;
};