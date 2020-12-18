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

#include "gtest.h"
#include "core/film/film.h"
#include "core/film/standardresolution.h"

TEST(FilmTest, CanBeCreated)
{
    ASSERT_NO_THROW(Film film);
}

TEST(FilmTest, CanGetResolution)
{
    Film film;
    ASSERT_NO_THROW(film.GetResolution());
}

TEST(FilmTest, CanSetResolution)
{
    Film film;
    ASSERT_NO_THROW(film.SetResolution(Resolution1024X768()));
    Resolution res = film.GetResolution();
    EXPECT_EQ(res.GetWidth(), 1024);
    EXPECT_EQ(res.GetHeight(), 768);
}

TEST(FilmTest, CanGetPixelValue)
{
    Film film;
    Pixel p = film.GetPixel(50, 50);
    EXPECT_FLOAT_EQ(p.m_XYZ[0], 0.0f);
    EXPECT_FLOAT_EQ(p.m_XYZ[1], 0.0f);
    EXPECT_FLOAT_EQ(p.m_XYZ[2], 0.0f);
}

TEST(FilmTest, ThrowOnInvalidPixelPosition)
{
    Film film;
    ASSERT_NO_THROW(film.GetPixel(0, 0));
    ASSERT_NO_THROW(film.GetPixel(799, 479));
    ASSERT_THROW(film.GetPixel(800, 480), std::invalid_argument);
    ASSERT_THROW(film.GetPixel(-1, -1), std::invalid_argument);
}

TEST(FilmTest, CanGetPixelValueAfterResize)
{
    Film film;
    film.SetResolution(Resolution800X600());
    ASSERT_NO_THROW(film.GetPixel(799, 599));
}

TEST(FilmTest, CanSetPixelValue)
{
    Film film;
    ASSERT_NO_THROW(film.SetPixel(50, 50, {0.2, 0.3, 0.4}));
    Pixel p = film.GetPixel(50, 50);
    EXPECT_FLOAT_EQ(p.m_XYZ[0], 0.2f);
    EXPECT_FLOAT_EQ(p.m_XYZ[1], 0.3f);
    EXPECT_FLOAT_EQ(p.m_XYZ[2], 0.4f);
}

TEST(FilmTest, CanGetTotalPixelCount)
{
    Film film;
    film.SetResolution(Resolution640X360());
    ASSERT_EQ(film.GetNumPixels(), 640 * 360);
}

