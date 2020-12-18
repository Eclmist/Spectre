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

#include "reflectantspectrum.h"

ReflectantSpectrum::ReflectantSpectrum(const RGBCoefficients& rgb)
    : SampledSpectrum()
{
    // An RGB to Spectrum Conversion for Reflectances, Smits(2000)
    // http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.40.9608&rep=rep1&type=pdf
    double r = rgb[0];
    double g = rgb[1];
    double b = rgb[2];

    if (r <= g && r <= b)
    {
        if (g <= b)
            InitAscendingRGB(rgb);
        else
            InitAscendingRBG(rgb);
    }
    else if (g <= r && g <= b)
    {
        if (r <= b)
            InitAscendingGRB(rgb);
        else
            InitAscendingGBR(rgb);
    }
    else
    {
        if (r <= g)
            InitAscendingBRG(rgb);
        else
            InitAscendingBGR(rgb);
    }

    ClampZero();
}

void ReflectantSpectrum::InitAscendingRGB(const RGBCoefficients& rgb)
{
    *this += stdReflW * rgb[0];
    *this += stdReflC * (rgb[1] - rgb[0]);
    *this += stdReflB * (rgb[2] - rgb[1]);
}

void ReflectantSpectrum::InitAscendingRBG(const RGBCoefficients& rgb)
{
    *this += stdReflW * rgb[0];
    *this += stdReflC * (rgb[2] - rgb[0]);
    *this += stdReflG * (rgb[1] - rgb[2]);
}

void ReflectantSpectrum::InitAscendingGRB(const RGBCoefficients& rgb)
{
    *this += stdReflW * rgb[1];
    *this += stdReflM * (rgb[0] - rgb[1]);
    *this += stdReflB * (rgb[2] - rgb[0]);
}

void ReflectantSpectrum::InitAscendingGBR(const RGBCoefficients& rgb)
{
    *this += stdReflW * rgb[1];
    *this += stdReflM * (rgb[2] - rgb[1]);
    *this += stdReflR * (rgb[0] - rgb[2]);
}

void ReflectantSpectrum::InitAscendingBRG(const RGBCoefficients& rgb)
{
    *this += stdReflW * rgb[2];
    *this += stdReflY * (rgb[0] - rgb[2]);
    *this += stdReflG * (rgb[1] - rgb[0]);
}

void ReflectantSpectrum::InitAscendingBGR(const RGBCoefficients& rgb)
{
    *this += stdReflW * rgb[2];
    *this += stdReflY * (rgb[1] - rgb[2]);
    *this += stdReflR * (rgb[0] - rgb[1]);
}

