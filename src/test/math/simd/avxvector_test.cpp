/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.
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
    EXPECT_DOUBLE_EQ(v[0], 0.0);
    EXPECT_DOUBLE_EQ(v[1], 0.0);
    EXPECT_DOUBLE_EQ(v[2], 0.0);
    EXPECT_DOUBLE_EQ(v[3], 0.0);
}

TEST(AvxVectorTest, CanBeCreatedScalar)
{
    AvxVector v(22.0);
    EXPECT_DOUBLE_EQ(v[0], 22.0);
    EXPECT_DOUBLE_EQ(v[1], 22.0);
    EXPECT_DOUBLE_EQ(v[2], 22.0);
    EXPECT_DOUBLE_EQ(v[3], 22.0);
}

TEST(AvxVectorTest, CanBeCreatedPerComponent)
{
    AvxVector v(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);

    AvxVector u(1.0, 2.0);
    EXPECT_DOUBLE_EQ(u[0], 1.0);
    EXPECT_DOUBLE_EQ(u[1], 2.0);
    EXPECT_DOUBLE_EQ(u[2], 0.0);
    EXPECT_DOUBLE_EQ(u[3], 0.0);

    AvxVector w(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(w[0], 1.0);
    EXPECT_DOUBLE_EQ(w[1], 2.0);
    EXPECT_DOUBLE_EQ(w[2], 3.0);
    EXPECT_DOUBLE_EQ(w[3], 0.0);
}

TEST(AvxVectorTest, CanBeSetPerComponents)
{
    AvxVector v;
    v[0] = 1.0;
    v[1] = 2.0;
    v[2] = 3.0;
    v[3] = 4.0;

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(AvxVectorTest, CanBeAccessedPerComponent)
{
    AvxVector v(1.0, 2.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(AvxVectorTest, CanBeCopyConstructed)
{
    AvxVector a(22.0);
    AvxVector b(a);

    EXPECT_DOUBLE_EQ(b[0], 22.0);
    EXPECT_DOUBLE_EQ(b[1], 22.0);
    EXPECT_DOUBLE_EQ(b[2], 22.0);
    EXPECT_DOUBLE_EQ(b[3], 22.0);

    b[0] = 0.0;
    EXPECT_DOUBLE_EQ(a[0], 22.0);
}

TEST(AvxVectorTest, CanBeCopied)
{
    AvxVector a(22.0);
    AvxVector b = a;

    EXPECT_DOUBLE_EQ(b[0], 22.0);
    EXPECT_DOUBLE_EQ(b[1], 22.0);
    EXPECT_DOUBLE_EQ(b[2], 22.0);
    EXPECT_DOUBLE_EQ(b[3], 22.0);

    b[0] = 0.0;
    EXPECT_DOUBLE_EQ(a[0], 22.0);
}

TEST(AvxVectorTest, CanBeAdded)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);

    AvxVector c = a + b;
    EXPECT_DOUBLE_EQ(c[0], 3.0);
    EXPECT_DOUBLE_EQ(c[1], 5.0);
    EXPECT_DOUBLE_EQ(c[2], 7.0);
    EXPECT_DOUBLE_EQ(c[3], 9.0);
}

TEST(AvxVectorTest, CanBeAddAssigned)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);
    b += a;

    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 5.0);
    EXPECT_DOUBLE_EQ(b[2], 7.0);
    EXPECT_DOUBLE_EQ(b[3], 9.0);
}

TEST(AvxVectorTest, CanBeSubtracted)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);

    AvxVector c = a - b;
    EXPECT_DOUBLE_EQ(c[0], -1.0);
    EXPECT_DOUBLE_EQ(c[1], -1.0);
    EXPECT_DOUBLE_EQ(c[2], -1.0);
    EXPECT_DOUBLE_EQ(c[3], -1.0);
}

TEST(AvxVectorTest, CanBeSubtractAssigned)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    AvxVector b(2.0, 3.0, 4.0, 5.0);
    b -= a;

    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 1.0);
    EXPECT_DOUBLE_EQ(b[3], 1.0);
}

TEST(AvxVectorTest, CanBeNegated)
{
    AvxVector a(-1.0);
    AvxVector b = -a;
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 1.0);
    EXPECT_DOUBLE_EQ(b[3], 1.0);
}

TEST(AvxVectorTest, DoesNotChangeWithPveSign)
{
    AvxVector a(-1.0);
    AvxVector b = +a;
    EXPECT_DOUBLE_EQ(b[0], -1.0);
    EXPECT_DOUBLE_EQ(b[1], -1.0);
    EXPECT_DOUBLE_EQ(b[2], -1.0);
    EXPECT_DOUBLE_EQ(b[3], -1.0);
}

TEST(AvxVectorTest, CanComputeMagnitude)
{
    AvxVector a(1.0, 2.0, 3.0);
    AvxVector b(1.0, 0.0, 0.0);
    AvxVector c(0.0, 2.0, 0.0);
    AvxVector d(0.0, 0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.Magnitude(), sqrt(14.0));
    EXPECT_DOUBLE_EQ(b.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.Magnitude(), 2.0);
    EXPECT_DOUBLE_EQ(d.Magnitude(), 3.0);
}

