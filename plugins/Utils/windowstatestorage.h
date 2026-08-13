/*
 * Copyright 2015-2016 Canonical Ltd.
 * Copyright 2021 UBports Foundation
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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QFuture>
#include <QThread>

// lomiri-api
#include <lomiri/shell/application/Mir.h>

class AsyncQuery;

class WindowStateStorage: public QObject
{
    Q_OBJECT
public:
    WindowStateStorage(const QString &dbName = QString(), QObject *parent = nullptr);
    virtual ~WindowStateStorage();

    Q_INVOKABLE Mir::State getState(const QString &windowId, Mir::State defaultValue) const;

    Q_INVOKABLE QRect getGeometry(const QString &windowId, const QRect &defaultValue) const;

    Q_INVOKABLE int getStage(const QString &appId, int defaultValue) const;

    const QString getDbName();

Q_SIGNALS:
    void saveStage(const QString &appId, int stage);
    void saveGeometry(const QString &windowId, const QRect &rect);
    void saveState(const QString &windowId, Mir::State state);

private:
    QThread m_thread;
    AsyncQuery *m_asyncQuery;
};
