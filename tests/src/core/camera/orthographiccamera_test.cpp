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
#include "core/camera/orthographiccamera.h"

TEST(OrthographicCameraTest, CanBeCreated)
{
    ASSERT_NO_THROW(OrthographicCamera());
}

TEST(OrthographicCameraTest, CanSetSize)
{
    OrthographicCamera camera1;
    EXPECT_DOUBLE_EQ(camera1.GetSize(), 1.0);

    OrthographicCamera camera2(1.2);
    EXPECT_DOUBLE_EQ(camera2.GetSize(), 1.2);
    
    ASSERT_NO_THROW(camera1.SetSize(1.4));
    EXPECT_DOUBLE_EQ(camera1.GetSize(), 1.4);
}

TEST(OrthographicCameraTest, HasDefaultSize)
{
    OrthographicCamera camera;
    EXPECT_DOUBLE_EQ(camera.GetSize(), 1.0);
}

TEST(OrthographicCameraTest, CanGenerateRay)
{
    OrthographicCamera camera;
    Ray topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    Ray centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    Ray bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_EQ(topLeftCornerRay.GetDirection(), Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.GetDirection(), Vector3(0, 0, 1));
    EXPECT_EQ(bottomRightRay.GetDirection(), Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.GetOrigin(), Point3(0, 0, 0));
    EXPECT_FALSE(bottomRightRay.GetOrigin() == Point3(0, 0, 0));
    EXPECT_FALSE(topLeftCornerRay.GetOrigin() == Point3(0, 0, 0));

    Matrix4x4& transform = camera.GetTransform();
    transform = Transform::GetTranslationMatrix({ 1, 0, 0 });

    topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_EQ(topLeftCornerRay.GetDirection(), Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.GetDirection(), Vector3(0, 0, 1));
    EXPECT_EQ(bottomRightRay.GetDirection(), Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.GetOrigin(), Point3(1, 0, 0));
    EXPECT_FALSE(bottomRightRay.GetOrigin() == Point3(1, 0, 0));
    EXPECT_FALSE(topLeftCornerRay.GetOrigin() == Point3(1, 0, 0));

    transform = transform * Transform::GetRotationMatrix({ 0, SMath::DegToRad(90.0), 0 });
    topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_EQ(topLeftCornerRay.GetDirection(), Vector3(1, 0, 0));
    EXPECT_EQ(centerRay.GetDirection(), Vector3(1, 0, 0));
    EXPECT_EQ(bottomRightRay.GetDirection(), Vector3(1, 0, 0));
    EXPECT_EQ(centerRay.GetOrigin(), Point3(1, 0, 0));
    EXPECT_FALSE(bottomRightRay.GetOrigin() == Point3(1, 0, 0));
    EXPECT_FALSE(topLeftCornerRay.GetOrigin() == Point3(1, 0, 0));
}

