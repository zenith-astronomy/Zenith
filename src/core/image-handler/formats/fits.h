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

#pragma once

#include <fitsio.h>
#include <longnam.h>
#include <stdexcept>

#include "../image.h"

namespace Fits
{
    class FitsFile
    {
    public:
        FitsFile(const Path& path, int mode = READWRITE)
        {
            int status = 0;

            std::string path_str = path.string();

            if (fits_open_file(&fptr, path_str.c_str(), mode, &status))
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

        FitsFile(const FitsFile&) = delete;
        FitsFile& operator=(const FitsFile&) = delete;

        fitsfile* get()
        {
            return fptr;
        }

    private:
        fitsfile* fptr = nullptr;
    };

    struct Info
    {
        int bitpix = -32;

        std::size_t naxis1 = 0;
        std::size_t naxis2 = 0;
        std::size_t naxis3 = 1;
    };

    Image Load(const Path& path);
}