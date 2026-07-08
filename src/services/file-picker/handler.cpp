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

#include "handler.h"

#include <QFileDialog>

std::vector<Path> FilePicker::OpenFilePicker(QWidget* parent, Type type, bool allowMultiple, QString title)
{
    QStringList filePaths;
    std::vector<Path> paths;

    switch (type)
    {
    case NATIVE:
    {
        filePaths = QFileDialog::getOpenFileNames(
            parent,
            title,
            QString(),
            "All Files (*)"
            );
        break;
    }
    case CUSTOM:
    {
        throw std::runtime_error("Custom file picker not yet available");
        break;
    }
    default:
    {
        throw std::runtime_error("Couldn't open a file picker");
    }
    }

    for (const QString& filePath : std::as_const(filePaths))
    {
        paths.emplace_back(filePath.toStdString());
    }

    return paths;
}