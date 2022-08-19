/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
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

class Ray
{
public:
    Ray(const Vector3& origin, const Vector3& direction);
    ~Ray() = default;

public:
    inline Vector3 operator()(double t) const { return m_Origin + m_Direction * t; }

    inline Vector3 GetOrigin() const { return m_Origin; }
    inline Vector3 GetDirection() const { return m_Direction; }

    inline void SetOrigin(Vector3 origin) { m_Origin = origin; }
    inline void SetDirection(Vector3 direction) { m_Direction = direction.Normalized(); }

private:
    Vector3 m_Origin;
    Vector3 m_Direction;
};