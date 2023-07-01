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

#include "accelerator.h"

constexpr uint32_t MaxTreeDepth = 8;
constexpr uint32_t MaxNumNodes = 65536; // 4^MaxTreeDepth

struct SimdQBvhNode
{
    BoundingBox m_ChildBoundingBoxes;
    uint32_t m_ChildIndices[4];
    uint32_t m_Axis0, m_Axis1, m_Axis2;
};

class QBvhAccelerator : public Accelerator
{
public:
    QBvhAccelerator() = default;
    ~QBvhAccelerator() override = default;

public:
    void Build(const std::vector<Primitive>& primitives) const override;
    void Intersect(const Ray& ray) const override;

protected:
    SimdQBvhNode m_RootNode[MaxNumNodes];
};

