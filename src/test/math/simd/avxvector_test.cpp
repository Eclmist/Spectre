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
#include <stdexcept>

TEST(AvxVectorTest, CanBeCreated)
{
    ASSERT_NO_THROW(AvxVector v);
}

TEST(AvxVectorTest, DefaultsToZeroVector)
{
    AvxVector v;
    EXPECT_DOUBLE_EQ(v.x, 0);
    EXPECT_DOUBLE_EQ(v.y, 0);
    EXPECT_DOUBLE_EQ(v.z, 0);
    EXPECT_DOUBLE_EQ(v.w, 0);
}

TEST(AvxVectorTest, CanBeCreatedScalar)
{
    AvxVector v(22);
    EXPECT_DOUBLE_EQ(v.x, 22);
    EXPECT_DOUBLE_EQ(v.y, 22);
    EXPECT_DOUBLE_EQ(v.z, 22);
    EXPECT_DOUBLE_EQ(v.w, 22);
}

TEST(AvxVectorTest, CanBeCreatedPerComponent)
{
    AvxVector v(1, 2, 3, 4);
    EXPECT_DOUBLE_EQ(v.x, 1);
    EXPECT_DOUBLE_EQ(v.y, 2);
    EXPECT_DOUBLE_EQ(v.z, 3);
    EXPECT_DOUBLE_EQ(v.w, 4);

    AvxVector u(1, 2);
    EXPECT_DOUBLE_EQ(u.x, 1);
    EXPECT_DOUBLE_EQ(u.y, 2);
    EXPECT_DOUBLE_EQ(u.z, 0);
    EXPECT_DOUBLE_EQ(u.w, 0);

    AvxVector w(1, 2, 3);
    EXPECT_DOUBLE_EQ(w.x, 1);
    EXPECT_DOUBLE_EQ(w.y, 2);
    EXPECT_DOUBLE_EQ(w.z, 3);
    EXPECT_DOUBLE_EQ(w.w, 0);
}

TEST(AvxVectorTest, CanBeSetPerComponents)
{
    AvxVector v;
    v.x = 1;
    v.y = 2;
    v.z = 3;
    v.w = 4;

    EXPECT_DOUBLE_EQ(v.x, 1);
    EXPECT_DOUBLE_EQ(v.y, 2);
    EXPECT_DOUBLE_EQ(v.z, 3);
    EXPECT_DOUBLE_EQ(v.w, 4);
}

TEST(AvxVectorTest, CanBeAccessedPerComponent)
{
    AvxVector v(1, 2, 3, 4);

    EXPECT_DOUBLE_EQ(v.x, 1);
    EXPECT_DOUBLE_EQ(v.y, 2);
    EXPECT_DOUBLE_EQ(v.z, 3);
    EXPECT_DOUBLE_EQ(v.w, 4);
    EXPECT_DOUBLE_EQ(v[0], 1);
    EXPECT_DOUBLE_EQ(v[1], 2);
    EXPECT_DOUBLE_EQ(v[2], 3);
    EXPECT_DOUBLE_EQ(v[3], 4);
}

TEST(AvxVectorTest, CanBeCopyConstructed)
{
    AvxVector a(22);
    AvxVector b(a);

    EXPECT_DOUBLE_EQ(b.x, 22);
    EXPECT_DOUBLE_EQ(b.y, 22);
    EXPECT_DOUBLE_EQ(b.z, 22);
    EXPECT_DOUBLE_EQ(b.w, 22);

    b.x = 0;
    EXPECT_DOUBLE_EQ(a.x, 22);
}

TEST(AvxVectorTest, CanBeCopied)
{
    AvxVector a(22);
    AvxVector b = a;

    EXPECT_DOUBLE_EQ(b.x, 22);
    EXPECT_DOUBLE_EQ(b.y, 22);
    EXPECT_DOUBLE_EQ(b.z, 22);
    EXPECT_DOUBLE_EQ(b.w, 22);

    b.x = 0;
    EXPECT_DOUBLE_EQ(a.x, 22);
}

TEST(AvxVectorTest, CanBeAdded)
{
    AvxVector a(1, 2, 3, 4);
    AvxVector b(2, 3, 4, 5);

    AvxVector c = a + b;
    EXPECT_DOUBLE_EQ(c.x, 3);
    EXPECT_DOUBLE_EQ(c.y, 5);
    EXPECT_DOUBLE_EQ(c.z, 7);
    EXPECT_DOUBLE_EQ(c.w, 9);
}

