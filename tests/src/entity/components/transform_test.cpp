/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest.h"
#include "core/entity/components/transform.h"
TEST(TransformTest, CanBeCreated)
{
    ASSERT_NO_THROW(Transform());
}

TEST(TransformTest, CanGetMatrix)
{
    ASSERT_NO_THROW(Transform().GetMatrix());
}

TEST(TransformTest, CanGetInverseMatrix)
{
    ASSERT_NO_THROW(Transform().GetInverseMatrix());
}

TEST(TransformTest, DefaultsToIdentity)
{
    EXPECT_TRUE(Transform().GetMatrix().IsIdentity());
    EXPECT_EQ(Transform().GetMatrix(), Transform().GetInverseMatrix());
}

TEST(TransformTest, CanGetTranslation)
{
    EXPECT_EQ(Transform().GetTranslation(), Vector3());
}

TEST(TransformTest, CanSetTranlation)
{
    Transform t;
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetTranslation(), Vector3(1, 2, 3));
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 4 }));
    EXPECT_EQ(t.GetTranslation(), Vector3(1, 2, 4));
}

TEST(TransformTest, CanGetRotation)
{
    EXPECT_EQ(Transform().GetRotation(), Vector3());
}

TEST(TransformTest, CanSetRotation)
{
    Transform t;
    ASSERT_NO_THROW(t.SetRotation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetRotation(), Vector3(1, 2, 3));
    ASSERT_NO_THROW(t.SetRotation({ 1, 2, 4 }));
    EXPECT_EQ(t.GetRotation(), Vector3(1, 2, 4));
}

TEST(TransformTest, CanGetScale)
{
    EXPECT_EQ(Transform().GetScale(), Vector3(1));
}

TEST(TransformTest, CanSetScale)
{
    Transform t;
    ASSERT_NO_THROW(t.SetScale({ 1, 2, 3 }));
    EXPECT_EQ(t.GetScale(), Vector3(1, 2, 3));
    ASSERT_NO_THROW(t.SetScale({ 1, 2, 4 }));
    EXPECT_EQ(t.GetScale(), Vector3(1, 2, 4));
}

TEST(TransformTest, MatrixHasCorrectValues)
{
    Transform t, t2;
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1));
    ASSERT_NO_THROW(t.SetScale({ 1, 1, 4 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 4, 3, 0, 0, 0, 1));
    ASSERT_NO_THROW(t2.SetRotation({ M_PI_2, 0, 0 }));
    EXPECT_EQ(t2.GetMatrix(), Matrix4x4(1, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 1));
    ASSERT_NO_THROW(t2.SetRotation({ M_PI_2, M_PI_2, M_PI_2 }));
    EXPECT_EQ(t2.GetMatrix(), Matrix4x4(0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1));
    ASSERT_NO_THROW(t.SetRotation({ M_PI_2, M_PI_2, M_PI_2 }));
    EXPECT_EQ(t.GetMatrix(), Matrix4x4(0, 0, 4, 1, 0, 1, 0, 2, -1, 0, 0, 3, 0, 0, 0, 1));
}


