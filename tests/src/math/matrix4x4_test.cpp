/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.

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

#include "gtest.h"
#include "math/matrix4x4.h"

TEST(Matrix4x4Test, CanBeCreated)
{
    ASSERT_NO_THROW(Matrix4x4());
}

TEST(Matrix4x4Test, CanBeInitializedWithValues)
{
    Matrix4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

    EXPECT_DOUBLE_EQ(m.m_11, 0);
    EXPECT_DOUBLE_EQ(m.m_12, 1);
    EXPECT_DOUBLE_EQ(m.m_13, 2);
    EXPECT_DOUBLE_EQ(m.m_14, 3);
    EXPECT_DOUBLE_EQ(m.m_21, 4);
    EXPECT_DOUBLE_EQ(m.m_22, 5);
    EXPECT_DOUBLE_EQ(m.m_23, 6);
    EXPECT_DOUBLE_EQ(m.m_24, 7);
    EXPECT_DOUBLE_EQ(m.m_31, 8);
    EXPECT_DOUBLE_EQ(m.m_32, 9);
    EXPECT_DOUBLE_EQ(m.m_33, 10);
    EXPECT_DOUBLE_EQ(m.m_34, 11);
    EXPECT_DOUBLE_EQ(m.m_41, 12);
    EXPECT_DOUBLE_EQ(m.m_42, 13);
    EXPECT_DOUBLE_EQ(m.m_43, 14);
    EXPECT_DOUBLE_EQ(m.m_44, 15);

    for (int i = 0; i < 16; ++i)
        EXPECT_DOUBLE_EQ(m.m_Data[i], i);

    for (int s = 0; s < 4; ++s)
        for (int t = 0; t < 4; ++t)
            EXPECT_DOUBLE_EQ(m.m_Data2D[s][t], s * 4 + t);
}

TEST(Matrix4x4Test, CanBeInitializedWithArray)
{
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Matrix4x4 m(data);
    for (int i = 0; i < 16; ++i)
        EXPECT_DOUBLE_EQ(m.m_Data[i], i);
}

TEST(Matrix4x4Test, CanBeInitializedWithArray2D)
{
    double data2D[4][4] = { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15} };
    Matrix4x4 m(data2D);
    for (int i = 0; i < 16; ++i)
        EXPECT_DOUBLE_EQ(m.m_Data[i], i);
}

TEST(Matrix4x4Test, CanCheckIfIdentity)
{
    EXPECT_TRUE(Matrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1).IsIdentity());
    EXPECT_FALSE(Matrix4x4(1,1,1,0,0,1,0,1,1,0,1,1,0,1,0,1).IsIdentity());
    EXPECT_FALSE(Matrix4x4(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,2).IsIdentity());
    EXPECT_FALSE(Matrix4x4(1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1).IsIdentity());
    EXPECT_FALSE(Matrix4x4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0).IsIdentity());
    EXPECT_FALSE(Matrix4x4(-1,0,0,0,0,-1,0,0,0,0,-1,0,0,0,0,-1).IsIdentity());
    EXPECT_FALSE(Matrix4x4(0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0).IsIdentity());
}

TEST(Matrix4x4Test, DefaultsToIdentity)
{
    EXPECT_TRUE(Matrix4x4().IsIdentity());
}

TEST(Matrix4x4Test, CanComputeTranspose)
{
    Matrix4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    Matrix4x4 transposed = m.Transposed();

    for (int s = 0; s < 4; ++s)
        for (int t = 0; t < 4; ++t)
            EXPECT_DOUBLE_EQ(transposed.m_Data2D[s][t], t * 4 + s);
}

TEST(Matrix4x4Test, CanMultiply)
{
    Matrix4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    Matrix4x4 res(56, 62, 68, 74, 152, 174, 196, 218, 248, 286, 324, 362, 344, 398, 452, 506);

    EXPECT_EQ(m * m, res);
}


