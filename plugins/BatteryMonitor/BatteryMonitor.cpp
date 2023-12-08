#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor()
{
    QDBusConnection::systemBus().connect("org.freedesktop.UPower", "/org/freedesktop/UPower/devices/DisplayDevice", "org.freedesktop.DBus.Properties", "PropertiesChanged", this, SLOT(propertiesChanged(QString, QVariantMap, QStringList)));
    m_iface = new QDBusInterface("org.freedesktop.UPower", "/org/freedesktop/UPower/devices/DisplayDevice", "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
}

bool BatteryMonitor::hasBattery()
{
    QDBusReply<QDBusVariant> reply;
    uint state;

    reply = m_iface->call(GET, UPOWER_PROPERTIES, "Type");
    state = reply.value().variant().toUInt();

    if (state == ON_BATTERY) {
        reply = m_iface->call(GET, UPOWER_PROPERTIES, "PowerSupply");
        if (reply.value().variant().toBool())
            return true;
        else
            return false;
    } else
        return false;
}

uint BatteryMonitor::state()
{
    if (!hasBattery())
        return UNKNOWN;

    QDBusReply<QDBusVariant> reply = m_iface->call(GET, UPOWER_PROPERTIES, "State");
    return reply.value().variant().toUInt();
}

bool BatteryMonitor::charging()
{
    if (state() == CHARGING)
        return true;
    else
        return false;
}

qint64 BatteryMonitor::timeToFull()
{
    if (!hasBattery())
        return -1;

    QDBusReply<QDBusVariant> reply = m_iface->call(GET, UPOWER_PROPERTIES, "TimeToFull");
    if (reply.isValid() && charging()) {
        uint value = reply.value().variant().toUInt();
        if (value == 0)
            return -2;

        return value;
    }
}

void BatteryMonitor::propertiesChanged(QString string, QVariantMap map, QStringList list)
{
    if (map.contains("State"))
        Q_EMIT chargingChanged();
    else if (map.contains("TimeToFull") && map.contains("Percentage"))
        Q_EMIT timeToFullChanged();
}
