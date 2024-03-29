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

#include "core/film/film.h"

class Camera
{
public:
    Camera() = default;
    ~Camera() = default;

public:
    inline Matrix4x4& GetTransform() { return m_Transform; }
    inline Film& GetFilm() { return m_Film; }

public:
    virtual Ray GenerateRay(const Point2i& filmSpacePos, const Vector2& offset) = 0;

protected:
    friend class CameraTest_CanTransformCameraPointToWorldSpace_Test;
    friend class CameraTest_CanTransformCameraVectorToWorldSpace_Test;
    friend class CameraTest_CanTranformFilmPointToCameraSpace_Test;
    friend class CameraTest_CanTransformWorldVectorToCameraSpace_Test;
    friend class CameraTest_CanTransformWorldPointToCameraSpace_Test;

    Vector3 ToWorldSpace(const Vector3& cameraSpaceVector);
    Point3 ToWorldSpace(const Point3& cameraSpacePoint);

    Vector3 ToCameraSpace(const Vector3& worldSpaceVector);
    Point3 ToCameraSpace(const Point3& worldSpacePoint);
    Point3 ToCameraSpace(const Point2i& filmSpacePoint);

protected:
    Matrix4x4 m_Transform;
    Film m_Film;
};

