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
#include "math/vector4.h"
#include <stdexcept>

TEST(Vector4Test, CanBeCreated)
{
    ASSERT_NO_THROW(Vector4 v);
}

TEST(Vector4Test, DefaultsToZeroVector)
{
    Vector4 v;
    EXPECT_DOUBLE_EQ(v[0], 0.0);
    EXPECT_DOUBLE_EQ(v[1], 0.0);
    EXPECT_DOUBLE_EQ(v[2], 0.0);
    EXPECT_DOUBLE_EQ(v[3], 0.0);
}

TEST(Vector4Test, CanBeCreatedScalar)
{
    Vector4 v(22.0);
    EXPECT_DOUBLE_EQ(v[0], 22.0);
    EXPECT_DOUBLE_EQ(v[1], 22.0);
    EXPECT_DOUBLE_EQ(v[2], 22.0);
    EXPECT_DOUBLE_EQ(v[3], 22.0);
}

TEST(Vector4Test, CanBeCreatedPerComponent)
{
    Vector4 v(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);

    Vector4 u(1.0, 2.0);
    EXPECT_DOUBLE_EQ(u[0], 1.0);
    EXPECT_DOUBLE_EQ(u[1], 2.0);
    EXPECT_DOUBLE_EQ(u[2], 0.0);
    EXPECT_DOUBLE_EQ(u[3], 0.0);

    Vector4 w(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(w[0], 1.0);
    EXPECT_DOUBLE_EQ(w[1], 2.0);
    EXPECT_DOUBLE_EQ(w[2], 3.0);
    EXPECT_DOUBLE_EQ(w[3], 0.0);
}

TEST(Vector4Test, CanBeSetPerComponents)
{
    Vector4 v;
    v[0] = 1.0;
    v[1] = 2.0;
    v[2] = 3.0;
    v[3] = 4.0;

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(Vector4Test, CanBeAccessedPerComponent)
{
    Vector4 v(1.0, 2.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(Vector4Test, CanBeCopyConstructed)
{
    Vector4 a(22.0);
    Vector4 b(a);

    EXPECT_DOUBLE_EQ(b[0], 22.0);
    EXPECT_DOUBLE_EQ(b[1], 22.0);
    EXPECT_DOUBLE_EQ(b[2], 22.0);
    EXPECT_DOUBLE_EQ(b[3], 22.0);

    b[0] = 0.0;
    EXPECT_DOUBLE_EQ(a[0], 22.0);
}

TEST(Vector4Test, CanBeCopied)
{
    Vector4 a(22.0);
    Vector4 b = a;

    EXPECT_DOUBLE_EQ(b[0], 22.0);
    EXPECT_DOUBLE_EQ(b[1], 22.0);
    EXPECT_DOUBLE_EQ(b[2], 22.0);
    EXPECT_DOUBLE_EQ(b[3], 22.0);

    b[0] = 0.0;
    EXPECT_DOUBLE_EQ(a[0], 22.0);
}

TEST(Vector4Test, CanBeAdded)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);

    Vector4 c = a + b;
    EXPECT_DOUBLE_EQ(c[0], 3.0);
    EXPECT_DOUBLE_EQ(c[1], 5.0);
    EXPECT_DOUBLE_EQ(c[2], 7.0);
    EXPECT_DOUBLE_EQ(c[3], 9.0);
}

TEST(Vector4Test, CanBeAddAssigned)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);
    b += a;

    EXPECT_DOUBLE_EQ(b[0], 3.0);
    EXPECT_DOUBLE_EQ(b[1], 5.0);
    EXPECT_DOUBLE_EQ(b[2], 7.0);
    EXPECT_DOUBLE_EQ(b[3], 9.0);
}

TEST(Vector4Test, CanBeSubtracted)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);

    Vector4 c = a - b;
    EXPECT_DOUBLE_EQ(c[0], -1.0);
    EXPECT_DOUBLE_EQ(c[1], -1.0);
    EXPECT_DOUBLE_EQ(c[2], -1.0);
    EXPECT_DOUBLE_EQ(c[3], -1.0);
}

