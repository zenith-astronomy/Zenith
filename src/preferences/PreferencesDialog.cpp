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

#include "PreferencesDialog.h"

#include <QBoxLayout>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QPushButton>
#include <QDialogButtonBox>

PreferencesDialog::PreferencesDialog(PreferencesData& preferencesData, QWidget* parent) : QDialog(parent), m_PreferencesData(preferencesData)
{
    setWindowTitle("Preferences");
    resize(600, 400);

    auto* root_layout = new QVBoxLayout(this);
    auto* content_layout = new QHBoxLayout();

    auto* categories_buttons = new QButtonGroup();
    categories_buttons->setExclusive(true);

    auto* general_button = new QPushButton("General");
    auto* appearance_button = new QPushButton("Appearance");

    general_button->setCheckable(true);
    appearance_button->setCheckable(true);

    categories_buttons->addButton(general_button, 0);
    categories_buttons->addButton(appearance_button, 1);

    general_button->setChecked(true);

    auto* categories_widget = new QWidget(this);
    auto* categories_layout = new QVBoxLayout(categories_widget);
    categories_layout->addWidget(general_button);
    categories_layout->addWidget(appearance_button);
    categories_layout->addStretch();

    auto* categories_view = new QStackedWidget();

    m_GeneralPreferences = new GeneralPreferences(this);
    m_AppearancePreferences = new AppearancePreferences(this);

    categories_view->addWidget(m_GeneralPreferences);
    categories_view->addWidget(m_AppearancePreferences);

    categories_view->setCurrentIndex(0);

    connect(categories_buttons, &QButtonGroup::idClicked, categories_view, &QStackedWidget::setCurrentIndex);

    auto* dialog_buttons = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Apply
    );

    connect(dialog_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(dialog_buttons->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &PreferencesDialog::ApplyPreferences);

    content_layout->addWidget(categories_widget);
    content_layout->addWidget(categories_view);

    root_layout->addLayout(content_layout);
    root_layout->addWidget(dialog_buttons);
}

void PreferencesDialog::UpdatePreferences()
{
    m_GeneralPreferences->UpdatePreferences(m_PreferencesData);
}

void PreferencesDialog::ApplyPreferences()
{
    m_GeneralPreferences->ApplyPreferences(m_PreferencesData);
}