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
#include "math/point.h"

TEST(Point3Test, CanBeCreated)
{
    ASSERT_NO_THROW(Point3 p);
}

TEST(Point3Test, DefaultsToOrigin)
{
    Point3 p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
    EXPECT_DOUBLE_EQ(p.z, 0.0);
}

TEST(Point3Test, CanBeCreatedScalar)
{
    Point3 p(22.0);
    EXPECT_DOUBLE_EQ(p.x, 22.0);
    EXPECT_DOUBLE_EQ(p.y, 22.0);
    EXPECT_DOUBLE_EQ(p.z, 22.0);
}

TEST(Point3Test, CanBeCreatedPerComponent)
{
    Point3 p(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
    EXPECT_DOUBLE_EQ(p.z, 3.0);
}

TEST(Point3Test, CanBeSetPerComponents)
{
    Point3 p;
    p.x = 1.0;
    p.y = 2.0;
    p.z = 3.0;

    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
    EXPECT_DOUBLE_EQ(p.z, 3.0);
}

TEST(Point3Test, CanBeAccessedPerComponent)
{
    Point3 p(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(p[0], 1.0);
    EXPECT_DOUBLE_EQ(p[1], 2.0);
    EXPECT_DOUBLE_EQ(p[2], 3.0);
    EXPECT_DOUBLE_EQ(p.x, 1.0);
    EXPECT_DOUBLE_EQ(p.y, 2.0);
    EXPECT_DOUBLE_EQ(p.z, 3.0);
}

TEST(Point3Test, CanBeCopyConstructed)
{
    Point3 a(22.0);
    Point3 b(a);

    EXPECT_DOUBLE_EQ(b.x, 22.0);
    EXPECT_DOUBLE_EQ(b.y, 22.0);
    EXPECT_DOUBLE_EQ(b.z, 22.0);

    b.x = 0.0;
    EXPECT_DOUBLE_EQ(a.x, 22.0);
}

TEST(Point3Test, CanBeCopied)
{
    Point3 a(22.0);
    Point3 b = a;

    EXPECT_DOUBLE_EQ(b.x, 22.0);
    EXPECT_DOUBLE_EQ(b.y, 22.0);
    EXPECT_DOUBLE_EQ(b.z, 22.0);

    b.x = 0.0;
    EXPECT_DOUBLE_EQ(a.x, 22.0);
}

TEST(Point3Test, CanCheckEquality)
{
    EXPECT_EQ(Point3(1.0), Point3(1.0));
    EXPECT_EQ(Point3(0.2), Point3(0.2));
    EXPECT_EQ(Point3(1.0, 2.0, 3.0), Point3(1.0, 2.0, 3.0));
    EXPECT_NE(Point3(0.0), Point3(1.0));
    EXPECT_NE(Point3(0.0), Point3(0.00001));
    EXPECT_NE(Point3(0.0, 1.0, 2.0), Point3(0.0, 1.0, 2.1));
}

TEST(Point3Test, CanBeNegated)
{
    Point3 a(-1.0);
    Point3 b = -a;
    EXPECT_DOUBLE_EQ(b.x, 1.0);
    EXPECT_DOUBLE_EQ(b.y, 1.0);
    EXPECT_DOUBLE_EQ(b.z, 1.0);
}

TEST(Point3Test, DoesNotChangeWithPpeSign)
{
    Point3 a(-1.0);
    Point3 b = +a;
    EXPECT_DOUBLE_EQ(b.x, -1.0);
    EXPECT_DOUBLE_EQ(b.y, -1.0);
    EXPECT_DOUBLE_EQ(b.z, -1.0);
}