TEST(AvxVectorTest, CanBeAddAssigned)
{
    AvxVector a(1, 2, 3, 4);
    AvxVector b(2, 3, 4, 5);
    b += a;

    EXPECT_DOUBLE_EQ(b.x, 3);
    EXPECT_DOUBLE_EQ(b.y, 5);
    EXPECT_DOUBLE_EQ(b.z, 7);
    EXPECT_DOUBLE_EQ(b.w, 9);
}

TEST(AvxVectorTest, CanBeSubtracted)
{
    AvxVector a(1, 2, 3, 4);
    AvxVector b(2, 3, 4, 5);

    AvxVector c = a - b;
    EXPECT_DOUBLE_EQ(c.x, -1);
    EXPECT_DOUBLE_EQ(c.y, -1);
    EXPECT_DOUBLE_EQ(c.z, -1);
    EXPECT_DOUBLE_EQ(c.w, -1);
}

TEST(AvxVectorTest, CanBeSubtractAssigned)
{
    AvxVector a(1, 2, 3, 4);
    AvxVector b(2, 3, 4, 5);
    b -= a;

    EXPECT_DOUBLE_EQ(b.x, 1);
    EXPECT_DOUBLE_EQ(b.y, 1);
    EXPECT_DOUBLE_EQ(b.z, 1);
    EXPECT_DOUBLE_EQ(b.w, 1);
}

TEST(AvxVectorTest, CanBeNegated)
{
    AvxVector a(-1);
    AvxVector b = -a;
    EXPECT_DOUBLE_EQ(b.x, 1);
    EXPECT_DOUBLE_EQ(b.y, 1);
    EXPECT_DOUBLE_EQ(b.z, 1);
    EXPECT_DOUBLE_EQ(b.w, 1);
}

TEST(AvxVectorTest, DoesNotChangeWithPveSign)
{
    AvxVector a(-1);
    AvxVector b = +a;
    EXPECT_DOUBLE_EQ(b.x, -1);
    EXPECT_DOUBLE_EQ(b.y, -1);
    EXPECT_DOUBLE_EQ(b.z, -1);
    EXPECT_DOUBLE_EQ(b.w, -1);
}

TEST(AvxVectorTest, CanComputeMagnitude)
{
    AvxVector a(1, 2, 3);
    AvxVector b(1, 0, 0);
    AvxVector c(0, 2, 0);
    AvxVector d(0, 0, 3);

    EXPECT_DOUBLE_EQ(a.Magnitude(), sqrt(14));
    EXPECT_DOUBLE_EQ(b.Magnitude(), 1);
    EXPECT_DOUBLE_EQ(c.Magnitude(), 2);
    EXPECT_DOUBLE_EQ(d.Magnitude(), 3);
}

TEST(AvxVectorTest, CanComputeSquareMagnitude)
{
    AvxVector a(1, 2, 3);
    AvxVector b(1, 0, 0);
    AvxVector c(0, 2, 0);
    AvxVector d(0, 0, 3);

    EXPECT_DOUBLE_EQ(a.MagnitudeSquared(), 14);
    EXPECT_DOUBLE_EQ(b.MagnitudeSquared(), 1);
    EXPECT_DOUBLE_EQ(c.MagnitudeSquared(), 4);
    EXPECT_DOUBLE_EQ(d.MagnitudeSquared(), 9);
}

TEST(AvxVectorTest, DefaultUnitVectorsHaveUnitLength)
{
    EXPECT_DOUBLE_EQ(AvxVector::Up().MagnitudeSquared(), 1);
    EXPECT_DOUBLE_EQ(AvxVector::Right().MagnitudeSquared(), 1);
    EXPECT_DOUBLE_EQ(AvxVector::Forward().MagnitudeSquared(), 1);
}

TEST(AvxVectorTest, DefaultZeroVectorHaveZeroLength)
{
    EXPECT_DOUBLE_EQ(AvxVector::Zero().MagnitudeSquared(), 0);
}

