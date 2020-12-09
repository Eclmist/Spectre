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

#include "stbexporter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <vector>

#define DEFAULT_OUTPUT_NAME "RTCore_Output"

StbExporter::StbExporter()
    : m_OutputFileName(DEFAULT_OUTPUT_NAME)
{
}

void StbExporter::Export(const Film& film) const 
{
    // TEMP CODE
    std::vector<char> data(800 * 460 * 3);
    int iterator = 0;

    for (int y = 0; y < 460; ++y)
        for (int x = 0; x < 800; ++x)
        {
            data[iterator++] = (x + 1) / 800.0f * 255.0f;
            data[iterator++] = (1.0 - ((y + 1) / 460.0f)) * 255.0f;
            data[iterator++] = 255.0f;
        }

    std::string outputWithFileExtension = m_OutputFileName + ".png";
    stbi_write_png(outputWithFileExtension.c_str(), 800, 460, 3, data.data(), 3 * 800);
    system(m_OutputFileName.c_str());
    // TEMP CODE
}

