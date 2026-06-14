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

#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QRect>

class DisplayCutoutsModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool expanded WRITE setExpanded)
    Q_PROPERTY(Qt::ScreenOrientation orientation WRITE setOrientation)
    Q_PROPERTY(bool enabled WRITE setEnabled)
    Q_PROPERTY(bool lightMode WRITE setLightMode)

public:
    DisplayCutoutsModel(QObject *parent = nullptr);
    ~DisplayCutoutsModel() = default;

    void setExpanded(bool value);
    void setOrientation(Qt::ScreenOrientation value);
    void setEnabled(bool value);
    void setLightMode(bool lightMode);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public Q_SLOTS:
    void reloadConfig();

private:
    bool m_expanded{false};
    bool m_enabled{true};
    bool m_lightMode{false};
    QList<QRect> m_expandedCutouts;
    QList<QRect> m_collapsedCutouts;
    QList<QRect> m_collapsedLightCutouts;
    Qt::ScreenOrientation m_orientation;

    void loadConfig();
};
