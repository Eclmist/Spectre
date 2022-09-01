/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
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
#include "math/ray.h"

TEST(RayTest, CanBeCreated)
{
    ASSERT_NO_THROW(Ray({ 0.0 }, { 1.0, 2.0, 3.0 }));
}

TEST(RayTest, DirectionIsNormalized)
{
    EXPECT_EQ(Ray({ 0.0 }, { 6.0, 0.0, 0.0 }).GetDirection(), Vector3(1.0, 0.0, 0.0));
    EXPECT_EQ(Ray({ 0.0 }, { 1.0, 2.0, 3.0 }).GetDirection(), Vector3(1.0, 2.0, 3.0).Normalized());

    Ray r({ 0.0 }, { 0.0 });
    r.SetDirection({ 1.0, 0.0, 0.0 });
    EXPECT_EQ(r.GetDirection().Magnitude(), 1.0);
    r.SetDirection({ 1.0, 2.0, 3.0 });
    EXPECT_EQ(r.GetDirection().Magnitude(), 1.0);
}

TEST(RayTest, CanBeCopied)
{
    Ray r({ 0.0 }, { 1.0, 2.0, 3.0 });
    Ray copy(r);
    EXPECT_EQ(r.GetDirection(), copy.GetDirection());
    EXPECT_EQ(r.GetOrigin(), copy.GetOrigin());
}

TEST(RayTest, CanBeEvaluated)
{
    Ray r({ 0.0 }, { 1.0, 0.0, 0.0 });
    EXPECT_EQ(r(1), Point3(1.0, 0.0, 0.0));
    EXPECT_EQ(r(2), Point3(2.0, 0.0, 0.0));
    EXPECT_EQ(r(-1), Point3(-1.0, 0.0, 0.0));

    Ray r2({ 2.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 });
    EXPECT_EQ(r2(0), Point3(2.0, 1.0, 0.0));
    EXPECT_EQ(r2(1), Point3(2.0, 2.0, 0.0));
    EXPECT_EQ(r2(-1), Point3(2.0, 0.0, 0.0));
}

TEST(RayTest, CanTestForEquality)
{
    Ray r({ 0.0 }, { 1.0, 0.0, 0.0 });
    Ray r2({ 2.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 });
    Ray r3({ 0.0 }, { 1.0, 2.0, 3.0 });

    EXPECT_EQ(r, r);
    EXPECT_EQ(r2, r2);
    EXPECT_EQ(r3, r3);

    EXPECT_NE(r, r2);
    EXPECT_NE(r, r3);
    EXPECT_NE(r2, r3);
}