TEST(Vector4Test, CanBeSubtractAssigned)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    Vector4 b(2.0, 3.0, 4.0, 5.0);
    b -= a;

    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 1.0);
    EXPECT_DOUBLE_EQ(b[3], 1.0);
}

TEST(Vector4Test, CanBeNegated)
{
    Vector4 a(-1.0);
    Vector4 b = -a;
    EXPECT_DOUBLE_EQ(b[0], 1.0);
    EXPECT_DOUBLE_EQ(b[1], 1.0);
    EXPECT_DOUBLE_EQ(b[2], 1.0);
    EXPECT_DOUBLE_EQ(b[3], 1.0);
}

TEST(Vector4Test, DoesNotChangeWithPveSign)
{
    Vector4 a(-1.0);
    Vector4 b = +a;
    EXPECT_DOUBLE_EQ(b[0], -1.0);
    EXPECT_DOUBLE_EQ(b[1], -1.0);
    EXPECT_DOUBLE_EQ(b[2], -1.0);
    EXPECT_DOUBLE_EQ(b[3], -1.0);
}

TEST(Vector4Test, CanComputeMagnitude)
{
    Vector4 a(1.0, 2.0, 3.0);
    Vector4 b(1.0, 0.0, 0.0);
    Vector4 c(0.0, 2.0, 0.0);
    Vector4 d(0.0, 0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.Magnitude(), sqrt(14.0));
    EXPECT_DOUBLE_EQ(b.Magnitude(), 1.0);
    EXPECT_DOUBLE_EQ(c.Magnitude(), 2.0);
    EXPECT_DOUBLE_EQ(d.Magnitude(), 3.0);
}

TEST(Vector4Test, CanComputeSquareMagnitude)
{
    Vector4 a(1.0, 2.0, 3.0);
    Vector4 b(1.0, 0.0, 0.0);
    Vector4 c(0.0, 2.0, 0.0);
    Vector4 d(0.0, 0.0, 3.0);

    EXPECT_DOUBLE_EQ(a.MagnitudeSquared(), 14.0);
    EXPECT_DOUBLE_EQ(b.MagnitudeSquared(), 1.0);
    EXPECT_DOUBLE_EQ(c.MagnitudeSquared(), 4.0);
    EXPECT_DOUBLE_EQ(d.MagnitudeSquared(), 9.0);
}

TEST(Vector4Test, DefaultUnitVectorsHaveUnitLength)
{
    EXPECT_DOUBLE_EQ(Vector4::Up().MagnitudeSquared(), 1.0);
    EXPECT_DOUBLE_EQ(Vector4::Right().MagnitudeSquared(), 1.0);
    EXPECT_DOUBLE_EQ(Vector4::Forward().MagnitudeSquared(), 1.0);
}

TEST(Vector4Test, DefaultZeroVectorHaveZeroLength)
{
    EXPECT_DOUBLE_EQ(Vector4::Zero().MagnitudeSquared(), 0.0);
}

TEST(Vector4Test, CanCheckEquality)
{
    EXPECT_EQ(Vector4(1.0), Vector4(1.0));
    EXPECT_EQ(Vector4(0.2), Vector4(0.2));
    EXPECT_EQ(Vector4(1.0, 2.0, 3.0, 4.0), Vector4(1.0, 2.0, 3.0, 4.0));
    EXPECT_NE(Vector4(0.0), Vector4(1.0));
    EXPECT_NE(Vector4(0.0), Vector4(0.00001));
    EXPECT_NE(Vector4(0.0, 1.0, 2.0, 3.0), Vector4(0.0, 1.0, 2.1, 3.0));
}

TEST(Vector4Test, CanBeScaled)
{
    EXPECT_EQ(Vector4(1.0) * 2.0, Vector4(2.0));
    EXPECT_EQ(Vector4(1.0, 2.0, 3.0, 4.0) * 2.0, Vector4(2, 4, 6.0, 8.0));
}

