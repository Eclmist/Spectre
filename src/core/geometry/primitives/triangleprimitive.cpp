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

    CalculateBoundingBox();
}

bool TrianglePrimitive::Intersect(const Ray& ray) const
{
    return false;
}

bool TrianglePrimitive::Intersect(const Ray& ray, double* tHit, SurfaceInteraction* surface) const
{
    Vector3 e1, e2, p, q, t;
    const TriangleMesh::Vertex& v0 = *(dynamic_cast<TriangleMesh*>(m_ParentGeometry))->GetVertex(m_VertexIndices[0]);
    const TriangleMesh::Vertex& v1 = *(dynamic_cast<TriangleMesh*>(m_ParentGeometry))->GetVertex(m_VertexIndices[1]);
    const TriangleMesh::Vertex& v2 = *(dynamic_cast<TriangleMesh*>(m_ParentGeometry))->GetVertex(m_VertexIndices[2]);

    e1 = v1.m_Position - v0.m_Position;
    e2 = v2.m_Position - v0.m_Position;

    p = Vector3::Cross(ray.m_Direction, e2);
    double det = Vector3::Dot(e1, p);

    if (abs(det) < SMath::Epsilon)
        return false;

    double invDet = 1 / det;

    // Calculate distance from v0 to ray origin
    t = ray.m_Origin - v0.m_Position;

    // Barycentric coordinates
    double u, v;

    u = Vector3::Dot(t, p) * invDet;
    // Barycentric coordinates lie outside bounds (no intersect)
    if (u < 0 || u > 1)
        return false;

    q = Vector3::Cross(t, e1);

    v = Vector3::Dot(ray.m_Direction, q) * invDet;
    // Barycentric coordinates lie outside bounds (no intersect)
    if (v < 0 || u + v > 1)
        return false;

    // Compute normal vector
    Normal3 normal = Normal3(1 - u - v) * v0.m_Normal + Normal3(u) * v1.m_Normal + Normal3(v) * v2.m_Normal;

    double temp = Vector3::Dot(e2, q) * invDet;

    if (temp < 0 || temp > ray.m_TMax)
        return false;

    *tHit = temp;
    surface->m_Point = ray(*tHit);
    surface->m_Normal = normal.Normalized();
    surface->m_Wo = -ray.m_Direction;
    surface->m_Primitive = (Primitive*)(this);

    return true;
}

bool TrianglePrimitive::Sample(const Point2& uv, Interaction* interaction) const
{
    return false;
}

void TrianglePrimitive::CalculateBoundingBox()
{
    if (m_ParentGeometry == nullptr)
        return;

    const TriangleMesh::Vertex& v0 = *(dynamic_cast<TriangleMesh*>(m_ParentGeometry))->GetVertex(m_VertexIndices[0]);
    const TriangleMesh::Vertex& v1 = *(dynamic_cast<TriangleMesh*>(m_ParentGeometry))->GetVertex(m_VertexIndices[1]);
    const TriangleMesh::Vertex& v2 = *(dynamic_cast<TriangleMesh*>(m_ParentGeometry))->GetVertex(m_VertexIndices[2]);

    Point3 min, max;
    min.x = std::min({ v0.m_Position.x, v1.m_Position.x, v2.m_Position.x });
    min.y = std::min({ v0.m_Position.y, v1.m_Position.y, v2.m_Position.y });
    min.z = std::min({ v0.m_Position.z, v1.m_Position.z, v2.m_Position.z });

    max.x = std::max({ v0.m_Position.x, v1.m_Position.x, v2.m_Position.x });
    max.y = std::max({ v0.m_Position.y, v1.m_Position.y, v2.m_Position.y });
    max.z = std::max({ v0.m_Position.z, v1.m_Position.z, v2.m_Position.z });

    m_BoundingBox.m_Min = min;
    m_BoundingBox.m_Max = max;
}

