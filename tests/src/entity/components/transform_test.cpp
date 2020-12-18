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
    EXPECT_EQ(Transform().GetTranslation(), Vector4());
}

TEST(TransformTest, CanTranslate)
{
    Transform t;
    ASSERT_NO_THROW(t.Translate({ 1, 2, 3 }));
    EXPECT_EQ(t.GetTranslation(), Vector4(1, 2, 3, 0));
    ASSERT_NO_THROW(t.Translate({ 1, 2, 3 }));
    EXPECT_EQ(t.GetTranslation(), Vector4(2, 4, 6, 0));
    ASSERT_THROW(t.Translate({ 1, 2, 3, 1 }), std::invalid_argument);
}

TEST(TransformTest, CanSetTranlation)
{
    Transform t;
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetTranslation(), Vector4(1, 2, 3, 0));
    ASSERT_NO_THROW(t.SetTranslation({ 1, 2, 4 }));
    EXPECT_EQ(t.GetTranslation(), Vector4(1, 2, 4, 0));
    ASSERT_THROW(t.SetTranslation({ 1, 2, 3, 1 }), std::invalid_argument);
}

TEST(TransformTest, CanGetRotation)
{
    EXPECT_EQ(Transform().GetRotation(), Vector4());
}

TEST(TransformTest, CanRotate)
{
    Transform t;
    ASSERT_NO_THROW(t.Rotate({ 1, 2, 3 }));
    EXPECT_EQ(t.GetRotation(), Vector4(1, 2, 3, 0));
    ASSERT_NO_THROW(t.Rotate({ 1, 2, 3 }));
    EXPECT_EQ(t.GetRotation(), Vector4(2, 4, 6, 0));
    ASSERT_THROW(t.Rotate({ 1, 2, 3, 1 }), std::invalid_argument);
}

TEST(TransformTest, CanSetRotation)
{
    Transform t;
    ASSERT_NO_THROW(t.SetRotation({ 1, 2, 3 }));
    EXPECT_EQ(t.GetRotation(), Vector4(1, 2, 3, 0));
    ASSERT_NO_THROW(t.SetRotation({ 1, 2, 4 }));
    EXPECT_EQ(t.GetRotation(), Vector4(1, 2, 4, 0));
    ASSERT_THROW(t.SetRotation({ 1, 2, 3, 1 }), std::invalid_argument);
}

TEST(TransformTest, CanScale)
{
    Transform t;
    ASSERT_NO_THROW(t.Scale({ 1, 2, 3 }));
    EXPECT_EQ(t.GetScale(), Vector4(1, 2, 3, 0));
    ASSERT_NO_THROW(t.Scale({ 1, 2, 3 }));
    EXPECT_EQ(t.GetScale(), Vector4(1, 4, 9, 0));
    ASSERT_THROW(t.Scale({ 1, 2, 3, 1 }), std::invalid_argument);
}

TEST(TransformTest, CanGetScale)
{
    EXPECT_EQ(Transform().GetScale(), Vector4(1));
}

TEST(TransformTest, CanSetScale)
{
    Transform t;
    ASSERT_NO_THROW(t.SetScale({ 1, 2, 3 }));
    EXPECT_EQ(t.GetScale(), Vector4(1, 2, 3, 0));
    ASSERT_NO_THROW(t.SetScale({ 1, 2, 4 }));
    EXPECT_EQ(t.GetScale(), Vector4(1, 2, 4, 0));
    ASSERT_THROW(t.SetScale({ 1, 2, 3, 1 }), std::invalid_argument);
}

