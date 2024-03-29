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

namespace Sampling
{
    inline Point3 UniformSampleHemisphere()
    {
        double y = SMath::Random::UniformFloat();
        double r = std::sqrt(std::max(0.0, 1.0 - y * y));
        double phi = 2 * SMath::Pi * SMath::Random::UniformFloat();
        return Point3(r * cos(phi), y, r * sin(phi));
    }

    inline double UniformHemispherePdf() {
        return SMath::Inv2Pi;
    }

    inline Point3 UniformSampleSphere()
    {
        double z = 1 - 2 * SMath::Random::UniformFloat();
        double r = std::sqrt(std::max(0.0, 1.0 - z * z));
        double phi = 2 * SMath::Pi * SMath::Random::UniformFloat();
        return Point3(r * cos(phi), r * sin(phi), z);
    }

    inline double UniformSpherePdf()
    {
        return SMath::Inv4Pi;
    }

    inline Point2 RejectionSampleDisk()
    {
        Point2 p;
        do {
            p.x = 1 - 2 * SMath::Random::UniformFloat();
            p.y = 1 - 2 * SMath::Random::UniformFloat();
        } while (p.x * p.x + p.y * p.y > 1);
        return p;
    }

    inline Point2 ConcentricSampleDisk()
    {
        Point2 uOffset = Point2(SMath::Random::UniformFloat() * 2.0 - 1.0, SMath::Random::UniformFloat() * 2.0 - 1.0);

        if (uOffset.x == 0 && uOffset.y == 0)
            return {};

        double theta, r;

        if (std::abs(uOffset.x) > std::abs(uOffset.y))
        {
            r = uOffset.x;
            theta = SMath::PiOver4 * (uOffset.y / uOffset.x);
        }
        else 
        {
            r = uOffset.y;
            theta = SMath::PiOver2 - SMath::PiOver4 * (uOffset.x / uOffset.y);
        }

        return Point2(cos(theta) * r, sin(theta) * r);
    }

    inline Point3 CosineSampleHemisphere()
    {
        Point2 d = ConcentricSampleDisk();
        double z = std::sqrt(std::max(0.0, 1.0 - d.x * d.x - d.y * d.y));
        return Point3(d.x, d.y, z);
    }

    inline double CosineHemispherePdf(double cosTheta)
    {
        return cosTheta * SMath::InvPi;
    }
}

