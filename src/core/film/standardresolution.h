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

#include "resolution.h"

class Resolution640X360 : public Resolution
{
public:
    Resolution640X360()
    {
        m_Width = 640;
        m_Height = 360;
    };
};

class Resolution800X480: public Resolution
{
public:
    Resolution800X480()
    {
        m_Width = 800;
        m_Height = 480;
    };
};

class Resolution800X600 : public Resolution
{
public:
    Resolution800X600()
    {
        m_Width = 800;
        m_Height = 600;
    };
};

class Resolution1024X768 : public Resolution
{
public:
    Resolution1024X768()
    {
        m_Width = 1024;
        m_Height = 768;
    };
};

class Resolution1280X720 : public Resolution
{
public:
    Resolution1280X720()
    {
        m_Width = 1280;
        m_Height = 720;
    };
};

class Resolution1366X768 : public Resolution
{
public:
    Resolution1366X768()
    {
        m_Width = 1366;
        m_Height = 768;
    };
};

class Resolution1600X900 : public Resolution
{
public:
    Resolution1600X900()
    {
        m_Width = 1600;
        m_Height = 900;
    };
};
class Resolution1920X1080 : public Resolution
{
public:
    Resolution1920X1080()
    {
        m_Width = 1920;
        m_Height = 1080;
    };
};

class Resolution2560X1440 : public Resolution
{
public:
    Resolution2560X1440()
    {
        m_Width = 2560;
        m_Height = 1440;
    };
};

class Resolution3840X2160 : public Resolution
{
public:
    Resolution3840X2160()
    {
        m_Width = 3840;
        m_Height = 2160;
    };
};

