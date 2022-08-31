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

TEST(Point2Test, CanBeCreated)
{
	ASSERT_NO_THROW(Point2 p);
}

TEST(Point2Test, DefaultsToOrigin)
{
	Point2 p;
	EXPECT_DOUBLE_EQ(p.x, 0.0);
	EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(Point2Test, CanBeCreatedScalar)
{
	Point2 p(22.0);
	EXPECT_DOUBLE_EQ(p.x, 22.0);
	EXPECT_DOUBLE_EQ(p.y, 22.0);
}

TEST(Point2Test, CanBeCreatedPerComponent)
{
	Point2 p(1.0, 2.0);
	EXPECT_DOUBLE_EQ(p.x, 1.0);
	EXPECT_DOUBLE_EQ(p.y, 2.0);
}

TEST(Point2Test, CanBeSetPerComponents)
{
	Point2 p;
	p.x = 1.0;
	p.y = 2.0;

	EXPECT_DOUBLE_EQ(p.x, 1.0);
	EXPECT_DOUBLE_EQ(p.y, 2.0);
}

TEST(Point2Test, CanBeAccessedPerComponent)
{
	Point2 p(1.0, 2.0);

	EXPECT_DOUBLE_EQ(p[0], 1.0);
	EXPECT_DOUBLE_EQ(p[1], 2.0);
	EXPECT_DOUBLE_EQ(p.x, 1.0);
	EXPECT_DOUBLE_EQ(p.y, 2.0);
}

TEST(Point2Test, CanBeCopyConstructed)
{
	Point2 a(22.0);
	Point2 b(a);

	EXPECT_DOUBLE_EQ(b.x, 22.0);
	EXPECT_DOUBLE_EQ(b.y, 22.0);

	b.x = 0.0;
	EXPECT_DOUBLE_EQ(a.x, 22.0);
}

TEST(Point2Test, CanBeCopied)
{
	Point2 a(22.0);
	Point2 b = a;

	EXPECT_DOUBLE_EQ(b.x, 22.0);
	EXPECT_DOUBLE_EQ(b.y, 22.0);

	b.x = 0.0;
	EXPECT_DOUBLE_EQ(a.x, 22.0);
}

TEST(Point2Test, CanCheckEquality)
{
	EXPECT_EQ(Point2(1.0), Point2(1.0));
	EXPECT_EQ(Point2(0.2), Point2(0.2));
	EXPECT_EQ(Point2(1.0, 2.0), Point2(1.0, 2.0));
	EXPECT_NE(Point2(0.0), Point2(1.0));
	EXPECT_NE(Point2(0.0), Point2(0.00001));
	EXPECT_NE(Point2(0.0, 1.0), Point2(0.1, 1.0));
}

TEST(Point2Test, CanBeNegated)
{
	Point2 a(-1.0);
	Point2 b = -a;
	EXPECT_DOUBLE_EQ(b.x, 1.0);
	EXPECT_DOUBLE_EQ(b.y, 1.0);
}

TEST(Point2Test, DoesNotChangeWithPveSign)
{
	Point2 a(-1.0);
	Point2 b = +a;
	EXPECT_DOUBLE_EQ(b.x, -1.0);
	EXPECT_DOUBLE_EQ(b.y, -1.0);
}

TEST(Point2Test, CanGetDistanceBetweenPoints)
{
	EXPECT_DOUBLE_EQ(Point2::Distance({ 0, 0 }, { 1.0, 0.0 }), 1.0);
	EXPECT_DOUBLE_EQ(Point2::SquareDistance({ 0, 0 }, { 1.0, 0.0 }), 1.0);
	EXPECT_DOUBLE_EQ(Point2::Distance({ 0.5, 0.13 }, { 2.5, -3 }), 3.7144178547923223);
	EXPECT_DOUBLE_EQ(Point2::SquareDistance({ 0.5, 0.13 }, { 2.5, -3 }), 13.796899999999999);
}

