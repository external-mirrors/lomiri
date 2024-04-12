/*
 * Copyright (C) 2013-2016 Canonical Ltd.
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
 * Author: Michael Terry <michael.terry@canonical.com>
 */


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * CHANGES MADE HERE MUST BE REFLECTED ON THE MOCK LIB
 * COUNTERPART IN tests/mocks/Lightdm/liblightdm
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

// LightDM currently is Qt4 compatible, and so doesn't define setRoleNames.
// To use the same method of setting role name that it does, we
// set our compatibility to Qt4 here too.
#define QT_DISABLE_DEPRECATED_BEFORE QT_VERSION_CHECK(4, 0, 0)

#include "UsersModel.h"
#include "UsersModelPrivate.h"
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtGui/QIcon>

namespace QLightDM
{

UsersModel::UsersModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new UsersModelPrivate(this))
{
    Q_D(UsersModel);

    // Extend roleNames (we want to keep the "display" role)
    d->m_roles = QAbstractListModel::roleNames();
    d->m_roles[NameRole] = "name";
    d->m_roles[RealNameRole] = "realName";
    d->m_roles[LoggedInRole] = "loggedIn";
    d->m_roles[BackgroundRole] = "background";
    d->m_roles[BackgroundPathRole] = "backgroundPath";
    d->m_roles[SessionRole] = "session";
    d->m_roles[HasMessagesRole] = "hasMessages";
    d->m_roles[ImagePathRole] = "imagePath";
    d->m_roles[UidRole] = "uid";

    connect(d_ptr, &UsersModelPrivate::dataChanged, this, [this](int i) {
        QModelIndex index = createIndex(i, 0);
        Q_EMIT dataChanged(index, index);
    });
}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    Q_D(const UsersModel);

    return d->m_roles;
}

int UsersModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const UsersModel);

    if (parent.isValid()) {
        return 0;
    } else { // parent is root
        return d->entries.size();
    }
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    Q_D(const UsersModel);

    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    switch (role) {
    case Qt::DisplayRole:
        return d->entries[row].real_name;
    case Qt::DecorationRole:
        return QIcon();
    case UsersModel::NameRole:
        return d->entries[row].username;
    case UsersModel::RealNameRole:
        return d->entries[row].real_name;
    case UsersModel::SessionRole:
        return d->entries[row].session;
    case UsersModel::LoggedInRole:
        return d->entries[row].is_active;
    case UsersModel::BackgroundRole:
        return QPixmap(d->entries[row].background);
    case UsersModel::BackgroundPathRole:
        return d->entries[row].background;
    case UsersModel::HasMessagesRole:
        return d->entries[row].has_messages;
    case UsersModel::ImagePathRole:
        return "";
    case UsersModel::UidRole:
        return d->entries[row].uid;
    default:
        return QVariant();
    }
}

}
