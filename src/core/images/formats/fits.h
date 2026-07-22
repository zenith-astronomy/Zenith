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

#pragma once

#include <fitsio.h>

#include "../image.h"

namespace Fits
{
    class FitsFile
    {
    public:
        FitsFile(const Path& path)
        {
            int status = 0;

            if (fits_open_file(&fptr, path.string().c_str(), READONLY, &status))
            {
                throw std::runtime_error("Failed to open FITS file");
            }
        }

        ~FitsFile()
        {
            if (fptr)
            {
                int status = 0;
                fits_close_file(fptr, &status);
            }
        }

        fitsfile* GetFptr()
        {
            return fptr;
        }

    private:
        fitsfile* fptr = nullptr;
    };

    struct Info
    {
        std::size_t naxis1 = 1;
        std::size_t naxis2 = 1;
        std::size_t naxis3 = 1;
    };

    Info GetInfo(fitsfile* fptr);

    Image Load(const Path& path);
}

