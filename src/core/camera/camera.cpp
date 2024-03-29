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

#include "camera.h"

Vector3 Camera::ToWorldSpace(const Vector3& cameraSpaceVector)
{
    return (m_Transform * cameraSpaceVector.Resize<4>()).Resize<3>();
}

Point3 Camera::ToWorldSpace(const Point3& cameraSpacePoint)
{
    Point4 resizedPoint = cameraSpacePoint.Resize<4>();
    resizedPoint.w = 1.0;
    return (m_Transform * resizedPoint).Resize<3>();
}

Vector3 Camera::ToCameraSpace(const Vector3& worldSpaceVector)
{
    return (m_Transform.Inversed() * worldSpaceVector.Resize<4>()).Resize<3>();
}

Point3 Camera::ToCameraSpace(const Point3& worldSpacePoint)
{
    Point4 resizedPoint = worldSpacePoint.Resize<4>();
    resizedPoint.w = 1.0;

    return (m_Transform.Inversed() * resizedPoint).Resize<3>();
}

Point3 Camera::ToCameraSpace(const Point2i& filmSpacePoint)
{
    double halfFilmWidth = m_Film.GetResolution().GetWidth() / 2.0;
    double halfFilmHeight = m_Film.GetResolution().GetHeight() / 2.0;
    return { filmSpacePoint.x - halfFilmWidth, halfFilmHeight - filmSpacePoint.y, 1.0 };
}

