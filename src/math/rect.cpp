/*
    This file is part of RTCore, an open-source physically based
    renderer.

    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "rect.h"
#include <stdexcept>

Rect::Rect(int x, int y, int w, int h)
    : x(x)
    , y(y)
    , w(w)
    , h(h)
{
    if (w < 0 || h < 0)
        throw std::invalid_argument("Rects cannot have negative size");
}

bool Rect::IsWithinBounds(int _x, int _y) const
{
    return _x >= x && _x < (x + w) &&
           _y >= y && _y < (y + h);
}
