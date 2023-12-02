#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor()
{
    QDBusInterface temp_iface("org.freedesktop.UPower", "/org/freedesktop/UPower", "org.freedesktop.UPower", QDBusConnection::systemBus());
    QDBusReply<QDBusObjectPath> path = temp_iface.call("GetDisplayDevice");

    m_displayPath = path.value();
    m_iface = new QDBusInterface("org.freedesktop.UPower", m_displayPath.path(), "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
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

QString BatteryMonitor::getTimeToFull()
{
    if (!hasBattery())
        return QString();

    QDBusReply<QDBusVariant> reply = m_iface->call(GET, UPOWER_PROPERTIES, "TimeToFull");
    if (reply.isValid() && charging()) {
        uint value = reply.value().variant().toUInt();

        if (value == 0) {
            // This is a bit complex. Either UPower will be trying to calculate time to full, or we're actually full.
            QDBusReply<QDBusVariant> percentage = m_iface->call(GET, UPOWER_PROPERTIES, "Percentage");
            if (percentage.value().variant().toFloat() == 100.0)
                return QString("Fully charged");
            else
                return QString();
        }

        uint hours = value / 60 / 60;
        uint minutes = value / 60 % 60;

        if (hours == 0)
            return QString("%1 minutes until full").arg(QString::number(minutes));
        else if (minutes == 0)
            return QString("%1 hours until full").arg(QString::number(hours));
        else
            return QString("%1 hours and %2 minutes until full").arg(QString::number(hours)).arg(QString::number(minutes));

    } else if (reply.isValid() && state() == FULLY_CHARGED) {
        return QString("Fully charged");

    } else {
        return QString();
    }
}
