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
#include "math/rect.h"

TEST(RectTest, CanBeCreated)
{
    ASSERT_THROW(Rect rect(0, 0, -1, 0), std::invalid_argument);
    ASSERT_THROW(Rect rect(0, 0, 0, -1), std::invalid_argument);
    ASSERT_THROW(Rect rect(0, 0, -1, -1), std::invalid_argument);
    ASSERT_NO_THROW(Rect rect(0, 0, 0, 0));
    ASSERT_NO_THROW(Rect rect(-1, 0, 0, 0));
    ASSERT_NO_THROW(Rect rect(0, -1, 0, 0));
    ASSERT_NO_THROW(Rect rect(0, 0, 100, 100));
    ASSERT_NO_THROW(Rect rect(0, 0, 10000, 10000));
}

TEST(RectTest, CanCheckIfInBounds)
{
    Rect rect(100, 200, 200, 400);
    EXPECT_FALSE(rect.IsWithinBounds(99, 199));
    EXPECT_FALSE(rect.IsWithinBounds(100, 199));
    EXPECT_TRUE(rect.IsWithinBounds(100, 200));

    EXPECT_FALSE(rect.IsWithinBounds(300, 600));
    EXPECT_FALSE(rect.IsWithinBounds(299, 600));
    EXPECT_FALSE(rect.IsWithinBounds(300, 599));
    EXPECT_TRUE(rect.IsWithinBounds(299, 599));
}