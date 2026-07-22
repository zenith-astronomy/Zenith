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

#include "ConsoleManager.h"

#include <QApplication>

ConsoleManager::ConsoleManager(QWidget* parent) : QObject(parent)
{
    consoleModel = new ConsoleModel;
    consoleView = new ConsoleView;
    consoleView->listView->setModel(consoleModel);
}

void ConsoleManager::AddEntry(const std::string& message, const EntryType type)
{
    ConsoleEntry entry;

    entry.type = type;
    entry.timestamp = QDateTime::currentDateTime();
    entry.message = QString::fromStdString(message);

    consoleModel->AddEntry(entry);

    consoleView->listView->scrollToBottom();

    if (entry.type == ERROR)
    {
        emit ShowConsole();
    }
}