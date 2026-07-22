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

#include "GeneralPreferences.h"

#include <QBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QFormLayout>

GeneralPreferences::GeneralPreferences(QWidget* parent) : QWidget(parent)
{
    auto* root_layout = new QVBoxLayout(this);

    auto* scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);

    auto* content = new QWidget(scroll_area);
    auto* content_layout = new QVBoxLayout(content);

    auto* startup_box = new QGroupBox("Startup", content);
    auto* startup_layout = new QFormLayout(startup_box);

    m_startup_WindowState_combo = new QComboBox();
    m_startup_WindowState_combo->setToolTip("Sets the window state at startup");
    m_startup_WindowState_combo->addItem("Minimized", static_cast<int>(Qt::WindowMinimized));
    m_startup_WindowState_combo->addItem("Normal", static_cast<int>(Qt::WindowNoState));
    m_startup_WindowState_combo->addItem("Maximized", static_cast<int>(Qt::WindowMaximized));
    m_startup_WindowState_combo->addItem("Full Screen", static_cast<int>(Qt::WindowFullScreen));

    m_startup_IsConsoleVisible_check = new QCheckBox();
    m_startup_IsConsoleVisible_check->setToolTip("Sets the console visibility at startup");

    startup_layout->addRow("Window state: ", m_startup_WindowState_combo);
    startup_layout->addRow("Show console: ", m_startup_IsConsoleVisible_check);

    content_layout->addWidget(startup_box);
    content_layout->addStretch();

    scroll_area->setWidget(content);

    root_layout->addWidget(scroll_area);
}

void GeneralPreferences::UpdatePreferences(const PreferencesData& preferencesData)
{
    m_startup_WindowState_combo->setCurrentIndex(
        m_startup_WindowState_combo->findData(
            static_cast<int>(preferencesData.startup_WindowState)
        )
    );
    m_startup_IsConsoleVisible_check->setChecked(
        preferencesData.startup_IsConsoleVisible
    );
}

void GeneralPreferences::ApplyPreferences(PreferencesData& preferencesData)
{
    preferencesData.startup_WindowState = static_cast<Qt::WindowStates>(
        m_startup_WindowState_combo->currentData().toInt()
    );
    preferencesData.startup_IsConsoleVisible = static_cast<bool>(
        m_startup_IsConsoleVisible_check->isChecked()
    );
}