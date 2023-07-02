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

class TriangleMesh : public Geometry
{
public:
    TriangleMesh();
    ~TriangleMesh() override = default;

private:
    struct TriangleMeshVertex
    {
        Point3 m_Position;
        Normal3 m_Normal;
        Vector3 m_Tangent;
        Vector3 m_Bitangent;
        Vector2 m_TexCoord;
    };

    struct TriangleMeshFace
    {
        uint32_t m_VertexIndex0;
        uint32_t m_VertexIndex1;
        uint32_t m_VertexIndex2;
    };

    using TriangleMeshVertexIndex = uint32_t;

private:
    friend class AssetImporter;
    std::vector<TriangleMeshVertex> m_Vertices;
    std::vector<TriangleMeshFace> m_Faces;

};

