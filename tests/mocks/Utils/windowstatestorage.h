/*
 * Copyright 2015-2016 Canonical Ltd.
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

#include <QObject>
#include <QVariantMap>
#include <QRect>

// lomiri-api
#include <lomiri/shell/application/Mir.h>

class WindowStateStorage: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
public:
    WindowStateStorage(QObject *parent = 0);

    Q_INVOKABLE void saveState(const QString &windowId, Mir::State state);
    Q_INVOKABLE Mir::State getState(const QString &windowId, Mir::State defaultValue) const;

    Q_INVOKABLE void saveGeometry(const QString &windowId, const QRect &rect);
    Q_INVOKABLE QRect getGeometry(const QString &windowId, const QRect &defaultValue) const;

    Q_INVOKABLE void saveStage(const QString &appId, int stage);
    Q_INVOKABLE int getStage(const QString &appId, int defaultValue) const;

    // Only in the mock, to easily restore a fresh state
    Q_INVOKABLE void clear();

Q_SIGNALS:
    void geometryChanged(const QVariantMap& geometry);

    // For testing.
    void stageSaved(const QString& appId, int stage);

private:
    void setGeometry(const QVariantMap& geometry);
    QVariantMap geometry() const;

    QHash<QString, Mir::State> m_state;
    QHash<QString, int> m_stage;
    QVariantMap m_geometry;
};
