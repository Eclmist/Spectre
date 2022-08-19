/*
    This file is part of RTCore, an open-source physically based
    renderer.

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
#include "core/film/filmtile.h"

TEST(FilmTileTest, CanBeCreated)
{
    ASSERT_THROW(FilmTile filmTile({0,0}, {0,0}), std::invalid_argument);
    ASSERT_THROW(FilmTile filmTile({0,0}, {1,0}), std::invalid_argument);
    ASSERT_THROW(FilmTile filmTile({0,0}, {0,1}), std::invalid_argument);
    ASSERT_THROW(FilmTile filmTile({-1,-1}, {1,1}), std::invalid_argument);
    ASSERT_THROW(FilmTile filmTile({0,-1}, {1,1}), std::invalid_argument);
    ASSERT_THROW(FilmTile filmTile({-1,0}, {1,1}), std::invalid_argument);
    ASSERT_NO_THROW(FilmTile filmTile({0,0}, {1,1}));
}

TEST(FilmTileTest, CanGetPosition)
{
    FilmTile filmTile({ 20, 30 }, { 100, 120 });
    EXPECT_EQ(filmTile.GetPosition(), Vector2i(20, 30));
}

TEST(FilmTileTest, CanGetSize)
{
    FilmTile filmTile({ 20, 30 }, { 100, 120 });
    EXPECT_EQ(filmTile.GetSize(), Vector2i(100, 120));
}

TEST(FilmTileTest, CanConvertBetweenFilmAndTileSpace)
{
    FilmTile filmTile({ 50, 50 }, { 50, 50 });
    EXPECT_EQ(filmTile.FilmToTileSpace({ 50, 50 }), Vector2i(0, 0));
    EXPECT_EQ(filmTile.FilmToTileSpace({ 100, 100 }), Vector2i(50, 50));
    EXPECT_EQ(filmTile.FilmToTileSpace({ 25, 25 }), Vector2i(-25, -25));

    EXPECT_EQ(filmTile.TileToFilmSpace({ 0, 0 }), Vector2i(50, 50));
    EXPECT_EQ(filmTile.TileToFilmSpace({ 50, 50 }), Vector2i(100, 100));
    EXPECT_EQ(filmTile.TileToFilmSpace({ -25, -25 }), Vector2i(25, 25));
}

TEST(FilmTileTest, CanGetIndex)
{
    FilmTile filmTile({ 20, 30 }, { 80, 70 });
    EXPECT_THROW(filmTile.GetIndex({ -1, 0 }), std::invalid_argument);
    EXPECT_THROW(filmTile.GetIndex({ 0, -1 }), std::invalid_argument);
    EXPECT_THROW(filmTile.GetIndex({ -1, -1 }), std::invalid_argument);
    EXPECT_NO_THROW(filmTile.GetIndex({ 0, 0 }));
    EXPECT_NO_THROW(filmTile.GetIndex({ 79, 69 }));
    EXPECT_THROW(filmTile.GetIndex({ 80, 69 }), std::invalid_argument);
    EXPECT_THROW(filmTile.GetIndex({ 79, 70 }), std::invalid_argument);
    EXPECT_THROW(filmTile.GetIndex({ 80, 70 }), std::invalid_argument);

    EXPECT_EQ(filmTile.GetIndex({ 0, 0 }), 0);
    EXPECT_EQ(filmTile.GetIndex({ 79, 0 }), 79);
    EXPECT_EQ(filmTile.GetIndex({ 0, 1 }), 80);
    EXPECT_EQ(filmTile.GetIndex({ 79, 1 }), 159);
    EXPECT_EQ(filmTile.GetIndex({ 79, 69 }), 5599);
}

TEST(FilmTileTest, ThrowOnInvalidPixelPosition)
{
    FilmTile filmTile({ 0, 0 }, { 50, 50 });
    ASSERT_NO_THROW(filmTile.GetFilmSpacePixel({ 0, 0 }));
    ASSERT_NO_THROW(filmTile.GetTileSpacePixel({ 0, 0 }));
    ASSERT_NO_THROW(filmTile.GetFilmSpacePixel({ 49, 49 }));
    ASSERT_NO_THROW(filmTile.GetTileSpacePixel({ 49, 49 }));
    ASSERT_THROW(filmTile.GetFilmSpacePixel({ -1, 0 }), std::invalid_argument);
    ASSERT_THROW(filmTile.GetFilmSpacePixel({ 0, -1 }), std::invalid_argument);
    ASSERT_THROW(filmTile.GetFilmSpacePixel({ -1, -1 }), std::invalid_argument);
    ASSERT_THROW(filmTile.GetFilmSpacePixel({ 50, 49 }), std::invalid_argument);
    ASSERT_THROW(filmTile.GetFilmSpacePixel({ 49, 50 }), std::invalid_argument);
    ASSERT_THROW(filmTile.GetFilmSpacePixel({ 50, 50 }), std::invalid_argument);
}

TEST(FilmTileTest, CanGetPixelValue)
{
    FilmTile filmTile({ 0, 0 }, { 50, 50 });
    Pixel p = filmTile.GetFilmSpacePixel({ 49, 49 });
    EXPECT_EQ(p.m_XYZ[0], 0.0);
    EXPECT_EQ(p.m_XYZ[1], 0.0);
    EXPECT_EQ(p.m_XYZ[2], 0.0);

    p = filmTile.GetTileSpacePixel({ 49, 49 });
    EXPECT_EQ(p.m_XYZ[0], 0.0);
    EXPECT_EQ(p.m_XYZ[1], 0.0);
    EXPECT_EQ(p.m_XYZ[2], 0.0);
}

TEST(FilmTileTest, CanSetPixelValue)
{
    FilmTile filmTile({ 0, 0 }, { 100, 100 });
    ASSERT_NO_THROW(filmTile.SetPixel({ 50, 50 }, { 0.2, 0.3, 0.4 }));
    Pixel p = filmTile.GetFilmSpacePixel({ 50, 50 });
    EXPECT_DOUBLE_EQ(p.m_XYZ[0], 0.2);
    EXPECT_DOUBLE_EQ(p.m_XYZ[1], 0.3);
    EXPECT_DOUBLE_EQ(p.m_XYZ[2], 0.4);
}

TEST(FilmTileTest, CanSplatPixelValue)
{
    FilmTile filmTile({ 0, 0 }, { 100, 100 });
    ASSERT_THROW(filmTile.SplatPixel({ 50, 50 }, { 0.2, 0.3, 0.4 }, 1.0001), std::invalid_argument);
    ASSERT_THROW(filmTile.SplatPixel({ 50, 50 }, { 0.2, 0.3, 0.4 }, -0.0001), std::invalid_argument);
    ASSERT_NO_THROW(filmTile.SplatPixel({ 50, 50 }, { 0.2, 0.3, 0.4 }, 1.0));
    Pixel p = filmTile.GetFilmSpacePixel({ 50, 50 });
    EXPECT_DOUBLE_EQ(p.m_XYZ[0], 0.2);
    EXPECT_DOUBLE_EQ(p.m_XYZ[1], 0.3);
    EXPECT_DOUBLE_EQ(p.m_XYZ[2], 0.4);
    ASSERT_THROW(filmTile.SplatPixel({ 50, 50 }, { 0.2, 0.3, 0.4 }, 0.0001), std::invalid_argument);
}

