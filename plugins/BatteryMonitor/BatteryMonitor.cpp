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
    return state() == CHARGING ? true : false;
}

bool BatteryMonitor::isFullyCharged()
{
    if (state() == FULLY_CHARGED)
        return true;

    QDBusReply<QDBusVariant> reply = m_iface->call(GET, UPOWER_PROPERTIES, "Percentage");
    float percentage = reply.value().variant().toFloat();

    if (percentage == 100.0 && charging())
        return true;
    else
        return false;
}

qint64 BatteryMonitor::timeToFull()
{
    if (!hasBattery())
        return NO_BATTERY;

    QDBusReply<QDBusVariant> reply = m_iface->call(GET, UPOWER_PROPERTIES, "TimeToFull");
    if (reply.isValid() && charging()) {
        uint value = reply.value().variant().toUInt();
        if (value == 0)
            return NO_TIMETOFULL;

        return value;
    }

    return NO_TIMETOFULL;
}

void BatteryMonitor::propertiesChanged(QString string, QVariantMap map, QStringList list)
{
    Q_UNUSED(string)
    Q_UNUSED(list)

    if (map.contains("State"))
        Q_EMIT chargingChanged();

    else if (map.contains("TimeToFull") && map.contains("Percentage") && charging())
        Q_EMIT timeToFullChanged();

    else if (isFullyCharged())
        Q_EMIT fullyChargedChanged();
}
