/*
 * Copyright 2025 UBports Foundation
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

/**
 * @brief The FileIo class
 *
 * This singleton class exposes file helpers to Qml
 *
 */

class FileIo: public QObject
{
    Q_OBJECT

public:
    FileIo(QObject *parent = 0);

public Q_SLOTS:
    bool remove(const QString path);
};
