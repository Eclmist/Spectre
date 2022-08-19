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

const double cieIntegralY = 106.856895;

const int numCieSamples = 471;
extern const double cieLambda[numCieSamples];
extern const double cieSamplesX[numCieSamples];
extern const double cieSamplesY[numCieSamples];
extern const double cieSamplesZ[numCieSamples];

const int numStdSamples = 32;
extern const double stdLambda[numStdSamples];
extern const double stdReflSamplesW[numStdSamples];
extern const double stdReflSamplesC[numStdSamples];
extern const double stdReflSamplesM[numStdSamples];
extern const double stdReflSamplesY[numStdSamples];
extern const double stdReflSamplesR[numStdSamples];
extern const double stdReflSamplesG[numStdSamples];
extern const double stdReflSamplesB[numStdSamples];
extern const double stdIllumSamplesW[numStdSamples];
extern const double stdIllumSamplesC[numStdSamples];
extern const double stdIllumSamplesM[numStdSamples];
extern const double stdIllumSamplesY[numStdSamples];
extern const double stdIllumSamplesR[numStdSamples];
extern const double stdIllumSamplesG[numStdSamples];
extern const double stdIllumSamplesB[numStdSamples];

