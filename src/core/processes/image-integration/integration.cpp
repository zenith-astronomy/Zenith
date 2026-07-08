/*
    Zenith, astrophotography image processing software.
    Copyright (C) 2026 Stefano De Angelis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "integration.h"

#include <stdexcept>

#include "algorithms/average.h"

Image Integrate(const std::vector<Image>& frames, Algorithm alg, Rejection rej)
{
    Image result;

    // Assign the image information
    result.width = frames[0].width;
    result.height = frames[0].height;
    result.channels = frames[0].channels;

    // Resize and clear the pixels vector
    result.pixels.resize(result.width * result.height * result.channels);
    result.pixels.clear();

    switch (alg)
    {
        case AVERAGE:
        {
            Average::Integrate(frames, result, rej);
            break;
        }

        default:
        {
            throw std::runtime_error("Unsupported integration algorithm");
        }
    }

    return result;
}