/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    Spectre is free software: you can redistribute it and/or modify
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

TEST(FilmTest, CanGetTile)
{
    Film film;
    film.GetTile({ 50, 50 });
}

TEST(FilmTest, ThrowOnInvalidPixelPosition)
{
    Film film;
    ASSERT_NO_THROW(film.GetTile({ 0, 0 }));
    ASSERT_NO_THROW(film.GetTile({ 799, 479 }));
    ASSERT_THROW(film.GetTile({ 800, 480 }), std::invalid_argument);
}

TEST(FilmTest, CanGetTileAfterResize)
{
    Film film;
    film.SetResolution(Resolution800X600());
    ASSERT_NO_THROW(film.GetTile({ 799, 599 }));
}

TEST(FilmTest, CanGetTotalTileCount)
{
    Film film;
    double tileSize = (double)film.GetTileSize();
    film.SetResolution(Resolution640X360());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(640 / tileSize) * std::ceil(360 / tileSize));

    film.SetResolution(Resolution800X480());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(800 / tileSize) * std::ceil(480 / tileSize));

    film.SetResolution(Resolution800X600());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(800 / tileSize) * std::ceil(600 / tileSize));

    film.SetResolution(Resolution1024X768());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(1024 / tileSize) * std::ceil(768 / tileSize));

    film.SetResolution(Resolution1280X720());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(1280 / tileSize) * std::ceil(720 / tileSize));

    film.SetResolution(Resolution1366X768());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(1366 / tileSize) * std::ceil(768 / tileSize));

    film.SetResolution(Resolution1600X900());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(1600 / tileSize) * std::ceil(900 / tileSize));

    film.SetResolution(Resolution1920X1080());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(1920 / tileSize) * std::ceil(1080 / tileSize));

    film.SetResolution(Resolution2560X1440());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(2560 / tileSize) * std::ceil(1440 / tileSize));

    film.SetResolution(Resolution3840X2160());
    ASSERT_EQ(film.GetNumTiles(), std::ceil(3840 / tileSize) * std::ceil(2160 / tileSize));
}

