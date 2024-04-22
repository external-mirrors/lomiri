/*
 * Copyright (C) 2023 UBports Foundation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Muhammad
 */

#include <QtQml>
#include <QtQml/QQmlContext>

#include "plugin.h"
#include "BatteryMonitor.h"

void BatteryMonitorPlugin::registerTypes(const char *uri) {
  qmlRegisterSingletonType<BatteryMonitor>(uri, 1, 0, "BatteryMonitor", [](QQmlEngine*, QJSEngine*) -> QObject* { return new BatteryMonitor; });
}
