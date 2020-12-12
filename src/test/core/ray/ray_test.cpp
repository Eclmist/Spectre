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
#include "core/ray/ray.h"

TEST(RayTest, CanBeCreated)
{
    ASSERT_NO_THROW(Ray({ 0 }, { 1, 2, 3 }));
}

TEST(RayTest, DirectionIsNormalized)
{
    EXPECT_EQ(Ray({ 0 }, { 6, 0, 0 }).m_Direction, Vector4(1, 0, 0));
    EXPECT_EQ(Ray({ 0 }, { 1, 2, 3 }).m_Direction, Vector4(1, 2, 3).Normalized());
}

TEST(RayTest, CanBeCopied)
{
    Ray r({ 0 }, { 1, 2, 3 });
    Ray copy(r);
    EXPECT_EQ(r.m_Direction, copy.m_Direction);
    EXPECT_EQ(r.m_Origin, copy.m_Origin);
}

