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
    Ray GenerateRay(const Point2& filmSpacePos) override { return {}; }
};

TEST(CameraTest, CanBeCreated)
{
    ASSERT_NO_THROW(CameraImplStub());
}

TEST(CameraTest, CanGetTransform)
{
    CameraImplStub camera;
    Transform& transform = camera.GetTransform();
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

TEST(CameraTest, CanTransformCameraToWorldSpaceVector)
{
    CameraImplStub camera;
    Transform& transform = camera.GetTransform();

    Vector3 cameraSpaceForward(0, 0, 1);
    Vector3 cameraSpaceUp(0, 1, 0);
    Vector3 cameraSpaceRight(1, 0, 0);

    // Camera at origin
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceRight), cameraSpaceRight);

    Vector3 translation(1, -2.30, 5.234);
    transform.SetTranslation(translation);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceRight), cameraSpaceRight);
}

TEST(CameraTest, CanTransformCameraToWorldSpacePoint)
{
    CameraImplStub camera;
    Transform& transform = camera.GetTransform();

    Point3 cameraSpaceForward(0, 0, 1);
    Point3 cameraSpaceUp(0, 1, 0);
    Point3 cameraSpaceRight(1, 0, 0);

    // Camera at origin
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceRight), cameraSpaceRight);

    Vector3 translation(1, -2.30, 5.234);
    transform.SetTranslation(translation);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceForward), cameraSpaceForward + translation);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceUp), cameraSpaceUp + translation);
    EXPECT_EQ(camera.CameraToWorldSpace(cameraSpaceRight), cameraSpaceRight + translation);
}

