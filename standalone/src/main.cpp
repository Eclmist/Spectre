/*
    This file is part of Spectre, an open-source physically based
    spectral raytracing library.

    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
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

#include <iostream>
#include <cstring>

void PrintTitle()
{
    using namespace std;
    cout << "Spectre Version 0.0.1";
    cout << ", Copyright (c) 2019-2023 Samuel Van Allen" << endl;
}

void PrintUsage(const char* msg = nullptr)
{
    if (msg)
        fprintf(stderr, "spectre: %s\n\n", msg);

    using namespace std;
    cout << "Usage: spectre [options] <One or more scene files>" << endl << endl;
    cout << "Rendering Options: " << endl;
    cout << "   -h, --help              Display this help page" << endl;
    cout << "   -t, --numthreads        Specify the number of rendering threads to use" << endl;
    cout << "   -o, --out <fname>       Write the output image to a specified filename" << endl;
    cout << "   -s, --stamp             Stamp output filename with metadata" << endl;
    cout << "   -q, --quick             Reduce output quality for quick render" << endl;
    cout << "   -d, --debug             Render debug scene defined in code. To be deprecated." << endl;
    cout << "Logging Options: " << endl;
    cout << "   --quiet                 Suppress all non-error messages" << endl;
    cout << "For documentations, please refer to <url>" << endl;

    SPC_WIN32_ONLY(system("PAUSE"));
}

int main(int argc, char* argv[])
{
    PrintTitle();

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
        {
            PrintUsage();
            return -1;
        }
        //else if (!strcmp(argv[i], "--numthreads") || !strcmp(argv[i], "-t"))
        //    options.numThreads = exrMax(options.numThreads, exrU32(atoi(argv[++i])));
        //else if (!strcmp(argv[i], "--out") || !strcmp(argv[i], "-o"))
        //    options.outputFile = argv[++i];
        //else if (!strcmp(argv[i], "--stamp") || !strcmp(argv[i], "-s"))
        //    options.stampFile = true;
        //else if (!strcmp(argv[i], "--quick") || !strcmp(argv[i], "-q"))
        //    options.quickRender = true;
        //else if (!strcmp(argv[i], "--quiet"))
        //    options.quiet = true;
        //else if (!strcmp(argv[i], "--debug") || !strcmp(argv[i], "-d"))
        //    options.debug = true;
        //else
        //    filenames.push_back(argv[i]);
    }


    return 0;
}