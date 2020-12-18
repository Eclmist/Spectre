/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.

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

#pragma once

#include "component.h"
#include "math/matrix4x4.h"
#include "math/vector4.h"

class Transform : public Component
{
public:
    Transform();
    ~Transform() = default;

    inline Vector4 GetTranslation() const { return m_Translation; }
    inline Vector4 GetRotation() const { return m_EulerRotation; }
    inline Vector4 GetScale() const { return m_Scale; }

    void SetTranslation(const Vector4& translation);
    void SetRotation(const Vector4& eulerRotation);
    void SetScale(const Vector4& scale);

    Matrix4x4 GetMatrix() const;
    Matrix4x4 GetInverseMatrix() const;

private:
    bool IsValidTranslation(const Vector4& translation) const;
    bool IsValidRotation(const Vector4& rotation) const;
    bool IsValidScale(const Vector4& scale) const;

    static Matrix4x4 GetTranslationMatrix(const Vector4& translation);
    static Matrix4x4 GetRotationMatrix(const Vector4& rotation);
    static Matrix4x4 GetScaleMatrix(const Vector4& scale);

    static Matrix4x4 GetRotationMatrixX(double rotX);
    static Matrix4x4 GetRotationMatrixY(double rotY);
    static Matrix4x4 GetRotationMatrixZ(double rotZ);

private:
    Vector4 m_Translation;
    Vector4 m_EulerRotation;
    Vector4 m_Scale;
};