TEST(AvxVectorTest, CanComputeSquareMagnitude)
{
    AvxVector a(1.0, 2.0, 3.0);
    AvxVector b(1.0, 0.0, 0.0);
    AvxVector c(0.0, 2.0, 0.0);
    AvxVector d(0.0, 0.0, 3.0);

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
}

TEST(AvxVectorTest, CanCheckEquality)
{
    EXPECT_EQ(AvxVector(1.0), AvxVector(1.0));
    EXPECT_EQ(AvxVector(0.2), AvxVector(0.2));
    EXPECT_EQ(AvxVector(1.0, 2.0, 3.0, 4.0), AvxVector(1.0, 2.0, 3.0, 4.0));
    EXPECT_NE(AvxVector(0.0), AvxVector(1.0));
    EXPECT_NE(AvxVector(0.0), AvxVector(0.00001));
    EXPECT_NE(AvxVector(0.0, 1.0, 2.0, 3.0), AvxVector(0.0, 1.0, 2.1, 3.0));
}

TEST(AvxVectorTest, CanBeScaled)
{
    EXPECT_EQ(AvxVector(1.0) * 2.0, AvxVector(2.0));
    EXPECT_EQ(AvxVector(1.0, 2.0, 3.0, 4.0) * 2.0, AvxVector(2, 4, 6.0, 8.0));
}

TEST(AvxVectorTest, CanBeScaleAssigned)
{
    AvxVector a(1.0, 2.0, 3.0, 4.0);
    a *= {1.0, 0.5, 0.5, 2.0};
    EXPECT_EQ(a, AvxVector(1.0, 1.0, 1.5, 8.0));
    a *= 2.0;
    EXPECT_EQ(a, AvxVector(2.0, 2.0, 3.0, 16));
    a *= -1.0;
    EXPECT_EQ(a, -AvxVector(2.0, 2.0, 3.0, 16));
    a *= 0.0;
    EXPECT_EQ(a, AvxVector(0.0));
}

TEST(AvxVectorTest, CanBeNormalized)
{
    AvxVector b(1.1, 0.0, 0.0);
    AvxVector c(0.0, 2.0, 0.0);
    AvxVector d(0.0, 0.0, -3.0);
    EXPECT_EQ(b.Normalized(), AvxVector(1.0, 0.0, 0.0));
    EXPECT_EQ(c.Normalized(), AvxVector(0.0, 1.0, 0.0));
    EXPECT_EQ(d.Normalized(), AvxVector(0.0, 0.0, -1.0));
    EXPECT_NE(b, AvxVector(1.0, 0.0, 0.0));
    EXPECT_NE(c, AvxVector(0.0, 1.0, 0.0));
    EXPECT_NE(d, AvxVector(0.0, 0.0, -1.0));

    b.Normalize();
    c.Normalize();
    d.Normalize();
    EXPECT_EQ(b, AvxVector(1.0, 0.0, 0.0));
    EXPECT_EQ(c, AvxVector(0.0, 1.0, 0.0));
    EXPECT_EQ(d, AvxVector(0.0, 0.0, -1.0));

    AvxVector a(2.0, 2.0, 3.0);
    a.Normalize();
    EXPECT_DOUBLE_EQ(a[0], 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a[1], 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a[2], 0.7276068751089989);
    EXPECT_DOUBLE_EQ(a[3], 0.0);
}

TEST(AvxVectorTest, CanComputeDotProduct)
{
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ 1.0 }, { 2.0 }), 8.0);
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ 1.0, 2.0, 3.0, 4.0 }, { 2.0, 2.0, 1.0, 4.0 }), 25);
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ -1.0 }, { 2.0 }), -8.0);
    EXPECT_DOUBLE_EQ(AvxVector::Dot({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), 0.0);
    EXPECT_DOUBLE_EQ(AvxVector::AbsDot({ -1.0 }, { 2.0 }), 8.0);
    EXPECT_DOUBLE_EQ(AvxVector::AbsDot({ 1.0 }, { 2.0 }), 8.0);
}

TEST(AvxVectorTest, CanComputeAngle)
{
    EXPECT_DOUBLE_EQ(AvxVector::Angle({ 1.0 }, { 1.0 }), 0.0);
    EXPECT_DOUBLE_EQ(AvxVector::Angle({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), 1.5707963267948966);
    EXPECT_DOUBLE_EQ(AvxVector::Angle({ 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0 }), 0.1304771607247695);
}

TEST(AvxVectorTest, CanComputeCrossProduct)
{
    EXPECT_THROW(AvxVector::Cross({ 1.0 }, { 1.0, 2.0, 3.0, 0.0 }), std::invalid_argument);
    EXPECT_THROW(AvxVector::Cross({ 1.0, 2.0, 3.0, 0.0 }, { 1.0 }), std::invalid_argument);
    EXPECT_THROW(AvxVector::Cross({ 1.0 }, { 1.0 }), std::invalid_argument);

    EXPECT_EQ(AvxVector::Cross({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), AvxVector(0.0, 0.0, 1.0));
    EXPECT_EQ(AvxVector::Cross({ 1.0, 2.0, 3.0 }, { 2.0, 1.0, 0.0 }), AvxVector(-3.0, 6.0, -3.0));
    EXPECT_EQ(AvxVector::Cross({ -1.0, 2.0, 3.0 }, { 5.0, 1.0, 4.0 }), AvxVector(5.0, 19.0, -11.0));
}

