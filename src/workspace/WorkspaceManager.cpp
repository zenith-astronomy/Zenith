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

#include "WorkspaceManager.h"

#include "../core/images/formats/fits.h"

WorkspaceManager::WorkspaceManager(ConsoleManager*& console_manager, QWidget* parent) : QStackedWidget(parent), m_console_manager(console_manager)
{
}

void WorkspaceManager::OpenFile(const Path& path)
{
    std::string ext = path.extension().string();

    if (ext == ".fits" || ext == ".fit" || ext == ".fts")
    {
        DisplayImage(Fits::Load(path));
        m_console_manager->AddEntry(QString("Opened %1").arg(path.string()).toStdString());
    }
    else
    {
        m_console_manager->AddEntry("Unknown file format", ERROR);
    }
}

void WorkspaceManager::OpenFiles(const std::vector<Path>& paths)
{
    try
    {
        for (const Path& path : paths)
        {
            OpenFile(path);
        }
    }
    catch (const std::exception& e)
    {
        m_console_manager->AddEntry(e.what(), ERROR);
    }

}

void WorkspaceManager::DisplayImage(const Image& image)
{
    WorkspaceView* workspace = GetWorkspace(currentIndex());

    if (!workspace) return;

    workspace->DisplayImage(image);
}

void WorkspaceManager::CreateWorkspace()
{
    auto* workspace = new WorkspaceView;
    addWidget(workspace);

    emit WorkspaceCreated();
}

void WorkspaceManager::DeleteWorkspace(int index)
{
    auto* workspace = GetWorkspace(index);

    if (!workspace) return;

    removeWidget(workspace);
    delete workspace;

    emit WorkspaceDeleted(index);
}

WorkspaceView* WorkspaceManager::GetWorkspace(int index) const
{
    return qobject_cast<WorkspaceView*>(widget(index));
}