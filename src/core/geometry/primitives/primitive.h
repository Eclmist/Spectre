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

#pragma once

#include "core/geometry/geometry.h"

// TODO: Implement these stubs in the correct files
struct Interaction {

};

struct SurfaceInteraction : public Interaction {

};

struct MediumInteraction : public Interaction {

};

class Primitive
{
public:
    Primitive(Geometry* parentGeometry);
    virtual ~Primitive() = 0;

public:
    inline BoundingBox GetExtents() const { return m_BoundingBox; }

public:
    virtual Matrix4x4 GetTransform() const;

public:
    virtual bool Intersect(const Ray& ray) const = 0;
    virtual bool Intersect(const Ray& ray, double* tHit, SurfaceInteraction* surface) const = 0;

    virtual bool Sample(const Point2& uv, Interaction* interaction) const = 0;
    
protected:
    Geometry* m_ParentGeometry;
    BoundingBox m_BoundingBox;
};

