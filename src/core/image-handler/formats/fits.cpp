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

#include "fits.h"

namespace Fits
{
    Info GetInfo(fitsfile* fptr)
    {
        Info info = {};

        int status = 0;

        fits_read_key(fptr, TINT,  "BITPIX", &info.bitpix, nullptr, &status);
        
        fits_read_key(fptr, TINT, "NAXIS1", &info.naxis1, nullptr, &status);
        fits_read_key(fptr, TINT, "NAXIS2", &info.naxis2, nullptr, &status);
        fits_read_key(fptr, TINT, "NAXIS3", &info.naxis3, nullptr, &status);

        return info;
    }

    Image Load(const Path& path)
    {
        FitsFile file(path);
        fitsfile* fptr = file.get();

        Image image;

        return image;
    }
}