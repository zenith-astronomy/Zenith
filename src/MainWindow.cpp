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

#include "MainWindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>

#include "dialogs/AboutZenithDialog.h"
#include "dialogs/AboutQtDialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Zenith");
    resize(900, 600);


    // PREFERENCES

    // Load the preferences from disk
    m_preferences.Load(m_preferencesData);

    // Create the preferences dialog
    m_PreferencesDialog = new PreferencesDialog(m_preferencesData, this);


    // MANAGERS

    // Create the file picker manager
    m_filepicker_manager = new FilePickerManager;

    // Create the console manager
    m_console_manager = new ConsoleManager(this);
    auto* console_view = m_console_manager->consoleView;

    m_console_dock = new QDockWidget("Console", this);
    m_console_dock->setWidget(console_view);

    connect(console_view, &ConsoleView::CommandEntered, this, &MainWindow::ExecuteCommand);
    connect(m_console_manager, &ConsoleManager::ShowConsole, this, [this]() {
        m_console_dock->show();
    });

    m_console_dock->setVisible(m_preferencesData.startup_IsConsoleVisible);

    addDockWidget(Qt::RightDockWidgetArea, m_console_dock);

    m_console_dock->setFeatures(
        QDockWidget::DockWidgetMovable |
        QDockWidget::DockWidgetClosable
    );

    // Create the workspace manager
    m_workspace_manager = new WorkspaceManager(m_console_manager, this);
    setCentralWidget(m_workspace_manager);


    // ACTIONS

    // File actions
    auto* openfiles_action = new QAction(this);
    openfiles_action->setIcon(QIcon(":/resources/icons/open.svg"));
    openfiles_action->setText("Opens a file");

    connect(openfiles_action, &QAction::triggered, this, &MainWindow::openFiles);

    // View actions
    m_fullscreen_action = new QAction("Full Screen", this);
    m_fullscreen_action->setCheckable(true);
    connect(m_fullscreen_action, &QAction::triggered, this, &MainWindow::toggleFullScreen);

    // Workspace actions
    m_createworkspace_action = new QAction(this);
    m_createworkspace_action->setIcon(QIcon(":/resources/icons/plus.svg"));
    m_createworkspace_action->setText("Create new workspace");

    connect(m_createworkspace_action, &QAction::triggered, this, [this]() {
        m_workspace_manager->CreateWorkspace();
        m_console_manager->AddEntry("Created a new workspace");
    });
    m_createworkspace_action->setToolTip("Creates a new workspace");

    m_deleteworkspace_action = new QAction(this);
    m_deleteworkspace_action->setIcon(QIcon(":/resources/icons/minus.svg"));
    m_deleteworkspace_action->setText("Delete current workspace");

    connect(m_deleteworkspace_action, &QAction::triggered, this, [this]() {
        m_workspace_manager->DeleteWorkspace(m_workspace_manager->currentIndex());
        m_console_manager->AddEntry("Deleted the workspace");
    });
    m_deleteworkspace_action->setToolTip("Deletes the current workspace");


    // MENUS

    // File menu
    auto* file_menu = menuBar()->addMenu("File");

    file_menu->addAction(openfiles_action);
    file_menu->addSeparator();
    auto* exit_action = file_menu->addAction("Exit");
    connect(exit_action, &QAction::triggered, this, &MainWindow::close);

    // Edit menu
    auto* edit_menu = menuBar()->addMenu("Edit");

    auto* preferences_action = edit_menu->addAction("Preferences");
    connect(preferences_action, &QAction::triggered, this, [this]() {
        // Read the preferences stored in disk
        m_PreferencesDialog->UpdatePreferences();
        // Open the preferences dialog
        m_PreferencesDialog->exec();
        // Update the preferences
        m_preferences.Save(m_preferencesData);
    });

    // View menu
    auto* view_menu = menuBar()->addMenu("View");

    view_menu->addAction(m_fullscreen_action);

    // Workspace menu
    auto* workspace_menu = menuBar()->addMenu("Workspace");

    workspace_menu->addAction(m_createworkspace_action);

    workspace_menu->addAction(m_deleteworkspace_action);

    // Help menu
    auto* help_menu = menuBar()->addMenu("Help");

    auto* about_action = help_menu->addAction("About Zenith");
    connect(about_action, &QAction::triggered, this, [this]() {
        AboutZenithDialog dialog(this);
        dialog.exec();
    });
    auto* aboutqt_action = help_menu->addAction("About Qt");
    connect(aboutqt_action, &QAction::triggered, this, [this]() {
        AboutQtDialog dialog(this);
        dialog.exec();
    });


    // TOOLBARS

    // File toolbar
    auto* file_toolbar = addToolBar("File");

    file_toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    file_toolbar->addAction(openfiles_action);

    // Edit toolbar
    auto* edit_toolbar = addToolBar("Edit");

    // View toolbar
    auto* view_toolbar = addToolBar("View");

    view_toolbar->addAction(m_fullscreen_action);

    // Workspace toolbar
    auto* workspace_toolbar = addToolBar("Workspace");

    workspace_toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    workspace_toolbar->addAction(m_createworkspace_action);
    workspace_toolbar->addAction(m_deleteworkspace_action);
    m_workspace_combobox = new QComboBox(this);
    workspace_toolbar->addWidget(m_workspace_combobox);
    connect(m_workspace_combobox, &QComboBox::currentIndexChanged, m_workspace_manager, &WorkspaceManager::setCurrentIndex);
    connect(m_workspace_manager, &QStackedWidget::currentChanged, m_workspace_combobox, &QComboBox::setCurrentIndex);
    connect(m_workspace_manager, &WorkspaceManager::WorkspaceCreated, this, [this]() {
        m_workspace_combobox->addItem(QString("Workspace"));
        m_deleteworkspace_action->setEnabled(m_workspace_manager->count() > 1);
    });
    connect(m_workspace_manager, &WorkspaceManager::WorkspaceDeleted, this, [this](int index) {
        m_workspace_combobox->removeItem(index);
        m_deleteworkspace_action->setEnabled(m_workspace_manager->count() > 1);
    });

    setWindowState(m_preferencesData.startup_WindowState);

    if (isFullScreen())
    {
        m_fullscreen_action->setChecked(true);
        m_fullscreen_action->setToolTip("Exits full screen mode");
    }
    else
    {
        m_fullscreen_action->setChecked(false);
        m_fullscreen_action->setToolTip("Enters full screen mode");
    }

    m_workspace_manager->CreateWorkspace();

    m_console_manager->AddEntry("Zenith initialized", SUCCESS);
}

