#include <QtQml>
#include <QtQml/QQmlContext>

#include "plugin.h"
#include "BatteryMonitor.h"

void BatteryMonitorPlugin::registerTypes(const char *uri) {
  qmlRegisterSingletonType<BatteryMonitor>(uri, 1, 0, "BatteryMonitor", [](QQmlEngine*, QJSEngine*) -> QObject* { return new BatteryMonitor; });
}
