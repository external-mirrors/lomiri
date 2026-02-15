/*
 * Copyright (C) 2015-2016 Canonical Ltd.
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
 *
 */

#include "SessionsModel.h"
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QLoggingCategory>
#include <QtCore/QSortFilterProxyModel>

Q_LOGGING_CATEGORY(SessionsModelLogger, "lomiri.plugins.LightDM.SessionsModel")

QHash<int, QByteArray> SessionsModel::roleNames() const
{
    return m_roleNames;
}

int SessionsModel::rowCount(const QModelIndex& parent) const
{
    return m_model->rowCount(parent);
}

QList<QUrl> SessionsModel::iconSearchDirectories() const
{
    return m_iconSearchDirectories;
}

void SessionsModel::setIconSearchDirectories(const QList<QUrl> searchDirectories)
{
    // QML gives us a url with file:// prepended which breaks QFile::exists()
    // so convert the url to a local file
    QList<QUrl> localList = {};
    Q_FOREACH(const QUrl& searchDirectory, searchDirectories)
    {
        localList.append(searchDirectory.toLocalFile());
    }
    m_iconSearchDirectories = localList;
    Q_EMIT iconSearchDirectoriesChanged();
}

QUrl SessionsModel::iconUrl(const QString sessionKey) const
{
    const QStringList imgExtensions { "svg", "png" };
    for (const QUrl& searchDirectory : m_iconSearchDirectories)
    {
        for (const QString& imgExt : imgExtensions)
        {
            // This is an established icon naming convention
            QString customIconUrl = searchDirectory.toString(QUrl::StripTrailingSlash) +
                "/custom_" + sessionKey  + "_badge." + imgExt;
            QString iconUrl = searchDirectory.toString(QUrl::StripTrailingSlash) +
                "/" + sessionKey  + "_badge." + imgExt;

            QFile customIconFile(customIconUrl);
            QFile iconFile(iconUrl);
            if (customIconFile.exists()) {
                qCWarning(SessionsModelLogger) << "Found custom session badge icon: " << customIconUrl;
                return QUrl(customIconUrl);
            } else if (iconFile.exists()) {
                qCWarning(SessionsModelLogger) << "Found session badge icon: " << iconUrl;
                return QUrl(iconUrl);
            } else {
                qCWarning(SessionsModelLogger) << "Failed to find icon file: " << iconUrl;
            }
            // Skip the legacy part for .svg image extension... (SVGs have never been shipped in
            // lomiri sources, they only exist in ayatana-greeter-badges).
            if (imgExt == "png") {

                qCWarning(SessionsModelLogger) << "Trying legacy mechanism for finding an appropriate icon file.";

                // Search the legacy way, only needed if ayatana-greeter-badges is not used
                // as session icon badge source.
                QString path = searchDirectory.toString(QUrl::StripTrailingSlash) + "/";
                bool iconFound = false;
                if (sessionKey == "ubuntu" || sessionKey == "ubuntu-2d") {
                    path += "ubuntu_badge.png";
                    iconFound = true;
                } else if(
                            sessionKey == "gnome-classic" ||
                            sessionKey == "gnome-flashback-compiz" ||
                            sessionKey == "gnome-flashback-metacity" ||
                            sessionKey == "gnome-shell" ||
                            sessionKey == "gnome-wayland" ||
                            sessionKey == "gnome"
                        ) {
                    path += "gnome_badge.png";
                    iconFound = true;
                } else if (sessionKey == "plasma") {
                    path += "kde_badge.png";
                    iconFound = true;
                } else if (sessionKey == "xterm") {
                    path += "recovery_console_badge.png";
                    iconFound = true;
                } else if (sessionKey == "remote-login") {
                    path += "remote_login_help.png";
                    iconFound = true;
                }

                if (QFile(path).exists() && iconFound) {
                    qCWarning(SessionsModelLogger) << "Using session badge icon: " << path << " for session type: " << sessionKey;
                    return path;
                }
            }
        }
    }

    // FIXME make this smarter
    qCWarning(SessionsModelLogger) << "No suitable icon found! Falling back to unknown_badge.png icon.";
    return QUrl("./graphics/session_icons/unknown_badge.png");
}

QVariant SessionsModel::data(const QModelIndex& index, int role) const
{
    switch (role) {
        case SessionsModel::IconRole:
            return iconUrl(m_model->data(index, QLightDM::SessionsModel::KeyRole).toString());
        default:
            return m_model->data(index, role);
    }
}

SessionsModel::SessionsModel(QObject* parent)
  : LomiriSortFilterProxyModelQML(parent)
{
    // Add a custom IconRole that isn't in either of the lightdm implementations
    m_model = new QLightDM::SessionsModel(this);
    m_roleNames = m_model->roleNames();
    m_roleNames[IconRole] = "icon_url";

    // Update search locations to use $SNAP prefix if specified
    auto snapRoot = QFile::decodeName(qgetenv("SNAP"));
    if (!snapRoot.isEmpty()) {
        for (int i = 0; i < m_iconSearchDirectories.size(); i++) {
            m_iconSearchDirectories[i] = snapRoot + m_iconSearchDirectories[i].path();
        }
    }

    setModel(m_model);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortLocaleAware(true);
    setSortRole(Qt::DisplayRole);
    sort(0);
}
