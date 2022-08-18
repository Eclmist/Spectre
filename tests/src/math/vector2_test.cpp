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
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest.h"
#include "math/vector.h"

TEST(Vector2Test, CanBeCreated)
{
    ASSERT_NO_THROW(Vector2 v);
}

TEST(Vector2Test, DefaultsToZeroVector)
{
    Vector2 v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
}

TEST(Vector2Test, CanBeCreatedScalar)
{
    Vector2 v(22.0);
    EXPECT_DOUBLE_EQ(v.x, 22.0);
    EXPECT_DOUBLE_EQ(v.y, 22.0);
}

TEST(Vector2Test, CanBeCreatedPerComponent)
{
    Vector2 v(1.0, 2.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
}

TEST(Vector2Test, CanBeSetPerComponents)
{
    Vector2 v;
    v.x = 1.0;
    v.y = 2.0;

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
}

TEST(Vector2Test, CanBeAccessedPerComponent)
{
    Vector2 v(1.0, 2.0);

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
}

TEST(Vector2Test, CanBeCopyConstructed)
{
    Vector2 a(22.0);
    Vector2 b(a);

    EXPECT_DOUBLE_EQ(b.x, 22.0);
    EXPECT_DOUBLE_EQ(b.y, 22.0);

    b.x = 0.0;
    EXPECT_DOUBLE_EQ(a.x, 22.0);
}

TEST(Vector2Test, CanBeCopied)
{
    Vector2 a(22.0);
    Vector2 b = a;

    EXPECT_DOUBLE_EQ(b.x, 22.0);
    EXPECT_DOUBLE_EQ(b.y, 22.0);

    b.x = 0.0;
    EXPECT_DOUBLE_EQ(a.x, 22.0);
}

TEST(Vector2Test, CanCheckEquality)
{
    EXPECT_EQ(Vector2(1.0), Vector2(1.0));
    EXPECT_EQ(Vector2(0.2), Vector2(0.2));
    EXPECT_EQ(Vector2(1.0, 2.0), Vector2(1.0, 2.0));
    EXPECT_NE(Vector2(0.0), Vector2(1.0));
    EXPECT_NE(Vector2(0.0), Vector2(0.00001));
    EXPECT_NE(Vector2(0.0, 1.0), Vector2(0.1, 1.0));
}

TEST(Vector2Test, CanBeAdded)
{
    Vector2 a(1.0, 2.0);
    Vector2 b(2.0, 3.0);

    Vector2 c = a + b;
    EXPECT_DOUBLE_EQ(c.x, 3.0);
    EXPECT_DOUBLE_EQ(c.y, 5.0);
}

TEST(Vector2Test, CanBeAddAssigned)
{
    Vector2 a(1.0, 2.0);
    Vector2 b(2.0, 3.0);
    b += a;

    EXPECT_DOUBLE_EQ(b.x, 3.0);
    EXPECT_DOUBLE_EQ(b.y, 5.0);
}

TEST(Vector2Test, CanBeSubtracted)
{
    Vector2 a(1.0, 2.0);
    Vector2 b(2.0, 3.0);

    Vector2 c = a - b;
    EXPECT_DOUBLE_EQ(c.x, -1.0);
    EXPECT_DOUBLE_EQ(c.y, -1.0);
}

TEST(Vector2Test, CanBeSubtractAssigned)
{
    Vector2 a(1.0, 2.0);
    Vector2 b(2.0, 3.0);
    b -= a;

    EXPECT_DOUBLE_EQ(b.x, 1.0);
    EXPECT_DOUBLE_EQ(b.y, 1.0);
}

TEST(Vector2Test, CanBeMultipled)
{
    EXPECT_EQ(Vector2(1.0) * 2.0, Vector2(2.0));
    EXPECT_EQ(Vector2(1.0, 2.0) * 2.0, Vector2(2.0, 4.0));
}

TEST(Vector2Test, CanBeMultiplyAssigned)
{
    Vector2 a(1.0, 2.0);
    a *= {1.0, 0.5};
    EXPECT_EQ(a, Vector2(1.0, 1.0));
    a *= 2.0;
    EXPECT_EQ(a, Vector2(2.0, 2.0));
    a *= -1.0;
    EXPECT_EQ(a, -Vector2(2.0, 2.0));
    a *= 0.0;
    EXPECT_EQ(a, Vector2(0.0));
}

TEST(Vector2Test, CanBeDivided)
{
    EXPECT_EQ(Vector2(1.0) / 2.0, Vector2(0.5));
    EXPECT_EQ(Vector2(1.0, 2.0) / 2.0, Vector2(0.5, 1.0));
}

TEST(Vector2Test, CanBeDivideAssigned)
{
    Vector2 a(1.0, 2.0);
    a /= {1.0, 0.5};
    EXPECT_EQ(a, Vector2(1.0, 4.0));
    a /= 2.0;
    EXPECT_EQ(a, Vector2(0.5, 2.0));
    a /= -1.0;
    EXPECT_EQ(a, -Vector2(0.5, 2.0));
}

TEST(Vector2Test, CanBeNegated)
{
    Vector2 a(-1.0);
    Vector2 b = -a;
    EXPECT_DOUBLE_EQ(b.x, 1.0);
    EXPECT_DOUBLE_EQ(b.y, 1.0);
}

TEST(Vector2Test, DoesNotChangeWithPveSign)
{
    Vector2 a(-1.0);
    Vector2 b = +a;
    EXPECT_DOUBLE_EQ(b.x, -1.0);
    EXPECT_DOUBLE_EQ(b.y, -1.0);
}

TEST(Vector2Test, CanComputeMagnitude)
{
    Vector2 a(1.0, 2.0);
    Vector2 b(1.0, 0.0);
    Vector2 c(0.0, 2.0);
    Vector2 d(0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.Magnitude(), std::sqrt(5.0));
    EXPECT_DOUBLE_EQ(b.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.Magnitude(), 2.0);
    EXPECT_DOUBLE_EQ(d.Magnitude(), 3.0);
}

TEST(Vector2Test, CanComputeSquareMagnitude)
{
    Vector2 a(1.0, 2.0);
    Vector2 b(1.0, 0.0);
    Vector2 c(0.0, 2.0);
    Vector2 d(0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.SquareMagnitude(), 5.0);
    EXPECT_DOUBLE_EQ(b.SquareMagnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.SquareMagnitude(), 4.0);
    EXPECT_DOUBLE_EQ(d.SquareMagnitude(), 9.0);
}

TEST(Vector2Test, CanBeNormalized)
{
    Vector2 b(1.1, 0.0);
    Vector2 c(0.0, 2.0);
    EXPECT_EQ(b.Normalized(), Vector2(1.0, 0.0));
    EXPECT_EQ(c.Normalized(), Vector2(0.0, 1.0));
    EXPECT_NE(b, Vector2(1.0, 0.0));
    EXPECT_NE(c, Vector2(0.0, 1.0));

    b.Normalize();
    c.Normalize();
    EXPECT_EQ(b, Vector2(1.0, 0.0));
    EXPECT_EQ(c, Vector2(0.0, 1.0));

    Vector2 a(2.0, 2.0);
    a.Normalize();
    EXPECT_DOUBLE_EQ(a.x, 0.70710678118654746);
    EXPECT_DOUBLE_EQ(a.y, 0.70710678118654746);
}

TEST(Vector2Test, CanComputeDotProduct)
{
    EXPECT_DOUBLE_EQ(Vector2::Dot({ 1.0 }, { 2.0 }), 4.0);
    EXPECT_DOUBLE_EQ(Vector2::Dot({ 1.0, 2.0 }, { 2.0, 2.0 }), 6.0);
    EXPECT_DOUBLE_EQ(Vector2::Dot({ -1.0 }, { 2.0 }), -4.0 );
    EXPECT_DOUBLE_EQ(Vector2::Dot({ 1.0, 0.0 }, { 0.0, 1.0 }), 0.0);
    EXPECT_DOUBLE_EQ(Vector2::AbsDot({ -1.0 }, { 2.0 }), 4.0);
    EXPECT_DOUBLE_EQ(Vector2::AbsDot({ 1.0 }, { 2.0 }), 4.0);
}

