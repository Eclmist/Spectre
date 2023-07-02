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
#include "core/camera/perspectivecamera.h"

TEST(PerspectiveCameraTest, CanBeCreated)
{
    ASSERT_NO_THROW(PerspectiveCamera());
}

TEST(PerspectiveCameraTest, CanSetFov)
{
    PerspectiveCamera camera1;
    EXPECT_DOUBLE_EQ(camera1.GetHorizontalFov(), 75);

    PerspectiveCamera camera2(1.2);
    EXPECT_DOUBLE_EQ(camera2.GetHorizontalFov(), 1.2);
    
    ASSERT_NO_THROW(camera1.SetHorizontalFov(1.4));
    EXPECT_DOUBLE_EQ(camera1.GetHorizontalFov(), 1.4);
}

TEST(PerspectiveCameraTest, HasDefaultFov)
{
    PerspectiveCamera camera;
    EXPECT_DOUBLE_EQ(camera.GetHorizontalFov(), 75.0);
}

TEST(PerspectiveCameraTest, CanGenerateRay)
{
    PerspectiveCamera camera;
    Ray topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    Ray centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    Ray bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_FALSE(topLeftCornerRay.m_Direction == Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.m_Direction, Vector3(0, 0, 1));
    EXPECT_FALSE(bottomRightRay.m_Direction == Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.m_Origin, Point3(0, 0, 0));
    EXPECT_EQ(bottomRightRay.m_Origin, Point3(0, 0, 0));
    EXPECT_EQ(topLeftCornerRay.m_Origin, Point3(0, 0, 0));

    Matrix4x4& transform = camera.GetTransform();
    transform = Transform::GetTranslationMatrix({ 1, 0, 0 });
    topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_FALSE(topLeftCornerRay.m_Direction == Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.m_Direction, Vector3(0, 0, 1));
    EXPECT_FALSE(bottomRightRay.m_Direction == Vector3(0, 0, 1));
    EXPECT_EQ(centerRay.m_Origin, Point3(1, 0, 0));
    EXPECT_EQ(bottomRightRay.m_Origin, Point3(1, 0, 0));
    EXPECT_EQ(topLeftCornerRay.m_Origin, Point3(1, 0, 0));

    transform = transform * Transform::GetRotationMatrix({ 0, SMath::DegToRad(90.0), 0 });
    topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_FALSE(topLeftCornerRay.m_Direction == Vector3(1, 0, 0));
    EXPECT_EQ(centerRay.m_Direction, Vector3(1, 0, 0));
    EXPECT_FALSE(bottomRightRay.m_Direction == Vector3(1, 0, 0));
    EXPECT_EQ(centerRay.m_Origin, Point3(1, 0, 0));
    EXPECT_EQ(bottomRightRay.m_Origin, Point3(1, 0, 0));
    EXPECT_EQ(topLeftCornerRay.m_Origin, Point3(1, 0, 0));
}

TEST(PerspectiveCameraTest, GeneratedRayIsNormalized)
{
    PerspectiveCamera camera;
    Ray topLeftCornerRay = camera.GenerateRay({ 0, 0 });
    Ray centerRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth() / 2,
        camera.GetFilm().GetResolution().GetHeight() / 2 });
    Ray bottomRightRay = camera.GenerateRay({
        camera.GetFilm().GetResolution().GetWidth(),
        camera.GetFilm().GetResolution().GetHeight() });

    EXPECT_EQ(topLeftCornerRay.m_Direction, topLeftCornerRay.m_Direction.Normalized());
    EXPECT_EQ(centerRay.m_Direction, centerRay.m_Direction.Normalized());
    EXPECT_EQ(bottomRightRay.m_Direction, bottomRightRay.m_Direction.Normalized());
}


