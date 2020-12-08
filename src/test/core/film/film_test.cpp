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
#include "core/film/film.h"
#include "core/film/standardresolution.h"

TEST(FilmTestSuite, CanBeCreated)
{
    ASSERT_NO_THROW(Film film);
}

TEST(FilmTestSuite, CanGetResolution)
{
    Film film;
    ASSERT_NO_THROW(film.GetResolution());
}

TEST(FilmTestSuite, CanSetResolution)
{
    Film film;
    ASSERT_NO_THROW(film.SetResolution(Resolution1024X768()));
    Resolution res = film.GetResolution();
    EXPECT_EQ(res.GetWidth(), 1024);
    EXPECT_EQ(res.GetHeight(), 768);
}

