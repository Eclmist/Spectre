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

#include <atomic>

inline uint32_t FloatToBits(float f)
{
    uint32_t ui;
    memcpy(&ui, &f, sizeof(float));
    return ui;
}

inline float BitsToFloat(uint32_t ui)
{
    float f;
    memcpy(&f, &ui, sizeof(uint32_t));
    return f;
}

/*
 * std::atomic only supports Integral types as of C++17. C++20 adds floating
 * point support but Apple Clang as of (8/12/2020) does not support the feature.
*/
class AtomicFloat
{
public:
    AtomicFloat(float v = 0)
    {
        m_Bits = FloatToBits(v);
    };

    inline operator float() const { return BitsToFloat(m_Bits); };
    inline float operator=(float v) { m_Bits = FloatToBits(v); return v; };

    void Add(float v)
    {
        uint32_t oldBits = m_Bits, newBits;

        do
        {
            newBits = FloatToBits(BitsToFloat(oldBits) + v);
        } while (!m_Bits.compare_exchange_weak(oldBits, newBits));
    };

private:
    std::atomic<uint32_t> m_Bits;
};

