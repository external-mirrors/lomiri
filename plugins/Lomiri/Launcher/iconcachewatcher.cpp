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
    // List of base directories
    QStringList baseDirs = {
        "/usr/share",
        "/usr/local/share",
        QDir::homePath() + "/.local/share"
    };

    QStringList cacheFiles;
    QStringList foldersToWatch;
    for (const QString &base : baseDirs) {
        // icons
        QString iconsDir = base + "/icons";
        QDir icons(iconsDir);
        if (icons.exists()) {
            foldersToWatch << iconsDir;
            QFileInfoList subdirs = icons.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
            for (const QFileInfo &subdir : subdirs) {
                QString cachePath = subdir.absoluteFilePath() + "/icon-theme.cache";
                if (QFile::exists(cachePath)) {
                    cacheFiles << cachePath;
                }
            }
        }
        // pixmaps
        QString pixmapsDir = base + "/pixmaps";
        QDir pixmaps(pixmapsDir);
        if (pixmaps.exists()) {
            foldersToWatch << pixmapsDir;
        }
        // meta/gui
        QString metaGuiDir = base + "/meta/gui";
        QDir metaGui(metaGuiDir);
        if (metaGui.exists()) {
            foldersToWatch << metaGuiDir;
        }
    }

    if (!cacheFiles.isEmpty()) {
        m_watcher->addPaths(cacheFiles);
        connect(m_watcher, &QFileSystemWatcher::fileChanged,
                this, &IconCacheWatcher::onCacheFileChanged);
    }

    if (!foldersToWatch.isEmpty()) {
        m_watcher->addPaths(foldersToWatch);
        connect(m_watcher, &QFileSystemWatcher::directoryChanged,
                this, &IconCacheWatcher::onIconDirectoryChanged);
    }

    if (foldersToWatch.isEmpty() && cacheFiles.isEmpty()) {
        qWarning() << "No icon-theme.cache files found in standard icon directories.";
    } else {
        qDebug() << "IconCacheWatcher initialized with" << foldersToWatch.size() << "directories and"
                 << cacheFiles.size() << "cache files.";
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

void IconCacheWatcher::onIconDirectoryChanged(const QString &path)
{
    // Defer update if dpkg-new files are present (icon is still being installed)
    QDir dir(path);
    QStringList dpkgNewFiles = dir.entryList(QStringList("*.dpkg-new"), QDir::Files);
    if (!dpkgNewFiles.isEmpty())
        return;

    Q_EMIT iconCacheChanged();
}
