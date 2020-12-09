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

#pragma once

#include "exporter.h"
#include <string>

class StbExporter : public Exporter
{
public:
    StbExporter();
    ~StbExporter() = default;

    void Export(const Film& film) const override;

    inline void SetOutputName(const std::string& name) { m_OutputFileName = name; }
    inline std::string GetOutputName() const { return m_OutputFileName; }

private:
    void ExtractPixelData(const Film& film, std::vector<char>& data) const;
    int GetBufferSize(const Film& film) const;

private:
    std::string m_OutputFileName;
};
