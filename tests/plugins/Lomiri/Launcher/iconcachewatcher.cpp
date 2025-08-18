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

IconCacheWatcher* IconCacheWatcher::s_instance = nullptr;

IconCacheWatcher::IconCacheWatcher(QObject* parent)
    : QObject(parent)
{
    s_instance = this;
}

IconCacheWatcher* IconCacheWatcher::instance()
{
    return s_instance;
}

void IconCacheWatcher::triggerMockIconCacheChanged()
{
    Q_EMIT iconCacheChanged();
}