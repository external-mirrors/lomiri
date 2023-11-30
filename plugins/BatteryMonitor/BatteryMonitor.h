#ifndef BATTERYMONITOR_H
#define BATTERYMONITOR_H

#include <QObject>
#include <QDebug>
#include <QtDBus/QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusObjectPath>

#define GET "Get"
#define UPOWER_PROPERTIES "org.freedesktop.UPower.Device"

enum {
    /* Status */
    UNKNOWN = 0,
    CHARGING,
    DISCHARGING,
    EMPTY,
    FULLY_CHARGED = 4,

    /* Type */
    ON_LINEPOWER = 1,
    ON_BATTERY = 2
};

class BatteryMonitor: public QObject {
  Q_OBJECT

public:
  BatteryMonitor();

  bool hasBattery();
  Q_INVOKABLE bool charging();
  Q_INVOKABLE QString getTimeToFull();

private:
  QDBusInterface *m_iface;
  QDBusObjectPath m_displayPath;
};

#endif
