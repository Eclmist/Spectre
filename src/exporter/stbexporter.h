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

#include "exporter.h"

class StbExporter : public Exporter
{
public:
    StbExporter();
    ~StbExporter() = default;

    void Export(const Film& film) const override;

    inline void SetOutputName(const std::string& name) { m_OutputFileName = name; }
    inline std::string GetOutputName() const { return m_OutputFileName; }

private:
    std::vector<char> ExtractPixelData(const Film& film) const;
    int GetBufferSize(const Film& film) const;

private:
    std::string m_OutputFileName;
    mutable std::mutex m_ExportMutex;
};