void MainWindow::toggleFullScreen()
{
    if (isFullScreen())
    {
        showNormal();

        if (m_previousState == Qt::WindowMaximized)
        {
            showMaximized();
        }

        m_fullscreen_action->setChecked(false);
        m_fullscreen_action->setToolTip("Enters full screen mode");
    }
    else
    {
        m_previousState = windowState();
        showFullScreen();

        m_fullscreen_action->setChecked(true);
        m_fullscreen_action->setToolTip("Exits full screen mode");
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    bool HasUnsavedChanges = false;

    if (!HasUnsavedChanges)
    {
        event->accept();
        return;
    }

    auto result = QMessageBox::question(this, "Unsaved changes", "There are unsaved changes. Do you want to exit without saving?", QMessageBox::Ok | QMessageBox::Cancel);

    switch (result)
    {
        case QMessageBox::Ok:
        {
            event->accept();
            break;
        }
        case QMessageBox::Cancel:
        {
            event->ignore();
            break;
        }
        default:
        {
            event->ignore();
        }
    }
}

void MainWindow::openFiles()
{
    std::vector<Path> paths = m_filepicker_manager->OpenFilePicker();
    m_workspace_manager->OpenFiles(paths);
}

void MainWindow::ExecuteCommand(const std::string& input)
{
    std::istringstream stream(input);
    std::string cmd;
    std::string token;
    stream >> cmd;

    m_console_manager->AddEntry("> " + input, DEFAULT);

    if (cmd == "help")
    {

    }
    else if (cmd == "exit" || cmd == "quit")
    {
        MainWindow::close();
    }
    else if (cmd == "fs")
    {
        MainWindow::toggleFullScreen();
    }
    else if (cmd == "maximize")
    {
        MainWindow::showMaximized();
    }
    else if (cmd == "restore")
    {
        MainWindow::showNormal();
    }
    else if (cmd == "minimize")
    {
        MainWindow::showMinimized();
    }
    else if (cmd == "open")
    {
        if (!(stream >> token))
        {
            MainWindow::openFiles();
        }
    }
    else if (cmd == "clear")
    {
        m_console_manager->consoleModel->Clear();
    }
    else if (cmd == "hide")
    {
        m_console_dock->hide();
    }
    else
    {
        m_console_manager->AddEntry("Unknown command \'" + cmd + "\'", ERROR);
        m_console_manager->AddEntry("Type \'help\' for a list of available commands", TIP);
    }
}