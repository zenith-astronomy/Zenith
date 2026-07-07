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

#include "MainWindow.h"

#include <QApplication>
#include <QMenuBar>

#include "dialogs/AboutZenithDialog.h"
#include "dialogs/AboutQtDialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Zenith");
    resize(900, 600);
    show();

    // File menu
    auto* file_menu = menuBar()->addMenu("File");

    auto* quit_action = file_menu->addAction("Quit");
    connect(quit_action, &QAction::triggered, this, &MainWindow::close);

    // Edit menu
    auto* edit_menu = menuBar()->addMenu("Edit");

    auto* undo_action = edit_menu->addAction("Undo");
    auto* redo_action = edit_menu->addAction("Redo");
    edit_menu->addSeparator();
    auto* preferences_action = edit_menu->addAction("Preferences");

    // View menu
    auto* view_menu = menuBar()->addMenu("View");

    auto* fullscreen_action = view_menu->addAction("Full Screen");
    connect(fullscreen_action, &QAction::triggered, this, &MainWindow::toggleFullScreen);

    // Help menu
    auto* help_menu = menuBar()->addMenu("Help");

    auto* zenith_action = help_menu->addAction("About Zenith");
    connect(zenith_action, &QAction::triggered, this, [this]() {
        AboutZenithDialog dialog(this);
        dialog.exec();
    });
    auto* qt_action = help_menu->addAction("About Qt");
    connect(qt_action, &QAction::triggered, this, [this]() {
        AboutQtDialog dialog(this);
        dialog.exec();
    });
}

void MainWindow::toggleFullScreen()
{
    if (isFullScreen())
    {
        showMaximized();
    }
    else
    {
        showFullScreen();
    }
}