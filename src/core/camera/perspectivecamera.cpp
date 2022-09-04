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

#include "perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera(double fovH)
    : m_HorizontalFov(fovH)
{
}

Ray PerspectiveCamera::GenerateRay(const Point2i& filmSpacePos)
{
	double halfFovH = m_HorizontalFov / 2.0;
	double filmZPlane = (m_Film.GetResolution().GetWidth() / 2.0) / std::tan(Math::DegToRad(halfFovH));

	Point3 cameraSpaceFilmPoint = ToCameraSpace(filmSpacePos);
	cameraSpaceFilmPoint.z *= filmZPlane;
	Point3 rayOriginWs = ToWorldSpace(Point3(0, 0, 0));
	Vector3 rayDirectionWs = ToWorldSpace(cameraSpaceFilmPoint - Point3(0, 0, 0));
	return Ray(rayOriginWs, rayDirectionWs);
}

