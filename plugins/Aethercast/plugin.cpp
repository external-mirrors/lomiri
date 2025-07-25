/*
 * Copyright (C) 2025 UBports Foundation
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plugin.h"
#include "aethercast_helper.h"
#include "displays.h"
#include "device.h"

#include <QtQml/qqml.h>


void AethercastPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Aethercast"));

    // Register additional QtDBus types we need
    qDBusRegisterMetaType<InterfaceList>();
    qDBusRegisterMetaType<ManagedObjectList>();

    qmlRegisterType<Device>(uri, 1, 0, "AethercastDevice");
    qmlRegisterType<Displays>(uri, 1, 0, "AethercastDisplays");
}
