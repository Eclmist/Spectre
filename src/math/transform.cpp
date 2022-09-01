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

#include "transform.h"

Transform::Transform()
    : m_Translation(0.0)
    , m_EulerRotation(0.0)
    , m_Scale(1.0)
{
}

void Transform::SetTranslation(const Vector3& translation)
{
    m_Translation = translation;
}

void Transform::SetRotation(const Vector3& eulerRotation)
{
    m_EulerRotation = eulerRotation;
}

void Transform::SetScale(const Vector3& scale)
{
    m_Scale = scale;
}

Matrix4x4 Transform::GetMatrix() const
{
    return GetTranslationMatrix(m_Translation) * GetRotationMatrix(m_EulerRotation) * GetScaleMatrix(m_Scale);
}

Matrix4x4 Transform::GetInverseMatrix() const
{
    return GetScaleMatrix(Vector3(1.0) / m_Scale) * GetRotationMatrix(-m_EulerRotation) * GetTranslationMatrix(-m_Translation);
}

Matrix4x4 Transform::GetTranslationMatrix(const Vector3& translation)
{
    return { 1.0, 0.0, 0.0, translation.x,
             0.0, 1.0, 0.0, translation.y,
             0.0, 0.0, 1.0, translation.z,
             0.0, 0.0, 0.0, 1.0 };
}

Matrix4x4 Transform::GetRotationMatrix(const Vector3& rotation)
{
    return GetRotationMatrixZ(rotation.z) * GetRotationMatrixY(rotation.y) * GetRotationMatrixX(rotation.x); }

Matrix4x4 Transform::GetScaleMatrix(const Vector3& scale)
{
    return { scale.x, 0.0, 0.0, 0.0,
             0.0, scale.y, 0.0, 0.0,
             0.0, 0.0, scale.z, 0.0,
             0.0, 0.0, 0.0, 1.0 };

}

Matrix4x4 Transform::GetRotationMatrixX(double rotX)
{
    return { 1.0, 0.0, 0.0, 0.0,
             0.0, cos(rotX), -sin(rotX), 0.0,
             0.0, sin(rotX), cos(rotX), 0.0,
             0.0, 0.0, 0.0, 1.0 };
}

Matrix4x4 Transform::GetRotationMatrixY(double rotY)
{
    return { cos(rotY), 0.0, sin(rotY), 0.0,
             0.0, 1.0, 0.0, 0.0,
             -sin(rotY), 0.0, cos(rotY), 0.0,
             0.0, 0.0, 0.0, 1.0 };
}

Matrix4x4 Transform::GetRotationMatrixZ(double rotZ)
{
    return { cos(rotZ), -sin(rotZ), 0.0, 0.0,
             sin(rotZ), cos(rotZ), 0.0, 0.0,
             0.0, 0.0, 1.0, 0.0,
             0.0, 0.0, 0.0, 1.0 };
}

