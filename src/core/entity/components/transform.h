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

#include "component.h"

class Transform : public Component
{
public:
    Transform();
    ~Transform() = default;

public:
    inline Vector3 GetTranslation() const { return m_Translation; }
    inline Vector3 GetRotation() const { return m_EulerRotation; }
    inline Vector3 GetScale() const { return m_Scale; }

public:
    void SetTranslation(const Vector3& translation);
    void SetRotation(const Vector3& eulerRotation);
    void SetScale(const Vector3& scale);

    Matrix4x4 GetMatrix() const;
    Matrix4x4 GetInverseMatrix() const;

private:
    static Matrix4x4 GetTranslationMatrix(const Vector3& translation);
    static Matrix4x4 GetRotationMatrix(const Vector3& rotation);
    static Matrix4x4 GetScaleMatrix(const Vector3& scale);

    static Matrix4x4 GetRotationMatrixX(double rotX);
    static Matrix4x4 GetRotationMatrixY(double rotY);
    static Matrix4x4 GetRotationMatrixZ(double rotZ);

private:
    Vector3 m_Translation;
    Vector3 m_EulerRotation;
    Vector3 m_Scale;
};