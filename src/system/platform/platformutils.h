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

#ifdef RTC_PLATFORM_WIN
    #define RTC_WIN32_ONLY(stmt, alt) stmt
#elif RTC_PLATFORM_MAC
    #define RTC_WIN32_ONLY(stmt, alt) alt
#else RTC_PLATFORM_LINUX
    #define RTC_WIN32_ONLY(stmt, alt) alt
#endif

