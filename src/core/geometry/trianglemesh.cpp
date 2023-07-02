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

#include "trianglemesh.h"
#include "core/spatial/qbvhaccelerator.h"

TriangleMesh::TriangleMesh()
{
    m_BottomLevelAccelerator = std::make_unique<QBvhAccelerator>();
}

void TriangleMesh::SetVertices(Vertex* vertices, uint32_t numVertices)
{
    m_Vertices.clear();
    m_Vertices.assign(vertices, vertices + numVertices);
}

void TriangleMesh::SetFaces(TrianglePrimitive* faces, uint32_t numFaces)
{
    m_Faces.clear();
    m_Faces.assign(faces, faces + numFaces);
}
