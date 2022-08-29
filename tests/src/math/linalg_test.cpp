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
#include "math/linalg.h"

TEST(LinearAlgebraTest, CanMultiplyMatricesWithVectors3x3)
{
    Vector3 a = { 1.0, 1.0, 1.0 };
    Vector3 b = { 1.3432, 2.942, 4.1231 };
    Vector3 c = { -1.592, 1.149, -5.234 };
    Vector3 d = { -1.20, -3.049, 1.38 };
    Vector3 e = { 0, 0, 0 };
    Vector3 f = { 99999, 99999, 99998 };

    Matrix3x3 i = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    EXPECT_EQ(i * a, a);
    EXPECT_EQ(i * b, b);
    EXPECT_EQ(i * c, c);
    EXPECT_EQ(i * d, d);
    EXPECT_EQ(i * e, e);
    EXPECT_EQ(i * f, f);

    Matrix3x3 m1 = { 1, 2, 3, -4, -5, -6, 7, 8, 9 };
    EXPECT_EQ(m1 * a, Vector3(6, -15, 24 ));
    EXPECT_EQ(m1 * b, Vector3(19.5965, -44.8214, 70.0463));
    EXPECT_EQ(m1 * c, Vector3(-14.996, 32.027, -49.058));
    EXPECT_EQ(m1 * d, Vector3(-3.158, 11.765, -20.372));
    EXPECT_EQ(m1 * e, e);
    EXPECT_EQ(m1 * f, Vector3(599991, -1499979, 2399967));
}

TEST(LinearAlgebraTest, CanMultiplyMatricesWithVectors4x4)
{
    Vector4 a = { 1.0, 1.0, 1.0, 1.0 };
    Vector4 b = { 1.3432, 2.942, 4.1231, 2.235 };
    Vector4 c = { -1.592, 1.149, -5.234, -4.42 };
    Vector4 d = { -1.20, -3.049, 1.38, 1.231 };
    Vector4 e = { 0, 0, 0, 0 };
    Vector4 f = { 99999, 99999, 99998, -100000 };

    Matrix4x4 i = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    EXPECT_EQ(i * a, a);
    EXPECT_EQ(i * b, b);
    EXPECT_EQ(i * c, c);
    EXPECT_EQ(i * d, d);
    EXPECT_EQ(i * e, e);
    EXPECT_EQ(i * f, f);

    Matrix4x4 m1 = { 1, 2, 3, -4, -5, -6, 7, 8, 9, -10, 11, -12, 13, 14.2, 15, -16.5 };
    EXPECT_EQ(m1 * a, Vector4(2, 4, -2, 25.7));
    EXPECT_EQ(m1 * b, Vector4(10.6565, 22.3737, 1.2029, 84.207));
    EXPECT_EQ(m1 * c, Vector4(2.684, -70.932, -30.352, -9.9602));
    EXPECT_EQ(m1 * d, Vector4(-8.082, 43.802, 20.098, -58.5073));
    EXPECT_EQ(m1 * e, e);
    EXPECT_EQ(m1 * f, Vector4(999991, -1200003, 2199979, 5869942.8));
}
