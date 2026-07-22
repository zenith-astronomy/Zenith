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

#include "ConsoleModel.h"

#include <QBrush>
#include <QColor>


ConsoleModel::ConsoleModel(QObject* parent) : QAbstractListModel(parent)
{

}

void ConsoleModel::AddEntry(const ConsoleEntry& entry)
{
    beginInsertRows({}, rowCount(), rowCount());
    m_entries.push_back(entry);
    endInsertRows();
}

void ConsoleModel::Clear()
{
    beginResetModel();
    m_entries.clear();
    endResetModel();
}

int ConsoleModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;

    return static_cast<int>(m_entries.size());
}

QVariant ConsoleModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return {};

    const ConsoleEntry& entry = m_entries[index.row()];

    switch (role)
    {
        case Qt::DisplayRole:
        {
            return QString("[%1] %2").arg(entry.timestamp.toString("hh:mm:ss"), entry.message);
        }
        case Qt::ForegroundRole:
        {
            switch (entry.type)
            {
                case DEFAULT:
                {
                    return QBrush(QColor(200, 200, 200));
                }
                case TIP:
                {
                    return QBrush(QColor(200, 50, 170));
                }
                case SUCCESS:
                {
                    return QBrush(QColor(50, 200, 50));
                }
                case WARNING:
                {
                    return QBrush(QColor(200, 150, 50));
                }
                case ERROR:
                {
                    return QBrush(QColor(200, 0, 0));
                }
                default:
                {
                    return QBrush(QColor(200, 200, 200));
                }
            }
        }
        default: return {};
    }
}