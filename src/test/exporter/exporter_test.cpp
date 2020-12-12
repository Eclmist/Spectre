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
#include "exporter/exporter.h"

class ExporterImplStub : public Exporter
{
public:
    void Export(const Film& film) const override {};
};

TEST(ExporterTest, CanBeCreated)
{
    ASSERT_NO_THROW(ExporterImplStub exporter);
}

TEST(ExporterTest, CanExport)
{
    Film film;
    ExporterImplStub exporter;
    ASSERT_NO_THROW(exporter.Export(film));
}
