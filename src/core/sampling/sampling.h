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
	inline Vector3 UniformSampleHemisphere()
	{
		double y = Random::UniformFloat();
		double r = std::sqrt(std::max(0.0, 1.0 - y * y));
		double phi = 2 * Math::Pi * Random::UniformFloat();
		return Vector3(r * cos(phi), y, r * sin(phi));
	}

	inline double UniformHemispherePdf() {
		return Math::Inv2Pi;
	}

	inline Vector3 UniformSampleSphere()
	{
		double z = 1 - 2 * Random::UniformFloat();
		double r = std::sqrt(std::max(0.0, 1.0 - z * z));
		double phi = 2 * Math::Pi * Random::UniformFloat();
		return Vector3(r * cos(phi), r * sin(phi), z);
	}

	inline double UniformSpherePdf()
	{
		return Math::Inv4Pi;
	}

	inline Vector2 RejectionSampleDisk()
	{
		Vector2 p;
		do {
			p.x = 1 - 2 * Random::UniformFloat();
			p.y = 1 - 2 * Random::UniformFloat();
		} while (p.x * p.x + p.y * p.y > 1);
		return p;
	}

	inline Vector2 ConcentricSampleDisk()
	{
		Vector2 uOffset = Vector2(Random::UniformFloat(), Random::UniformFloat()) * Vector2(2) - Vector2(1);

		if (uOffset.x == 0 && uOffset.y == 0)
			return {};

		double theta, r;

		if (abs(uOffset.x) > abs(uOffset.y)) 
		{
			r = uOffset.x;
			theta = Math::PiOver4 * (uOffset.y / uOffset.x);
		}
		else 
		{
			r = uOffset.y;
			theta = Math::PiOver2 - Math::PiOver4 * (uOffset.x / uOffset.y);
		}

		return Vector2(r) * Vector2(cos(theta), sin(theta));
	}

	inline Vector3 CosineSampleHemisphere()
	{
		Vector2 d = ConcentricSampleDisk();
		double z = std::sqrt(std::max(0.0, 1.0 - d.x * d.x - d.y * d.y));
		return Vector3(d.x, d.y, z);
	}

	inline double CosineHemispherePdf(double cosTheta)
	{
		return cosTheta * Math::InvPi;
	}
}

