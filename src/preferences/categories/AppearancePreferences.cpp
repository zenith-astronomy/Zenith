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

#include "AppearancePreferences.h"

#include <QBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QFormLayout>

AppearancePreferences::AppearancePreferences(QWidget* parent) : QWidget(parent)
{
    auto* root_layout = new QVBoxLayout(this);

    auto* scroll_area = new QScrollArea(this);
    scroll_area->setWidgetResizable(true);

    auto* content = new QWidget(scroll_area);
    auto* content_layout = new QVBoxLayout(content);

    auto* startup_box = new QGroupBox("Colours", content);
    auto* startup_layout = new QFormLayout(startup_box);

    content_layout->addWidget(startup_box);
    content_layout->addStretch();

    scroll_area->setWidget(content);

    root_layout->addWidget(scroll_area);
}

void AppearancePreferences::UpdatePreferences(const PreferencesData& preferencesData)
{
}

void AppearancePreferences::ApplyPreferences(PreferencesData& preferencesData)
{
}