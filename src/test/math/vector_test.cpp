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
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
    EXPECT_DOUBLE_EQ(v.w, 0.0);
}

TEST(VectorTest, CanBeCreatedScalar)
{
    Vector4 v(22.0);
    EXPECT_DOUBLE_EQ(v.x, 22.0);
    EXPECT_DOUBLE_EQ(v.y, 22.0);
    EXPECT_DOUBLE_EQ(v.z, 22.0);
    EXPECT_DOUBLE_EQ(v.w, 22.0);
}

TEST(VectorTest, CanBeCreatedPerComponent)
{
    Vector4 v(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    EXPECT_DOUBLE_EQ(v.w, 4.0);
}

