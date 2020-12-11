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
#include "math/simd/avxvector.h"

TEST(AvxVectorTest, CanBeCreated)
{
    ASSERT_NO_THROW(AvxVector v);
}

TEST(AvxVectorTest, DefaultsToZeroVector)
{
    AvxVector v;
    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
    EXPECT_DOUBLE_EQ(v.z(), 0.0);
    EXPECT_DOUBLE_EQ(v.w(), 0.0);
}

TEST(AvxVectorTest, CanBeCreatedScalar)
{
    AvxVector v(22.0);
    EXPECT_DOUBLE_EQ(v.x(), 22.0);
    EXPECT_DOUBLE_EQ(v.y(), 22.0);
    EXPECT_DOUBLE_EQ(v.z(), 22.0);
    EXPECT_DOUBLE_EQ(v.w(), 22.0);
}

TEST(AvxVectorTest, CanBeCreatedPerComponent)
{
    AvxVector v(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
    EXPECT_DOUBLE_EQ(v.w(), 4.0);
}

TEST(AvxVectorTest, CanBeSetPerComponents)
{
    AvxVector v;
    v.x(1.0);
    v.y(2.0);
    v.z(3.0);
    v.w(4.0);

    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
    EXPECT_DOUBLE_EQ(v.w(), 4.0);
}

TEST(AvxVectorTest, CanBeAccessedPerComponent)
{
    AvxVector v(1.0, 2.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
    EXPECT_DOUBLE_EQ(v.w(), 4.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(AvxVectorTest, CanBeCopyConstructed)
{
    AvxVector a(22.0);
    AvxVector b(a);

    EXPECT_DOUBLE_EQ(b.x(), 22.0);
    EXPECT_DOUBLE_EQ(b.y(), 22.0);
    EXPECT_DOUBLE_EQ(b.z(), 22.0);
    EXPECT_DOUBLE_EQ(b.w(), 22.0);

    b.x(0.0);
    EXPECT_DOUBLE_EQ(a.x(), 22.0);
}

TEST(AvxVectorTest, CanBeCopied)
{
    AvxVector a(22.0);
    AvxVector b = a;

    EXPECT_DOUBLE_EQ(b.x(), 22.0);
    EXPECT_DOUBLE_EQ(b.y(), 22.0);
    EXPECT_DOUBLE_EQ(b.z(), 22.0);
    EXPECT_DOUBLE_EQ(b.w(), 22.0);

    b.x(0.0);
    EXPECT_DOUBLE_EQ(a.x(), 22.0);
}

TEST(AvxVectorTest, CanBeAdded)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);

    AvxVector c = a + b;
    EXPECT_DOUBLE_EQ(c.x(), 3.0);
    EXPECT_DOUBLE_EQ(c.y(), 5.0);
    EXPECT_DOUBLE_EQ(c.z(), 7.0);
    EXPECT_DOUBLE_EQ(c.w(), 9.0);
}

TEST(AvxVectorTest, CanBeAddAssigned)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);
    b += a;

    EXPECT_DOUBLE_EQ(b.x(), 3.0);
    EXPECT_DOUBLE_EQ(b.y(), 5.0);
    EXPECT_DOUBLE_EQ(b.z(), 7.0);
    EXPECT_DOUBLE_EQ(b.w(), 9.0);
}

TEST(AvxVectorTest, CanBeSubtracted)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);

    AvxVector c = a - b;
    EXPECT_DOUBLE_EQ(c.x(), -1.0);
    EXPECT_DOUBLE_EQ(c.y(), -1.0);
    EXPECT_DOUBLE_EQ(c.z(), -1.0);
    EXPECT_DOUBLE_EQ(c.w(), -1.0);
}

TEST(AvxVectorTest, CanBeSubtractAssigned)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);
    b -= a;

    EXPECT_DOUBLE_EQ(b.x(), 1.0);
    EXPECT_DOUBLE_EQ(b.y(), 1.0);
    EXPECT_DOUBLE_EQ(b.z(), 1.0);
    EXPECT_DOUBLE_EQ(b.w(), 1.0);
}

TEST(AvxVectorTest, CanBeNegated)
{
    AvxVector a(-1.0);
    AvxVector b = -a;
    EXPECT_DOUBLE_EQ(b.x(), 1.0);
    EXPECT_DOUBLE_EQ(b.y(), 1.0);
    EXPECT_DOUBLE_EQ(b.z(), 1.0);
    EXPECT_DOUBLE_EQ(b.w(), 1.0);
}

TEST(AvxVectorTest, DoesNotChangeWithPveSign)
{
    AvxVector a(-1.0);
    AvxVector b = +a;
    EXPECT_DOUBLE_EQ(b.x(), -1.0);
    EXPECT_DOUBLE_EQ(b.y(), -1.0);
    EXPECT_DOUBLE_EQ(b.z(), -1.0);
    EXPECT_DOUBLE_EQ(b.w(), -1.0);
}

TEST(AvxVectorTest, CanComputeMagnitude)
{
    AvxVector a(1.0, 2.0, 3.0, 0.0);
    AvxVector b(1.0, 0.0, 0.0, 0.0);
    AvxVector c(0.0, 2.0, 0.0, 0.0);
    AvxVector d(0.0, 0.0, 3.0, 0.0);

    EXPECT_DOUBLE_EQ(a.Magnitude(), sqrt(14.0));
    EXPECT_DOUBLE_EQ(b.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.Magnitude(), 2.0);
    EXPECT_DOUBLE_EQ(d.Magnitude(), 3.0);
}

TEST(AvxVectorTest, CanComputeSquareMagnitude)
{
    AvxVector a(1.0, 2.0, 3.0, 0.0);
    AvxVector b(1.0, 0.0, 0.0, 0.0);
    AvxVector c(0.0, 2.0, 0.0, 0.0);
    AvxVector d(0.0, 0.0, 3.0, 0.0);

    EXPECT_DOUBLE_EQ(a.MagnitudeSquared(), 14.0);
    EXPECT_DOUBLE_EQ(b.MagnitudeSquared(), 1.0);
    EXPECT_DOUBLE_EQ(c.MagnitudeSquared(), 4.0);
    EXPECT_DOUBLE_EQ(d.MagnitudeSquared(), 9.0);
}

TEST(AvxVectorTest, DefaultUnitVectorsHaveUnitLength)
{
    EXPECT_DOUBLE_EQ(AvxVector::Up().MagnitudeSquared(), 1.0);
    EXPECT_DOUBLE_EQ(AvxVector::Right().MagnitudeSquared(), 1.0);
    EXPECT_DOUBLE_EQ(AvxVector::Forward().MagnitudeSquared(), 1.0);
}

TEST(AvxVectorTest, DefaultZeroVectorHaveZeroLength)
{
    EXPECT_DOUBLE_EQ(AvxVector::Zero().MagnitudeSquared(), 0.0);
    EXPECT_DOUBLE_EQ(AvxVector::Zero().MagnitudeSquared(), AvxVector().MagnitudeSquared());
}

