/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.

    RTCore is free software: you can redistribute it and/or modify
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

#include "stbexporter.h"
#include <vector>
#include "core/spectrum/sampledspectrum.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

const std::string OutputFileName = "RTCore_Output";
const std::string OutputFileType = ".png";
const long NumColorChannels = 3L;

StbExporter::StbExporter()
    : m_OutputFileName(OutputFileName)
{
}

void StbExporter::Export(const Film& film) const 
{
    stbi_write_png(
        (m_OutputFileName + OutputFileType).c_str(),
        film.GetResolution().GetWidth(),
        film.GetResolution().GetHeight(),
        NumColorChannels,
        ExtractPixelData(film).data(),
        NumColorChannels * film.GetResolution().GetWidth());
}

std::vector<char> StbExporter::ExtractPixelData(const Film& film) const
{
    std::vector<char> data(GetBufferSize(film));
    Resolution resolution = film.GetResolution();
    int iterator = 0;
    for (int y = 0; y < resolution.GetHeight(); ++y)
    {
        for (int x = 0; x < resolution.GetWidth(); ++x)
        {
            Pixel p = const_cast<Film&>(film).GetTile({ x, y }).GetFilmSpacePixel({ x, y });
            RgbCoefficients rgb = SampledSpectrum::XyzToRgb(p.m_Xyz);
            data[iterator++] = (char)(std::clamp(rgb[0] * 255.0, 0.0, 255.0));
            data[iterator++] = (char)(std::clamp(rgb[1] * 255.0, 0.0,  255.0));
            data[iterator++] = (char)(std::clamp(rgb[2] * 255.0, 0.0, 255.0));
        }
    }

    return data;
}

int StbExporter::GetBufferSize(const Film& film) const
{
    return film.GetNumPixels() * NumColorChannels;
}

