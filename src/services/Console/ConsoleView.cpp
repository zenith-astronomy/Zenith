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

#include "ConsoleView.h"

#include <QBoxLayout>

ConsoleView::ConsoleView(QWidget* parent) : QWidget(parent)
{
    auto* root_layout = new QVBoxLayout(this);
    auto* input_layout = new QHBoxLayout();

    listView = new QListView;
    listView->setSelectionMode(QAbstractItemView::NoSelection);
    listView->setFocusPolicy(Qt::NoFocus);

    m_lineEdit = new QLineEdit;
    m_lineEdit->setPlaceholderText("Enter command");

    connect(m_lineEdit, &QLineEdit::returnPressed, this, [this]() {
        std::string input = m_lineEdit->text().trimmed().toStdString();

        if (!input.empty())
        {
            emit CommandEntered(input);
            m_lineEdit->clear();
        }
    });

    m_enter_button = new QPushButton("Enter");
    m_enter_button->setEnabled(!m_lineEdit->text().isEmpty());

    connect(m_enter_button, &QPushButton::clicked, this, [this]() {
        std::string input = m_lineEdit->text().trimmed().toStdString();

        if (!input.empty())
        {
            emit CommandEntered(input);
            m_lineEdit->clear();
        }
    });

    connect(m_lineEdit, &QLineEdit::textChanged, this, [this]() {
        m_enter_button->setEnabled(!m_lineEdit->text().isEmpty());
    });

    input_layout->addWidget(m_lineEdit);
    input_layout->addWidget(m_enter_button);

    root_layout->addWidget(listView);
    root_layout->addLayout(input_layout);
}