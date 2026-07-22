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

#include <QSettings>

struct PreferencesData
{
    Qt::WindowStates startup_WindowState = Qt::WindowMaximized;
    bool startup_IsConsoleVisible = true;
};

class AppPreferences
{
public:
    AppPreferences();

    void Load(PreferencesData& data) const;
    void Save(PreferencesData& data);

private:
    QSettings m_preferences;
};
