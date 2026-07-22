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

#include <QAbstractListModel>
#include <QDateTime>

enum EntryType
{
    DEFAULT,
    TIP,
    SUCCESS,
    WARNING,
    ERROR
};

struct ConsoleEntry
{
    EntryType type;
    QDateTime timestamp;
    QString message;
};

class ConsoleModel : public QAbstractListModel
{
public:
    explicit ConsoleModel(QObject* parent = nullptr);

    void AddEntry(const ConsoleEntry& entry);
    void Clear();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    std::vector<ConsoleEntry> m_entries;
};
