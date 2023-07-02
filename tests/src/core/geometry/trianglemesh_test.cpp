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
#include "core/geometry/trianglemesh.h"

TEST(TriangleMeshTest, CanBeCreated)
{
    ASSERT_NO_THROW(TriangleMesh());
}

TEST(TriangleMeshTest, CanTransform)
{
    TriangleMesh triangleMesh;
    EXPECT_TRUE(triangleMesh.GetTransform().IsIdentity());

    Matrix4x4 randomTransform = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 };

    triangleMesh.SetTransform(randomTransform);
    EXPECT_EQ(triangleMesh.GetTransform(), randomTransform);
    EXPECT_EQ(triangleMesh.GetTransformInv(), randomTransform.Inversed());
}

TEST(TriangleMeshTest, CanGetBottomLevelAccelerator)
{
    TriangleMesh triangleMesh;
    Accelerator* bottomLevelBvh = triangleMesh.GetBottomLevelAccelerator();
    EXPECT_NE(bottomLevelBvh, nullptr);
}

TEST(TriangleMeshTest, CanGetVertices)
{
    TriangleMesh triangleMesh;
    EXPECT_TRUE(triangleMesh.GetVertices().empty());
}

TEST(TriangleMeshTest, CanGetFaces)
{
    TriangleMesh triangleMesh;
    EXPECT_TRUE(triangleMesh.GetFaces().empty());
}

TEST(TriangleMeshTest, CanSetVertices)
{
    TriangleMesh triangleMesh;
    TriangleMesh::Vertex vertices[3];
    vertices[0] = { .m_Position = { 0, 0, 0 } };
    vertices[1] = { .m_Position = { 1, 0, 0 } };
    vertices[2] = { .m_Position = { 1, 1, 0 } };

    triangleMesh.SetVertices(vertices, 3);

    ASSERT_EQ(triangleMesh.GetVertices().size(), 3);
    EXPECT_EQ(triangleMesh.GetVertices()[0].m_Position, Point3(0, 0, 0));
    EXPECT_EQ(triangleMesh.GetVertices()[1].m_Position, Point3(1, 0, 0));
    EXPECT_EQ(triangleMesh.GetVertices()[2].m_Position, Point3(1, 1, 0));
}

TEST(TriangleMeshTest, VerticesAreCopied)
{
    TriangleMesh triangleMesh;

    {
        TriangleMesh::Vertex vertices[3];
        vertices[0] = { .m_Position = { 0, 0, 0 } };
        vertices[1] = { .m_Position = { 1, 0, 0 } };
        vertices[2] = { .m_Position = { 1, 1, 0 } };

        triangleMesh.SetVertices(vertices, 3);

        vertices[0] = { .m_Position = { 9, 9, 9 } };
        vertices[1] = { .m_Position = { 9, 9, 9 } };
        vertices[2] = { .m_Position = { 9, 9, 9 } };
    }

    ASSERT_EQ(triangleMesh.GetVertices().size(), 3);
    EXPECT_EQ(triangleMesh.GetVertices()[0].m_Position, Point3(0, 0, 0));
    EXPECT_EQ(triangleMesh.GetVertices()[1].m_Position, Point3(1, 0, 0));
    EXPECT_EQ(triangleMesh.GetVertices()[2].m_Position, Point3(1, 1, 0));
}

TEST(TriangleMeshTest, CanSetFaces)
{
    TriangleMesh triangleMesh;
    TriangleMesh::Vertex vertices[3];
    vertices[0] = { .m_Position = { 0, 0, 0 } };
    vertices[1] = { .m_Position = { 1, 0, 0 } };
    vertices[2] = { .m_Position = { 1, 1, 0 } };
    triangleMesh.SetVertices(vertices, 3);

    TrianglePrimitive face(&triangleMesh, 0, 1, 2);
    triangleMesh.SetFaces(&face, 1);

    ASSERT_EQ(triangleMesh.GetFaces().size(), 1);
    EXPECT_EQ(triangleMesh.GetFaces()[0].GetParent(), &triangleMesh);
}

