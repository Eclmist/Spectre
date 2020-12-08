/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2019 Samuel Van Allen - All rights reserved.

    Elixir is free software: you can redistribute it and/or modify
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

#include <iostream>
#include "googletest/gtest.h"

void PrintUsage()
{
    std::cout << "Usage: rtcore [options] <One or more scene files>\n\n";
    std::cout << "Rendering Options: \n";
    std::cout << "   -h, --help              Display this help page\n";
    std::cout << "Unit Tests: \n";
    std::cout << "   --unittest              Run unit tests\n";
    //std::cout << "For documentations, please refer to <http://docs.rtcore.io/>\n";

#ifdef RTC_PLATFORM_WIN
    system("Pause");
#endif
}

int main(int argc, char* argv[])
{
    // Process command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
        {
            PrintUsage();
            return -1;
        }
        else if (!strcmp(argv[i], "--unittest"))
        {
            testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
    }

#ifdef RTC_PLATFORM_WIN
    system("Pause");
#endif

    return EXIT_SUCCESS;
}
