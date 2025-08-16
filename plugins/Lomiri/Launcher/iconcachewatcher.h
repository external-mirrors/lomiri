/*
 * Copyright (C) 2025 UBports Foundation
 * Author(s): Riccardo Riccio <riccardo.riccio@ubports.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QFileSystemWatcher>

class IconCacheWatcher : public QObject
{
    Q_OBJECT
public:
    explicit IconCacheWatcher(QObject *parent = nullptr);

Q_SIGNALS:
    void iconCacheChanged();

private Q_SLOTS:
    void onCacheFileChanged(const QString &path);

private:
    QFileSystemWatcher *m_watcher;
};
