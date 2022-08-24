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

#include "sampledspectrum.h"

class IlluminantSpectrum : public SampledSpectrum
{
public:
    IlluminantSpectrum(const RgbCoefficients& rgb);

    // TODO: Might have to override the normalization constant to 
    // 683lm/W: https://light-measurement.com/colorimetry/

private:
    void InitAscendingRgb(const RgbCoefficients& rgb);
    void InitAscendingRbg(const RgbCoefficients& rgb);
    void InitAscendingGrb(const RgbCoefficients& rgb);
    void InitAscendingGbr(const RgbCoefficients& rgb);
    void InitAscendingBrg(const RgbCoefficients& rgb);
    void InitAscendingBgr(const RgbCoefficients& rgb);
};