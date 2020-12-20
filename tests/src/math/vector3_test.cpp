/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest.h"
#include "math/vector.h"

#define CHECK_PADDING(v) EXPECT_EQ(v[3], 0);

TEST(Vector3Test, CanBeCreated)
{
    ASSERT_NO_THROW(Vector3 v);
}

TEST(Vector3Test, DefaultsToZeroVector)
{
    Vector3 v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
    CHECK_PADDING(v);
}

TEST(Vector3Test, CanBeCreatedScalar)
{
    Vector3 v(22.0);
    EXPECT_DOUBLE_EQ(v.x, 22.0);
    EXPECT_DOUBLE_EQ(v.y, 22.0);
    EXPECT_DOUBLE_EQ(v.z, 22.0);
    CHECK_PADDING(v);
}

TEST(Vector3Test, CanBeCreatedPerComponent)
{
    Vector3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    CHECK_PADDING(v);
}

TEST(Vector3Test, CanBeSetPerComponents)
{
    Vector3 v;
    v.x = 1.0;
    v.y = 2.0;
    v.z = 3.0;

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    CHECK_PADDING(v);
}

TEST(Vector3Test, CanBeAccessedPerComponent)
{
    Vector3 v(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    CHECK_PADDING(v);
}

TEST(Vector3Test, CanBeCopyConstructed)
{
    Vector3 a(22.0);
    Vector3 b(a);

    EXPECT_DOUBLE_EQ(b.x, 22.0);
    EXPECT_DOUBLE_EQ(b.y, 22.0);
    EXPECT_DOUBLE_EQ(b.z, 22.0);

    b.x = 0.0;
    EXPECT_DOUBLE_EQ(a.x, 22.0);
    CHECK_PADDING(b);
}

TEST(Vector3Test, CanBeCopied)
{
    Vector3 a(22.0);
    Vector3 b = a;

    EXPECT_DOUBLE_EQ(b.x, 22.0);
    EXPECT_DOUBLE_EQ(b.y, 22.0);
    EXPECT_DOUBLE_EQ(b.z, 22.0);

    b.x = 0.0;
    EXPECT_DOUBLE_EQ(a.x, 22.0);
    CHECK_PADDING(b);
}

TEST(Vector3Test, CanCheckEquality)
{
    EXPECT_EQ(Vector3(1.0), Vector3(1.0));
    EXPECT_EQ(Vector3(0.2), Vector3(0.2));
    EXPECT_EQ(Vector3(1.0, 2.0, 3.0), Vector3(1.0, 2.0, 3.0));
    EXPECT_NE(Vector3(0.0), Vector3(1.0));
    EXPECT_NE(Vector3(0.0), Vector3(0.00001));
    EXPECT_NE(Vector3(0.0, 1.0, 2.0), Vector3(0.0, 1.0, 2.1));
}

TEST(Vector3Test, CanBeAdded)
{
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(2.0, 3.0, 4.0);

    Vector3 c = a + b;
    EXPECT_DOUBLE_EQ(c.x, 3.0);
    EXPECT_DOUBLE_EQ(c.y, 5.0);
    EXPECT_DOUBLE_EQ(c.z, 7.0);
    CHECK_PADDING(c);
}

TEST(Vector3Test, CanBeAddAssigned)
{
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(2.0, 3.0, 4.0);
    b += a;

    EXPECT_DOUBLE_EQ(b.x, 3.0);
    EXPECT_DOUBLE_EQ(b.y, 5.0);
    EXPECT_DOUBLE_EQ(b.z, 7.0);
    CHECK_PADDING(b);
}

TEST(Vector3Test, CanBeSubtracted)
{
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(2.0, 3.0, 4.0);

    Vector3 c = a - b;
    EXPECT_DOUBLE_EQ(c.x, -1.0);
    EXPECT_DOUBLE_EQ(c.y, -1.0);
    EXPECT_DOUBLE_EQ(c.z, -1.0);
    CHECK_PADDING(c);
}

TEST(Vector3Test, CanBeSubtractAssigned)
{
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(2.0, 3.0, 4.0);
    b -= a;

    EXPECT_DOUBLE_EQ(b.x, 1.0);
    EXPECT_DOUBLE_EQ(b.y, 1.0);
    EXPECT_DOUBLE_EQ(b.z, 1.0);
    CHECK_PADDING(b);
}

TEST(Vector3Test, CanBeMultipled)
{
    EXPECT_EQ(Vector3(1.0) * 2.0, Vector3(2.0));
    EXPECT_EQ(Vector3(1.0, 2.0, 3.0) * 2.0, Vector3(2.0, 4.0, 6.0));
}

TEST(Vector3Test, CanBeMultiplyAssigned)
{
    Vector3 a(1.0, 2.0, 3.0);
    a *= {1.0, 0.5, 0.5};
    EXPECT_EQ(a, Vector3(1.0, 1.0, 1.5));
    a *= 2.0;
    EXPECT_EQ(a, Vector3(2.0, 2.0, 3.0));
    a *= -1.0;
    EXPECT_EQ(a, -Vector3(2.0, 2.0, 3.0));
    a *= 0.0;
    EXPECT_EQ(a, Vector3(0.0));
    CHECK_PADDING(a);
}

TEST(Vector3Test, CanBeDivided)
{
    EXPECT_EQ(Vector3(1.0) / 2.0, Vector3(0.5));
    EXPECT_EQ(Vector3(1.0, 2.0, 3.0) / 2.0, Vector3(0.5, 1.0, 1.5));
}

TEST(Vector3Test, CanBeDivideAssigned)
{
    Vector3 a(1.0, 2.0, 3.0);
    a /= {1.0, 0.5, 0.5};
    EXPECT_EQ(a, Vector3(1.0, 4.0, 6.0));
    a /= 2.0;
    EXPECT_EQ(a, Vector3(0.5, 2.0, 3.0));
    a /= -1.0;
    EXPECT_EQ(a, -Vector3(0.5, 2.0, 3.0));
    CHECK_PADDING(a);
}

TEST(Vector3Test, CanBeNegated)
{
    Vector3 a(-1.0);
    Vector3 b = -a;
    EXPECT_DOUBLE_EQ(b.x, 1.0);
    EXPECT_DOUBLE_EQ(b.y, 1.0);
    EXPECT_DOUBLE_EQ(b.z, 1.0);
    CHECK_PADDING(b);
}

TEST(Vector3Test, DoesNotChangeWithPveSign)
{
    Vector3 a(-1.0);
    Vector3 b = +a;
    EXPECT_DOUBLE_EQ(b.x, -1.0);
    EXPECT_DOUBLE_EQ(b.y, -1.0);
    EXPECT_DOUBLE_EQ(b.z, -1.0);
    CHECK_PADDING(b);
}

TEST(Vector3Test, CanComputeMagnitude)
{
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(1.0, 0.0, 0.0);
    Vector3 c(0.0, 2.0, 0.0);
    Vector3 d(0.0, 0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.Magnitude(), sqrt(14.0));
    EXPECT_DOUBLE_EQ(b.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.Magnitude(), 2.0);
    EXPECT_DOUBLE_EQ(d.Magnitude(), 3.0);
}

TEST(Vector3Test, CanComputeSquareMagnitude)
{
    Vector3 a(1.0, 2.0, 3.0);
    Vector3 b(1.0, 0.0, 0.0);
    Vector3 c(0.0, 2.0, 0.0);
    Vector3 d(0.0, 0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.SquareMagnitude(), 14.0);
    EXPECT_DOUBLE_EQ(b.SquareMagnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.SquareMagnitude(), 4.0);
    EXPECT_DOUBLE_EQ(d.SquareMagnitude(), 9.0);
}

TEST(Vector3Test, CanBeNormalized)
{
    Vector3 b(1.1, 0.0, 0.0);
    Vector3 c(0.0, 2.0, 0.0);
    Vector3 d(0.0, 0.0, -3.0);
    EXPECT_EQ(b.Normalized(), Vector3(1.0, 0.0, 0.0));
    EXPECT_EQ(c.Normalized(), Vector3(0.0, 1.0, 0.0));
    EXPECT_EQ(d.Normalized(), Vector3(0.0, 0.0, -1.0));
    EXPECT_NE(b, Vector3(1.0, 0.0, 0.0));
    EXPECT_NE(c, Vector3(0.0, 1.0, 0.0));
    EXPECT_NE(d, Vector3(0.0, 0.0, -1.0));

    b.Normalize();
    c.Normalize();
    d.Normalize();
    EXPECT_EQ(b, Vector3(1.0, 0.0, 0.0));
    EXPECT_EQ(c, Vector3(0.0, 1.0, 0.0));
    EXPECT_EQ(d, Vector3(0.0, 0.0, -1.0));

    Vector3 a(2.0, 2.0, 3.0);
    a.Normalize();
    EXPECT_DOUBLE_EQ(a.x, 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a.y, 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a.z, 0.7276068751089989);
    CHECK_PADDING(a);
    CHECK_PADDING(b);
    CHECK_PADDING(c);
    CHECK_PADDING(d);
}

TEST(Vector3Test, CanComputeDotProduct)
{
    EXPECT_DOUBLE_EQ(Vector3::Dot({ 1.0 }, { 2.0 }), 6.0);
    EXPECT_DOUBLE_EQ(Vector3::Dot({ 1.0, 2.0, 3.0 }, { 2.0, 2.0, 1.0 }), 9.0);
    EXPECT_DOUBLE_EQ(Vector3::Dot({ -1.0 }, { 2.0 }), -6.0 );
    EXPECT_DOUBLE_EQ(Vector3::Dot({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), 0.0);
    EXPECT_DOUBLE_EQ(Vector3::AbsDot({ -1.0 }, { 2.0 }), 6.0);
    EXPECT_DOUBLE_EQ(Vector3::AbsDot({ 1.0 }, { 2.0 }), 6.0);
}

TEST(Vector3Test, CanComputeAngle)
{
    double d = Vector3::Angle({ 1.0 }, { 1.0 });
    EXPECT_DOUBLE_EQ(Vector3::Angle({ 1.0 }, { 1.0 }), 0.0);
    EXPECT_DOUBLE_EQ(Vector3::Angle({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), 1.5707963267948966);
    EXPECT_DOUBLE_EQ(Vector3::Angle({ 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0 }), 0.1304771607247695);
}

TEST(Vector3Test, CanComputeCrossProduct)
{
    EXPECT_EQ(Vector3::Cross({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), Vector3(0.0, 0.0, 1.0));
    EXPECT_EQ(Vector3::Cross({ 1.0, 2.0, 3.0 }, { 2.0, 1.0, 0.0 }), Vector3(-3.0, 6.0, -3.0));
    EXPECT_EQ(Vector3::Cross({ -1.0, 2.0, 3.0 }, { 5.0, 1.0, 4.0 }), Vector3(5.0, 19.0, -11.0));
}

