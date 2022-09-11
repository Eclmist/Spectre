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

#include "uncharted2filmictonemapper.h"

Uncharted2FilmicTonemapper::Uncharted2FilmicTonemapper(
    double whitePoint,
    double sAmt,
    double lAmt,
    double lAngle,
    double tAmt,
    double tNum,
    double tDenom)
    : m_ShoulderStrength(sAmt)
    , m_LinearStrength(lAmt)
    , m_LinearAngle(lAngle)
    , m_ToeStrength(tAmt)
    , m_ToeNumerator(tNum)
    , m_ToeDenominator(tDenom)
    , m_WhitePoint(whitePoint)
{
}

RgbCoefficients Uncharted2FilmicTonemapper::ApplyTonemap(const RgbCoefficients& linearSpaceColor)
{
    RgbCoefficients col = FilmicCurve(linearSpaceColor);
    col *= RgbCoefficients(1.0) / FilmicCurve(m_WhitePoint);
    return ApplyGammaCorrection(col);
}

RgbCoefficients Uncharted2FilmicTonemapper::FilmicCurve(const RgbCoefficients& x)
{
    const double& A = m_ShoulderStrength;
    const double& B = m_LinearStrength;
    const double& C = m_LinearAngle;
    const double& D = m_ToeStrength;
    const double& E = m_ToeNumerator;
    const double& F = m_ToeDenominator;

    return ((x * (x * A + C * B) + D * E) / (x * (x * A + B) + D * F)) - E / F;
}


