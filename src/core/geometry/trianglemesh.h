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

#include "geometry.h"
#include "core/geometry/primitives/triangleprimitive.h"

class TriangleMesh : public Geometry
{
public:
    TriangleMesh();
    ~TriangleMesh() override = default;

public:
    struct Vertex
    {
        Point3 m_Position;
        Normal3 m_Normal;
        Vector3 m_Tangent;
        Vector3 m_Bitangent;
        Vector2 m_TexCoord;
    };

public:
    inline const Vertex* GetVertex(uint32_t index) const { return &m_Vertices[index]; }
    inline const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
    inline const std::vector<TrianglePrimitive>& GetFaces() const { return m_Faces; }

public:
    void SetVertices(Vertex* vertices, uint32_t numVertices);
    void SetFaces(TrianglePrimitive* faces, uint32_t numFaces);

private:
    std::vector<Vertex> m_Vertices;
    std::vector<TrianglePrimitive> m_Faces;
};