TEST(AvxVectorTest, CanCheckEquality)
{
    EXPECT_EQ(AvxVector(1), AvxVector(1));
    EXPECT_EQ(AvxVector(0.2), AvxVector(0.2));
    EXPECT_EQ(AvxVector(1, 2, 3, 4), AvxVector(1, 2, 3, 4));
    EXPECT_NE(AvxVector(0), AvxVector(1));
    EXPECT_NE(AvxVector(0), AvxVector(0.00001));
    EXPECT_NE(AvxVector(0, 1, 2, 3), AvxVector(0, 1, 2.1, 3));
}

TEST(AvxVectorTest, CanBeScaled)
{
    EXPECT_EQ(AvxVector(1) * 2, AvxVector(2));
    EXPECT_EQ(AvxVector(1, 2, 3, 4) * 2, AvxVector(2, 4, 6, 8));
}

TEST(AvxVectorTest, CanBeScaleAssigned)
{
    AvxVector a(1, 2, 3, 4);
    a *= {1, 0.5, 0.5, 2};
    EXPECT_EQ(a, AvxVector(1, 1, 1.5, 8));
    a *= 2;
    EXPECT_EQ(a, AvxVector(2, 2, 3, 16));
    a *= -1;
    EXPECT_EQ(a, -AvxVector(2, 2, 3, 16));
    a *= 0;
    EXPECT_EQ(a, AvxVector(0));
}

TEST(AvxVectorTest, CanBeNormalized)
{
    AvxVector b(1.1, 0, 0);
    AvxVector c(0, 2, 0);
    AvxVector d(0, 0, 3);
    EXPECT_EQ(b.Normalized(), AvxVector(1, 0, 0));
    EXPECT_EQ(c.Normalized(), AvxVector(0, 1, 0));
    EXPECT_EQ(d.Normalized(), AvxVector(0, 0, 1));
    EXPECT_NE(b, AvxVector(1, 0, 0));
    EXPECT_NE(c, AvxVector(0, 1, 0));
    EXPECT_NE(d, AvxVector(0, 0, 1));

    b.Normalize();
    c.Normalize();
    d.Normalize();
    EXPECT_EQ(b, AvxVector(1, 0, 0));
    EXPECT_EQ(c, AvxVector(0, 1, 0));
    EXPECT_EQ(d, AvxVector(0, 0, 1));

    AvxVector a(2, 2, 3);
    a.Normalize();
    EXPECT_DOUBLE_EQ(a.x, 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a.y, 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a.z, 0.7276068751089989);
    EXPECT_DOUBLE_EQ(a.w, 0.0);
}

TEST(AvxVectorTest, CanComputeDotProduct)
{
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ 1 }, { 2 }), 8);
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ 1, 2, 3, 4 }, { 2, 2, 1, 4 }), 25);
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ -1 }, { 2 }), -8);
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ 1, 0, 0 }, { 0, 1, 0 }), 0);
    EXPECT_DOUBLE_EQ(AvxVector::AbsDot({ -1 }, { 2 }), 8);
    EXPECT_DOUBLE_EQ(AvxVector::AbsDot({ 1 }, { 2 }), 8);
}

TEST(AvxVectorTest, CanComputeAngle)
{
    EXPECT_DOUBLE_EQ(AvxVector::Angle({ 1 }, { 1 }), 0);
    EXPECT_DOUBLE_EQ(AvxVector::Angle({ 1, 0, 0 }, { 0, 1, 0 }), 1.5707963267948966);
    EXPECT_DOUBLE_EQ(AvxVector::Angle({ 2, 3, 4 }, { 5, 6, 7 }), 0.1304771607247695);
}

TEST(AvxVectorTest, CanComputeCrossProduct)
{
    EXPECT_THROW(AvxVector::Cross({ 1 }, {1, 2, 3, 0}), std::invalid_argument);
    EXPECT_THROW(AvxVector::Cross({ 1, 2, 3, 0 }, { 1 }), std::invalid_argument);
    EXPECT_THROW(AvxVector::Cross({ 1 }, { 1 }), std::invalid_argument);

    EXPECT_EQ(AvxVector::Cross({ 1, 0, 0 }, { 0, 1, 0 }), AvxVector(0, 0, 1));
    EXPECT_EQ(AvxVector::Cross({ 1, 2, 3 }, { 2, 1, 0 }), AvxVector(-3, 6, -3));
    EXPECT_EQ(AvxVector::Cross({ -1, 2, 3 }, { 5, 1, 4 }), AvxVector(5, 19, -11));
}