TEST(Vector4Test, CanBeScaleAssigned)
{
    Vector4 a(1.0, 2.0, 3.0, 4.0);
    a *= {1.0, 0.5, 0.5, 2.0};
    EXPECT_EQ(a, Vector4(1.0, 1.0, 1.5, 8.0));
    a *= 2.0;
    EXPECT_EQ(a, Vector4(2.0, 2.0, 3.0, 16));
    a *= -1.0;
    EXPECT_EQ(a, -Vector4(2.0, 2.0, 3.0, 16));
    a *= 0.0;
    EXPECT_EQ(a, Vector4(0.0));
}

TEST(Vector4Test, CanBeNormalized)
{
    Vector4 b(1.1, 0.0, 0.0);
    Vector4 c(0.0, 2.0, 0.0);
    Vector4 d(0.0, 0.0, -3.0);
    EXPECT_EQ(b.Normalized(), Vector4(1.0, 0.0, 0.0));
    EXPECT_EQ(c.Normalized(), Vector4(0.0, 1.0, 0.0));
    EXPECT_EQ(d.Normalized(), Vector4(0.0, 0.0, -1.0));
    EXPECT_NE(b, Vector4(1.0, 0.0, 0.0));
    EXPECT_NE(c, Vector4(0.0, 1.0, 0.0));
    EXPECT_NE(d, Vector4(0.0, 0.0, -1.0));

    b.Normalize();
    c.Normalize();
    d.Normalize();
    EXPECT_EQ(b, Vector4(1.0, 0.0, 0.0));
    EXPECT_EQ(c, Vector4(0.0, 1.0, 0.0));
    EXPECT_EQ(d, Vector4(0.0, 0.0, -1.0));

    Vector4 a(2.0, 2.0, 3.0);
    a.Normalize();
    EXPECT_DOUBLE_EQ(a[0], 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a[1], 0.48507125007266594);
    EXPECT_DOUBLE_EQ(a[2], 0.7276068751089989);
    EXPECT_DOUBLE_EQ(a[3], 0.0);
}

TEST(Vector4Test, CanComputeDotProduct)
{
    EXPECT_DOUBLE_EQ(Vector4::Dot({ 1.0 }, { 2.0 }), 8.0);
    EXPECT_DOUBLE_EQ(Vector4::Dot({ 1.0, 2.0, 3.0, 4.0 }, { 2.0, 2.0, 1.0, 4.0 }), 25);
    EXPECT_DOUBLE_EQ(Vector4::Dot({ -1.0 }, { 2.0 }), -8.0);
    EXPECT_DOUBLE_EQ(Vector4::Dot({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), 0.0);
    EXPECT_DOUBLE_EQ(Vector4::AbsDot({ -1.0 }, { 2.0 }), 8.0);
    EXPECT_DOUBLE_EQ(Vector4::AbsDot({ 1.0 }, { 2.0 }), 8.0);
}

TEST(Vector4Test, CanComputeAngle)
{
    EXPECT_DOUBLE_EQ(Vector4::Angle({ 1.0 }, { 1.0 }), 0.0);
    EXPECT_DOUBLE_EQ(Vector4::Angle({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), 1.5707963267948966);
    EXPECT_DOUBLE_EQ(Vector4::Angle({ 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0 }), 0.1304771607247695);
}

TEST(Vector4Test, CanComputeCrossProduct)
{
    EXPECT_THROW(Vector4::Cross({ 1.0 }, { 1.0, 2.0, 3.0, 0.0 }), std::invalid_argument);
    EXPECT_THROW(Vector4::Cross({ 1.0, 2.0, 3.0, 0.0 }, { 1.0 }), std::invalid_argument);
    EXPECT_THROW(Vector4::Cross({ 1.0 }, { 1.0 }), std::invalid_argument);

    EXPECT_EQ(Vector4::Cross({ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), Vector4(0.0, 0.0, 1.0));
    EXPECT_EQ(Vector4::Cross({ 1.0, 2.0, 3.0 }, { 2.0, 1.0, 0.0 }), Vector4(-3.0, 6.0, -3.0));
    EXPECT_EQ(Vector4::Cross({ -1.0, 2.0, 3.0 }, { 5.0, 1.0, 4.0 }), Vector4(5.0, 19.0, -11.0));
}

