/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
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
#include "core/film/standardresolution.h"

TEST(ResolutionTest, CanBeCreated)
{
    ASSERT_NO_THROW(Resolution res);
}

TEST(ResolutionTest, HasValidDefaults)
{
    Resolution res;
    EXPECT_EQ(res.GetWidth(), 800);
    EXPECT_EQ(res.GetHeight(), 480);
}

TEST(ResolutionTest, WidthHeightCanBeSet)
{
    Resolution res;
    res.SetWidth(500);
    res.SetHeight(500);
    EXPECT_EQ(res.GetWidth(), 500);
    EXPECT_EQ(res.GetHeight(), 500);
}

TEST(ResolutionTest, ThrowOnInvalidWidthHeight)
{
    Resolution res;
    EXPECT_NO_THROW(res.SetWidth(1));
    EXPECT_NO_THROW(res.SetHeight(1));
    EXPECT_NO_THROW(res.SetWidth(3840));
    EXPECT_NO_THROW(res.SetHeight(2160));
    EXPECT_THROW(res.SetWidth(3841), std::invalid_argument);
    EXPECT_THROW(res.SetHeight(2161), std::invalid_argument);
    EXPECT_THROW(res.SetWidth(0), std::invalid_argument);
    EXPECT_THROW(res.SetHeight(0), std::invalid_argument);
}

TEST(ResolutionTest, CanCopyWidthHeight)
{
    Resolution res;
    res.SetWidth(321);
    res.SetHeight(123);
    Resolution res2(res);
    EXPECT_EQ(res2.GetWidth(), res.GetWidth());
    EXPECT_EQ(res2.GetHeight(), res.GetHeight());
}

TEST(ResolutionTest, HaveCommonWidthHeightPresets)
{
    Resolution640X360 res640X360;
    EXPECT_EQ(res640X360.GetWidth(), 640);
    EXPECT_EQ(res640X360.GetHeight(), 360);

    Resolution800X480 res800X480;
    EXPECT_EQ(res800X480.GetWidth(), 800);
    EXPECT_EQ(res800X480.GetHeight(), 480);

    Resolution800X600 res800X600;
    EXPECT_EQ(res800X600.GetWidth(), 800);
    EXPECT_EQ(res800X600.GetHeight(), 600);

    Resolution1024X768 res1024X768;
    EXPECT_EQ(res1024X768.GetWidth(), 1024);
    EXPECT_EQ(res1024X768.GetHeight(), 768);

    Resolution1280X720 res1280X720;
    EXPECT_EQ(res1280X720.GetWidth(), 1280);
    EXPECT_EQ(res1280X720.GetHeight(), 720);

    Resolution1366X768 res1366X768;
    EXPECT_EQ(res1366X768.GetWidth(), 1366);
    EXPECT_EQ(res1366X768.GetHeight(), 768);

    Resolution1600X900 res1600X900;
    EXPECT_EQ(res1600X900.GetWidth(), 1600);
    EXPECT_EQ(res1600X900.GetHeight(), 900);

    Resolution1920X1080 res1920X1080;
    EXPECT_EQ(res1920X1080.GetWidth(), 1920);
    EXPECT_EQ(res1920X1080.GetHeight(), 1080);

    Resolution2560X1440 res2560X1440;
    EXPECT_EQ(res2560X1440.GetWidth(), 2560);
    EXPECT_EQ(res2560X1440.GetHeight(), 1440);

    Resolution3840X2160 res3840X2160;
    EXPECT_EQ(res3840X2160.GetWidth(), 3840);
    EXPECT_EQ(res3840X2160.GetHeight(), 2160);
}

TEST(ResolutionTest, CanCheckIfInBounds)
{
    Resolution640X360 res;
    EXPECT_TRUE(res.IsWithinBounds({0, 0}));
    EXPECT_TRUE(res.IsWithinBounds({639, 359}));
    EXPECT_FALSE(res.IsWithinBounds({640, 340}));
}

TEST(ResolutionTest, CanCheckEquality)
{
    Resolution640X360 res;
    EXPECT_EQ(res, Resolution640X360());
    Resolution res2;
    res2.SetWidth(640);
    res2.SetHeight(360);
    EXPECT_EQ(res, res2);

    res2.SetWidth(641);
    EXPECT_NE(res, res2);

    res2.SetWidth(640);
    res2.SetHeight(361);
    EXPECT_NE(res, res2);

    res2.SetHeight(360);
    EXPECT_EQ(res, res2);
}

