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

#include "AppPreferences.h"

namespace
{
    constexpr auto key_startup_WindowState = "startup/WindowState";
    constexpr auto key_startup_IsConsoleVisible = "startup/IsConsoleVisible";
}

AppPreferences::AppPreferences() : m_preferences()
{

}

void AppPreferences::Load(PreferencesData& data) const
{
    data.startup_WindowState = static_cast<Qt::WindowStates>(m_preferences.value(key_startup_WindowState, static_cast<int>(data.startup_WindowState)).toInt());
    data.startup_IsConsoleVisible = static_cast<bool>(m_preferences.value(key_startup_IsConsoleVisible, static_cast<bool>(data.startup_IsConsoleVisible)).toBool());
}

void AppPreferences::Save(PreferencesData& data)
{
    m_preferences.setValue(key_startup_WindowState, static_cast<int>(data.startup_WindowState));
    m_preferences.setValue(key_startup_IsConsoleVisible, static_cast<bool>(data.startup_IsConsoleVisible));
}