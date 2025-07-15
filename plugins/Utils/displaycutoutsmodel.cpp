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
#include <deviceinfo.h>

QRect parseRect(QString rect)
{
    auto parts = rect.split(",");
    if (parts.size() != 4) {
        return QRect();
    }
    return QRect(
        parts[0].toInt(), parts[1].toInt(),
        parts[2].toInt(), parts[3].toInt()
    );
}

DisplayCutoutsModel::DisplayCutoutsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    DeviceInfo info;
    if (!info.contains("DisplayCutouts")) {
        qWarning() << "DisplayCutouts not configured, not enabling";
        return;
    }

    auto cutouts = QString::fromStdString(info.get("DisplayCutouts", ""));
    auto parts = cutouts.split(";");
    if (parts.size() != 3) {
        qWarning() << "invalid DisplayCutouts config" << cutouts;
        return;
    }
    for (auto cutout : parts[1].split("/")) {
        m_collapsedCutouts.append(parseRect(cutout));
    }
    for (auto cutout : parts[2].split("/")) {
        m_expandedCutouts.append(parseRect(cutout));
    }
}

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
