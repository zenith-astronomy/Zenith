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

#include <QStackedWidget>

#include "WorkspaceView.h"

#include "../services/Console/ConsoleManager.h"

#include "../core/types.h"
#include "../core/images/image.h"

class WorkspaceManager : public QStackedWidget
{
    Q_OBJECT

public:
    explicit WorkspaceManager(ConsoleManager*& console_manager, QWidget* parent = nullptr);

    void OpenFile(const Path& path);
    void OpenFiles(const std::vector<Path>& paths);

    void DisplayImage(const Image& image);

    void CreateWorkspace();
    void DeleteWorkspace(int index);

    WorkspaceView* GetWorkspace(int index) const;

signals:
    void WorkspaceCreated();
    void WorkspaceDeleted(int index);

private:
    ConsoleManager* m_console_manager = nullptr;
};
