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

#include <QWidget>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>

class ConsoleView : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleView(QWidget* parent = nullptr);

    QListView* listView = nullptr;

signals:
    void CommandEntered(const std::string& input);

private:
    QLineEdit* m_lineEdit = nullptr;
    QPushButton* m_enter_button = nullptr;
};
