#ifndef BATTERYMONTIOR_PLUGIN_H
#define BATTERYMONITOR_PLUGIN_H

#include <QQmlExtensionPlugin>

class BatteryMonitorPlugin : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
  void registerTypes(const char *uri);
};

#endif
