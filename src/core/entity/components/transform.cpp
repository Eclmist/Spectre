/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.

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

#include "transform.h"

Transform::Transform()
    : m_Translation(0.0)
    , m_EulerRotation(0.0)
    , m_Scale(1.0)
{
}

void Transform::Translate(const Vector4& translation)
{
    if (IsValidTranslation(translation))
        throw std::invalid_argument("The input translation is invalid");

    m_Translation += translation;
}

void Transform::Rotate(const Vector4& eulerRotation)
{
    if (IsValidRotation(eulerRotation))
        throw std::invalid_argument("The input rotation is invalid");

    m_EulerRotation += eulerRotation;
}

void Transform::Scale(const Vector4& scale)
{
    if (IsValidScale(scale))
        throw std::invalid_argument("The input scale is invalid");

    m_Scale *= scale;
}

void Transform::SetTranslation(const Vector4& translation)
{
    if (IsValidTranslation(translation))
        throw std::invalid_argument("The input translation is invalid");

    m_Translation = translation;
}

void Transform::SetRotation(const Vector4& eulerRotation)
{
    if (IsValidRotation(eulerRotation))
        throw std::invalid_argument("The input rotation is invalid");

    m_EulerRotation = eulerRotation;
}

void Transform::SetScale(const Vector4& scale)
{
    if (IsValidScale(scale))
        throw std::invalid_argument("The input scale is invalid");

    m_Scale = scale;
}

const Matrix4x4& Transform::GetMatrix() const
{
    return {};
}

const Matrix4x4& Transform::GetInverseMatrix() const
{
    return {};
}

bool Transform::IsValidTranslation(const Vector4& translation) const
{
    return translation.w != 0;
}

bool Transform::IsValidRotation(const Vector4& eulerRotation) const
{
    return eulerRotation.w != 0;
}

bool Transform::IsValidScale(const Vector4& scale) const
{
    return scale.w != 0;
}

