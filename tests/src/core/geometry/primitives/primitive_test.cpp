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
#include "core/geometry/primitives/primitive.h"

class PrimitiveImplStub : public Primitive
{
public:
    PrimitiveImplStub(Geometry* parentGeometry)
        : Primitive(parentGeometry)
    {
    }

    ~PrimitiveImplStub() override = default;

public:
    bool Intersect(const Ray& ray) const override { return false; }
    bool Intersect(const Ray& ray, double* tHit, SurfaceInteraction* surface) const override { return false; }
    bool Sample(const Point2& uv, Interaction* interaction) const override { return false; }
};

TEST(PrimitiveTest, CanBeCreated)
{
    ASSERT_NO_THROW(PrimitiveImplStub(nullptr));
}

TEST(PrimitiveTest, CanGetTransform)
{
    PrimitiveImplStub primitive(nullptr);
    EXPECT_TRUE(primitive.GetTransform().IsIdentity());
}

TEST(PrimitiveTest, TransformReflectsParent)
{
    Geometry geometry;
    PrimitiveImplStub primitive(&geometry);
    EXPECT_TRUE(primitive.GetTransform().IsIdentity());

    geometry.SetTransform({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 });
    EXPECT_EQ(primitive.GetTransform(), Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6));
}

TEST(PrimitiveTest, CanGetParent)
{
    Geometry geometry;
    PrimitiveImplStub primitive(&geometry);
    EXPECT_EQ(primitive.GetParent(), &geometry);
}

TEST(PrimitiveTest, CanGetExtents)
{
    PrimitiveImplStub primitive(nullptr);
    EXPECT_EQ(primitive.GetExtents().m_Min, Point3());
    EXPECT_EQ(primitive.GetExtents().m_Max, Point3());
}

TEST(PrimitiveTest, ExtentsIsLocalSpace)
{
    Geometry geometry;
    geometry.SetTransform({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6 });

    PrimitiveImplStub primitive(&geometry);
    EXPECT_EQ(primitive.GetExtents().m_Min, Point3());
    EXPECT_EQ(primitive.GetExtents().m_Max, Point3());
}
