/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
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

#include "tonemapper.h"

class Film;

class Uncharted2FilmicTonemapper : public Tonemapper
{
public:
    Uncharted2FilmicTonemapper(
        double whitePoint = 11.2,
        double sAmt = 0.15,
        double lAmt = 0.50,
        double lAngle = 0.10,
        double tAmt = 0.20,
        double tNum = 0.02,
        double tDenom = 0.30
    );

public:
    RgbCoefficients ApplyTonemap(const RgbCoefficients& linearSpaceColor) override;

private:
    friend class Uncharted2FilmicTonemapperTest_FilmicCurveValues0To1_Test;
    friend class Uncharted2FilmicTonemapperTest_Values0To1AfterTonemapping_Test;

    RgbCoefficients FilmicCurve(const RgbCoefficients& x);

private:
    const double m_WhitePoint;
    const double m_ShoulderStrength;
    const double m_LinearStrength;
    const double m_LinearAngle;
    const double m_ToeStrength;
    const double m_ToeNumerator;
    const double m_ToeDenominator;
};

