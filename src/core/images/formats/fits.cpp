/*
    Zenith, astrophotography image processing software
    Copyright (C) 2026 Stefano De Angelis and contributors (see AUTHORS file)

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

#include "fits.h"

#include <longnam.h>

Fits::Info Fits::GetInfo(fitsfile* fptr)
{
    Info info = {};

    int status = 0;

    fits_read_key(fptr, TINT, "NAXIS1", &info.naxis1, nullptr, &status);
    fits_read_key(fptr, TINT, "NAXIS2", &info.naxis2, nullptr, &status);
    fits_read_key(fptr, TINT, "NAXIS3", &info.naxis3, nullptr, &status);

    return info;
}

Image Fits::Load(const Path& path)
{
    FitsFile fits(path);
    fitsfile* fptr = fits.GetFptr();

    Info info = GetInfo(fptr);
    std::size_t pixelCount = info.naxis1 * info.naxis2 * info.naxis3;

    std::vector<float> pixels(pixelCount);

    int status = 0;

    long fpixel[3] = {1, 1, 1};

    fits_read_pix(fptr, TFLOAT, fpixel, pixelCount, nullptr, pixels.data(), nullptr, &status);

    Image image;

    image.width = info.naxis1;
    image.height = info.naxis2;
    image.channels = info.naxis3;
    image.pixels = pixels;

    return image;
}