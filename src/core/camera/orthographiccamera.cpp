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

#include "orthographiccamera.h"

OrthographicCamera::OrthographicCamera(double size)
    : m_Size(size)
{
}

Ray OrthographicCamera::GenerateRay(const Point2i& filmSpacePos, const Vector2& offset)
{
    // Add an empirical scale such that size=1 is consistent with perspective camera
    const double sizeScale = 0.005;
    const double scaledSize = m_Size * sizeScale;
    Point3 cameraSpaceFilmPoint = ToCameraSpace(filmSpacePos);
    cameraSpaceFilmPoint.x += offset.x;
    cameraSpaceFilmPoint.y += offset.y;

    Point3 rayOriginWs = ToWorldSpace(Point3(cameraSpaceFilmPoint.x * scaledSize, cameraSpaceFilmPoint.y * scaledSize, 0));
    Vector3 rayDirectionWs = ToWorldSpace(Vector3(0, 0, 1));
    return Ray(rayOriginWs, rayDirectionWs);
}

