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
#include "core/camera/camera.h"
#include "core/film/standardresolution.h"

class CameraImplStub : public Camera
{
public:
    void Render() override {}
};

TEST(CameraTest, CanBeCreated)
{
    ASSERT_NO_THROW(CameraImplStub());
}

TEST(CameraTest, CanGetTransform)
{
    CameraImplStub camera;
    Transform& transform = camera.GetTransform();
    EXPECT_TRUE(transform.GetMatrix().IsIdentity());

    transform.SetTranslation({ 1.0, 0.0, 0.0 });
    EXPECT_EQ(camera.GetTransform().GetTranslation(), Vector3(1.0, 0.0, 0.0));
}

TEST(CameraTest, CanGetFilm)
{
    CameraImplStub camera;
    Film& film = camera.GetFilm();
    EXPECT_EQ(film.GetResolution(), Resolution());

    film.SetResolution(Resolution1024X768());
    EXPECT_EQ(camera.GetFilm().GetResolution(), Resolution1024X768());
}

