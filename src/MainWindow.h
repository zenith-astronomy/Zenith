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

#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QComboBox>
#include <QCloseEvent>
#include <QDockWidget>

#include "workspace/WorkspaceManager.h"

#include "services/Console/ConsoleManager.h"
#include "services/FilePicker/FilePickerManager.h"

#include "preferences/AppPreferences.h"
#include "preferences/PreferencesDialog.h"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);

    void toggleFullScreen();

    void openFiles();

    void ExecuteCommand(const std::string& input);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    WorkspaceManager* m_workspace_manager = nullptr;
    ConsoleManager* m_console_manager = nullptr;
    FilePickerManager* m_filepicker_manager = nullptr;

    QDockWidget* m_console_dock = nullptr;

    QAction* m_fullscreen_action = nullptr;

    QAction* m_createworkspace_action = nullptr;
    QAction* m_deleteworkspace_action = nullptr;

    QComboBox* m_workspace_combobox = nullptr;

    Qt::WindowStates m_previousState = Qt::WindowNoState;

    AppPreferences m_preferences;
    PreferencesData m_preferencesData;

    PreferencesDialog* m_PreferencesDialog = nullptr;
};
