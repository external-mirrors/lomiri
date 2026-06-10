/*
 * Copyright (C) 2026 UBports Foundation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "displaycutoutsmodel.h"

#include <QDebug>

DisplayCutoutsModel::DisplayCutoutsModel(QObject *parent) : QAbstractListModel(parent) { }

void DisplayCutoutsModel::setExpanded(bool value)
{
    if (m_expanded != value) {
        beginResetModel();
        m_expanded = value;
        endResetModel();
    }
}

void DisplayCutoutsModel::setOrientation(Qt::ScreenOrientation value)
{
    if (m_orientation != value) {
        beginResetModel();
        m_orientation = value;
        endResetModel();
    }
}

int DisplayCutoutsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (m_orientation != Qt::PortraitOrientation) {
        return 0;
    }
    return m_expanded ? m_expandedCutouts.count() : m_collapsedCutouts.count();
}

QVariant DisplayCutoutsModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    auto data = m_expanded ? &m_expandedCutouts : &m_collapsedCutouts;
    if (!index.isValid() || index.row() >= data->count()) {
        return {};
    }

    return QVariant(data->at(index.row()));
}
