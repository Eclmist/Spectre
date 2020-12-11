/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
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

#include "googletest/gtest.h"
#include "math/vector.h"

TEST(VectorTest, CanBeCreated)
{
    ASSERT_NO_THROW(Vector4 v);
}

TEST(VectorTest, DefaultsToZeroVector)
{
    Vector4 v;
    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
    EXPECT_DOUBLE_EQ(v.z(), 0.0);
    EXPECT_DOUBLE_EQ(v.w(), 0.0);
}

TEST(VectorTest, CanBeCreatedScalar)
{
    Vector4 v(22.0);
    EXPECT_DOUBLE_EQ(v.x(), 22.0);
    EXPECT_DOUBLE_EQ(v.y(), 22.0);
    EXPECT_DOUBLE_EQ(v.z(), 22.0);
    EXPECT_DOUBLE_EQ(v.w(), 22.0);
}

TEST(VectorTest, CanBeCreatedPerComponent)
{
    Vector4 v(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
    EXPECT_DOUBLE_EQ(v.w(), 4.0);
}

TEST(VectorTest, CanBeSetPerComponents)
{
    Vector4 v;
    v.x(1.0);
    v.y(2.0);
    v.z(3.0);
    v.w(4.0);

    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
    EXPECT_DOUBLE_EQ(v.w(), 4.0);
}

TEST(VectorTest, CanBeCopyConstructed)
{
    Vector4 a(22.0);
    Vector4 b(a);

    EXPECT_DOUBLE_EQ(b.x(), 22.0);
    EXPECT_DOUBLE_EQ(b.y(), 22.0);
    EXPECT_DOUBLE_EQ(b.z(), 22.0);
    EXPECT_DOUBLE_EQ(b.w(), 22.0);

    b.x(0.0);
    EXPECT_DOUBLE_EQ(a.x(), 22.0);
}

TEST(VectorTest, CanBeCopied)
{
    Vector4 a(22.0);
    Vector4 b = a;

    EXPECT_DOUBLE_EQ(b.x(), 22.0);
    EXPECT_DOUBLE_EQ(b.y(), 22.0);
    EXPECT_DOUBLE_EQ(b.z(), 22.0);
    EXPECT_DOUBLE_EQ(b.w(), 22.0);

    b.x(0.0);
    EXPECT_DOUBLE_EQ(a.x(), 22.0);
}

TEST(VectorTest, CanBeAdded)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);

    Vector4 c = a + b;
    EXPECT_DOUBLE_EQ(c.x(), 3.0);
    EXPECT_DOUBLE_EQ(c.y(), 5.0);
    EXPECT_DOUBLE_EQ(c.z(), 7.0);
    EXPECT_DOUBLE_EQ(c.w(), 9.0);
}

TEST(VectorTest, CanBeAddAssigned)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);
    b += a;

    EXPECT_DOUBLE_EQ(b.x(), 3.0);
    EXPECT_DOUBLE_EQ(b.y(), 5.0);
    EXPECT_DOUBLE_EQ(b.z(), 7.0);
    EXPECT_DOUBLE_EQ(b.w(), 9.0);
}

TEST(VectorTest, CanBeSubtracted)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);

    Vector4 c = a - b;
    EXPECT_DOUBLE_EQ(c.x(), -1.0);
    EXPECT_DOUBLE_EQ(c.y(), -1.0);
    EXPECT_DOUBLE_EQ(c.z(), -1.0);
    EXPECT_DOUBLE_EQ(c.w(), -1.0);
}

TEST(VectorTest, CanBeSubtractAssigned)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);
    b -= a;

    EXPECT_DOUBLE_EQ(b.x(), 1.0);
    EXPECT_DOUBLE_EQ(b.y(), 1.0);
    EXPECT_DOUBLE_EQ(b.z(), 1.0);
    EXPECT_DOUBLE_EQ(b.w(), 1.0);
}

TEST(VectorTest, CanBeNegated)
{
    Vector4 a(-1.0);
    Vector4 b = -a;
    EXPECT_DOUBLE_EQ(b.x(), 1.0);
    EXPECT_DOUBLE_EQ(b.y(), 1.0);
    EXPECT_DOUBLE_EQ(b.z(), 1.0);
    EXPECT_DOUBLE_EQ(b.w(), 1.0);
}

TEST(VectorTest, DoesNotChangeWithPveSign)
{
    Vector4 a(-1.0);
    Vector4 b = +a;
    EXPECT_DOUBLE_EQ(b.x(), -1.0);
    EXPECT_DOUBLE_EQ(b.y(), -1.0);
    EXPECT_DOUBLE_EQ(b.z(), -1.0);
    EXPECT_DOUBLE_EQ(b.w(), -1.0);
}


