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
  Q_PROPERTY(qint64 timeToFull READ timeToFull NOTIFY timeToFullChanged)
  Q_PROPERTY(bool charging READ charging NOTIFY chargingChanged)

public:
  BatteryMonitor();

  bool hasBattery();
  bool charging();
  qint64 timeToFull();

  Q_INVOKABLE uint state();

public Q_SLOTS:
  void propertiesChanged(QString string, QVariantMap map, QStringList list);

Q_SIGNALS:
  void chargingChanged();
  void timeToFullChanged();

private:
  QDBusInterface *m_iface;
  QDBusObjectPath m_displayPath;
};

#endif
