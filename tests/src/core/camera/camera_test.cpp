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
    Ray GenerateRay(const Point2i& filmSpacePos, const Vector2& offset) override { return {}; }
};

TEST(CameraTest, CanBeCreated)
{
    ASSERT_NO_THROW(CameraImplStub());
}

TEST(CameraTest, CanGetTransform)
{
    CameraImplStub camera;
    Matrix4x4& transform = camera.GetTransform();
    transform = Transform::GetTranslationMatrix({ 1, 2, 3 });
    EXPECT_EQ(camera.GetTransform(), Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1));
}

TEST(CameraTest, CanGetFilm)
{
    CameraImplStub camera;
    Film& film = camera.GetFilm();
    EXPECT_EQ(film.GetResolution(), Resolution());

    film.SetResolution(Resolution1024X768());
    EXPECT_EQ(camera.GetFilm().GetResolution(), Resolution1024X768());
}

TEST(CameraTest, CanTransformCameraVectorToWorldSpace)
{
    CameraImplStub camera;
    Matrix4x4& transform = camera.GetTransform();

    Vector3 cameraSpaceForward(0, 0, 1);
    Vector3 cameraSpaceUp(0, 1, 0);
    Vector3 cameraSpaceRight(1, 0, 0);

    // Camera at origin
    transform = Transform::GetTranslationMatrix({ 0.0 });
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), cameraSpaceRight);

    transform = Transform::GetTranslationMatrix({ 1, -2.30, 5.234 });
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), cameraSpaceRight);

    transform = Transform::GetScaleMatrix({ 2.0, 2.0, -2.0 });
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), Vector3(0, 0, -2));
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), Vector3(0, 2, 0));
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), Vector3(2, 0, 0));

    transform = Transform::GetRotationMatrix({ SMath::DegToRad(90.0), 0, 0 });
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward),-cameraSpaceUp);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), cameraSpaceForward);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), cameraSpaceRight);
}

TEST(CameraTest, CanTransformCameraPointToWorldSpace)
{
    CameraImplStub camera;
    Matrix4x4& transform = camera.GetTransform();

    Point3 cameraSpaceForward(0, 0, 1);
    Point3 cameraSpaceUp(0, 1, 0);
    Point3 cameraSpaceRight(1, 0, 0);

    // Camera at origin
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), cameraSpaceRight);

    Vector3 translation(1, -2.30, 5.234);
    transform = Transform::GetTranslationMatrix(translation);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), cameraSpaceForward + translation);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), cameraSpaceUp + translation);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), cameraSpaceRight + translation);

    transform = Transform::GetScaleMatrix({ 2.0, 2.0, -2.0 });
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), Point3(0, 0, -2));
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), Point3(0, 2, 0));
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), Point3(2, 0, 0));

    transform = Transform::GetRotationMatrix({ SMath::DegToRad(90.0), 0, 0 });
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceForward), -cameraSpaceUp);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceUp), cameraSpaceForward);
    EXPECT_EQ(camera.ToWorldSpace(cameraSpaceRight), cameraSpaceRight);
}

TEST(CameraTest, CanTranformFilmPointToCameraSpace)
{
    CameraImplStub camera;
    Matrix4x4& transform = camera.GetTransform();
    Resolution resolution = camera.GetFilm().GetResolution();

    Point2i filmPointA(0, 0);
    Point2i filmPointB(10, 0);
    Point2i filmPointC(0, 999);
    Point2i filmPointD(-1, 0);

    double halfWidth = resolution.GetWidth() / 2.0;
    double halfHeight = resolution.GetHeight() / 2.0;

    // Camera at origin
    EXPECT_EQ(camera.ToCameraSpace(filmPointA), Point3(-halfWidth, halfHeight, 1.0));
    EXPECT_EQ(camera.ToCameraSpace(filmPointB), Point3(10 - halfWidth, halfHeight, 1.0));
    EXPECT_EQ(camera.ToCameraSpace(filmPointC), Point3(-halfWidth, halfHeight - 999, 1.0));
    EXPECT_EQ(camera.ToCameraSpace(filmPointD), Point3(-1 - halfWidth, halfHeight, 1.0));
}

TEST(CameraTest, CanTransformWorldVectorToCameraSpace)
{
    CameraImplStub camera;
    Matrix4x4& transform = camera.GetTransform();

    Vector3 worldSpaceForward(0, 0, 1);
    Vector3 worldSpaceUp(0, 1, 0);
    Vector3 worldSpaceRight(1, 0, 0);

    // Camera at origin
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceForward), worldSpaceForward);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceUp), worldSpaceUp);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceRight), worldSpaceRight);

    Vector3 translation(1, -2.30, 5.234);
    transform = Transform::GetTranslationMatrix(translation);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceForward), worldSpaceForward);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceUp), worldSpaceUp);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceRight), worldSpaceRight);

    transform = Transform::GetTranslationMatrix(translation) * Transform::GetScaleMatrix({ 2.0, 2.0, -2.0 });
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceForward), Vector3(0, 0, -.5));
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceUp), Vector3(0, 0.5, 0));
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceRight), Vector3(0.5, 0, 0));

    transform = Transform::GetTranslationMatrix(translation) * Transform::GetRotationMatrix({ SMath::DegToRad(90.0), 0, 0 });
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceForward), worldSpaceUp);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceUp), -worldSpaceForward);
    EXPECT_EQ(camera.ToCameraSpace(worldSpaceRight), worldSpaceRight);
}

TEST(CameraTest, CanTransformWorldPointToCameraSpace)
{
    CameraImplStub camera;
    Matrix4x4& transform = camera.GetTransform();

    Point3 cameraSpaceForward(0, 0, 1);
    Point3 cameraSpaceUp(0, 1, 0);
    Point3 cameraSpaceRight(1, 0, 0);

    // Camera at origin
    EXPECT_EQ(camera.ToCameraSpace(cameraSpaceForward), cameraSpaceForward);
    EXPECT_EQ(camera.ToCameraSpace(cameraSpaceUp), cameraSpaceUp);
    EXPECT_EQ(camera.ToCameraSpace(cameraSpaceRight), cameraSpaceRight);

    Vector3 translation(1, -2.30, 5.234);
    transform = Transform::GetTranslationMatrix(translation);
    EXPECT_EQ(camera.ToCameraSpace(cameraSpaceForward), cameraSpaceForward - translation);
    EXPECT_EQ(camera.ToCameraSpace(cameraSpaceUp), cameraSpaceUp - translation);
    EXPECT_EQ(camera.ToCameraSpace(cameraSpaceRight), cameraSpaceRight - translation);
}

