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

#include "iconcachewatcher.h"

#include <QDebug>
#include <QDir>
#include <QFile>

IconCacheWatcher::IconCacheWatcher(QObject *parent)
    : QObject(parent),
      m_watcher(new QFileSystemWatcher(this))
{
    // Standard icon directories
    QStringList iconDirs = {
        "/usr/share/icons",
        "/usr/local/share/icons",
        QDir::homePath() + "/.local/share/icons"
    };

    QStringList cacheFiles;
    for (const QString &dir : iconDirs) {
        QDir d(dir);
        if (!d.exists()) continue;
        // Look for icon-theme.cache in all subdirs
        QFileInfoList subdirs = d.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QFileInfo &subdir : subdirs) {
            QString cachePath = subdir.absoluteFilePath() + "/icon-theme.cache";
            if (QFile::exists(cachePath)) {
                cacheFiles << cachePath;
            }
        }
    }

    if (cacheFiles.isEmpty()) {
        qWarning() << "No icon-theme.cache files found in standard icon directories.";
    } else {
        m_watcher->addPaths(cacheFiles);
        connect(m_watcher, &QFileSystemWatcher::fileChanged,
                this, &IconCacheWatcher::onCacheFileChanged);
    }
}

void IconCacheWatcher::onCacheFileChanged(const QString &path)
{
    Q_EMIT iconCacheChanged();
    // Re-add the path in case the file was recreated
    if (QFile::exists(path)) {
        m_watcher->addPath(path);
    }
}
