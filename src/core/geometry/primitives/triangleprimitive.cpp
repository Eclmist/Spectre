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

#include "triangleprimitive.h"
#include "core/geometry/trianglemesh.h"

TrianglePrimitive::TrianglePrimitive(TriangleMesh* parentMesh, uint32_t v0, uint32_t v1, uint32_t v2)
    : Primitive(parentMesh)
{
    m_VertexIndices[0] = v0;
    m_VertexIndices[1] = v1;
    m_VertexIndices[2] = v2;
}

bool TrianglePrimitive::Intersect(const Ray& ray) const
{
    return false;
}

bool TrianglePrimitive::Intersect(const Ray& ray, double* tHit, SurfaceInteraction* surface) const
{
    return false;
}

bool TrianglePrimitive::Sample(const Point2& uv, Interaction* interaction) const
{
    return false;
}

