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
#include "math/mathutils.h"

TEST(MathUtilsTest, CanConvertDegToRad)
{
    EXPECT_DOUBLE_EQ(Math::DegToRad(1), 0.017453292519943295);
    EXPECT_DOUBLE_EQ(Math::DegToRad(0), 0);
    EXPECT_DOUBLE_EQ(Math::DegToRad(-1), -0.017453292519943295);
    EXPECT_DOUBLE_EQ(Math::DegToRad(30), 0.52359877559829882);
    EXPECT_DOUBLE_EQ(Math::DegToRad(45), 0.78539816339744828);
    EXPECT_DOUBLE_EQ(Math::DegToRad(45), Math::PiOver4);
    EXPECT_DOUBLE_EQ(Math::DegToRad(60), 1.0471975511965976);
    EXPECT_DOUBLE_EQ(Math::DegToRad(90), 1.5707963267948966);
    EXPECT_DOUBLE_EQ(Math::DegToRad(90), Math::PiOver2);
    EXPECT_DOUBLE_EQ(Math::DegToRad(180), 3.1415926535897931);
    EXPECT_DOUBLE_EQ(Math::DegToRad(180), Math::Pi);
    EXPECT_DOUBLE_EQ(Math::DegToRad(270), 4.7123889803846897);
    EXPECT_DOUBLE_EQ(Math::DegToRad(360), 6.2831853071795862);
}

TEST(MathUtilsTest, CanConvertRadToDeg)
{
    EXPECT_DOUBLE_EQ(Math::RadToDeg(1), 57.295779513082323);
    EXPECT_DOUBLE_EQ(Math::RadToDeg(0), 0);
    EXPECT_DOUBLE_EQ(Math::RadToDeg(-1), -57.295779513082323);
    EXPECT_DOUBLE_EQ(Math::RadToDeg(Math::Pi), 180);
    EXPECT_DOUBLE_EQ(Math::RadToDeg(Math::Pi * 2), 360);
    EXPECT_DOUBLE_EQ(Math::RadToDeg(Math::PiOver2), 90);
    EXPECT_DOUBLE_EQ(Math::RadToDeg(Math::PiOver4), 45);
}

