/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
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

#include "gtest.h"
#include "core/geometry/primitives/triangleprimitive.h"
#include "core/geometry/trianglemesh.h"

TEST(TrianglePrimitiveTest, CanBeCreated)
{
    ASSERT_NO_THROW(TrianglePrimitive(nullptr, 0, 1, 2));
}

TEST(TrianglePrimitiveTest, CanGetExtents)
{
    TriangleMesh triangleMesh;
    TriangleMesh::Vertex vertices[3];
    vertices[0] = { .m_Position = { -1, 0, 0 } };
    vertices[1] = { .m_Position = { 1, 0, 5 } };
    vertices[2] = { .m_Position = { 1, 2, 1 } };
    triangleMesh.SetVertices(vertices, 3);

    TrianglePrimitive face(&triangleMesh, 0, 1, 2);
    triangleMesh.SetFaces(&face, 1);

    EXPECT_EQ(face.GetExtents().m_Min, Point3(-1, 0, 0));
    EXPECT_EQ(face.GetExtents().m_Max, Point3(1, 2, 5));
}

TEST(TrianglePrimitiveTest, CanComputeIntersection)
{
    double tHit;
    SurfaceInteraction surf;

    TriangleMesh triangleMesh;
    TriangleMesh::Vertex vertices[3];
    vertices[0] = { .m_Position = { 0, 0, 1 } };
    vertices[1] = { .m_Position = { 1, 0, 1 } };
    vertices[2] = { .m_Position = { 1, 1, 1 } };
    triangleMesh.SetVertices(vertices, 3);

    TrianglePrimitive face(&triangleMesh, 0, 1, 2);
    triangleMesh.SetFaces(&face, 1);

    EXPECT_TRUE(face.Intersect(Ray({ 0, 0, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_TRUE(face.Intersect(Ray({ 1, 0, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_TRUE(face.Intersect(Ray({ 1, 1, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_TRUE(face.Intersect(Ray({ 0.5, 0.5, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_TRUE(face.Intersect(Ray({ 1, 0.5, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_TRUE(face.Intersect(Ray({ 0.5, 0, 0 }, { 0, 0, 1 }), &tHit, &surf));

    EXPECT_FALSE(face.Intersect(Ray({ 0, 0, 0 }, { 0, 1, 0 }), &tHit, &surf));
    EXPECT_FALSE(face.Intersect(Ray({ 0, 0.01, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_FALSE(face.Intersect(Ray({ 0.99, 1, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_FALSE(face.Intersect(Ray({ 0.5, 0.5001, 0 }, { 0, 0, 1 }), &tHit, &surf));
    EXPECT_FALSE(face.Intersect(Ray({ 1, 1.01, 0 }, { 0, 0, 1 }), &tHit, &surf));
}

