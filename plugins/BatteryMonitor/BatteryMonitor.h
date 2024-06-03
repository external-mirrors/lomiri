/*
 * Copyright (C) 2023 Muhammad <muhammad23012009@hotmail.com>
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
 */

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
  Q_PROPERTY(bool fullyCharged READ isFullyCharged NOTIFY fullyChargedChanged)

public:
  BatteryMonitor();

  bool hasBattery();
  bool charging();
  bool isFullyCharged();
  qint64 timeToFull();

  Q_INVOKABLE uint state();

  enum Error {
      NO_BATTERY = -1,
      NO_TIMETOFULL = -2
  };
  Q_ENUM(Error)

public Q_SLOTS:
  void propertiesChanged(QString string, QVariantMap map, QStringList list);

Q_SIGNALS:
  void chargingChanged();
  void timeToFullChanged();
  void fullyChargedChanged();

private:
  QDBusInterface *m_iface;
  QDBusObjectPath m_displayPath;
};

#endif
