/*
 * Copyright (C) 2016 Canonical Ltd.
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
 * Authors:
 * Ken VanDine <ken.vandine@canonical.com>
 *
 */

#include "displays.h"
#include <org_aethercast.h>
#include "dbus-shared.h"

#include <QQmlEngine>

Displays::Displays(QObject *parent):
    Displays(QDBusConnection::systemBus(), parent)
{
}

Displays::Displays(const QDBusConnection &dbus, QObject *parent):
    QObject(parent),
    m_dbus(dbus)
{
    m_manager = new OrgAethercastManagerInterface(AETHERCAST_SERVICE, AETHERCAST_PATH, m_dbus);

    m_aethercastProperties.reset(new OrgFreedesktopDBusPropertiesInterface(AETHERCAST_SERVICE, AETHERCAST_PATH, m_dbus));

    QObject::connect(m_aethercastProperties.data(), SIGNAL(PropertiesChanged(const QString&, const QVariantMap&, const QStringList&)),
                     this, SLOT(slotPropertiesChanged(const QString&, const QVariantMap&, const QStringList&)));

    getAll();
    connect(m_dbus.interface(), &QDBusConnectionInterface::serviceRegistered, this, [=](QString service) {
        if (service != AETHERCAST_SERVICE)
            return;

        getAll();
    });
}

void Displays::getAll()
{
    watchCall(m_aethercastProperties->GetAll(AETHERCAST_MANAGER_IFACE), [=](QDBusPendingCallWatcher *watcher) {
            QDBusPendingReply<QVariantMap> reply = *watcher;

        if (reply.isError()) {
            qWarning() << "Failed to retrieve properties for manager";
            watcher->deleteLater();
            return;
        }

        auto properties = reply.argumentAt<0>();
        setProperties(properties);
        watcher->deleteLater();
    });
}

void Displays::slotPropertiesChanged(const QString &interface, const QVariantMap &changedProperties,
                                           const QStringList &invalidatedProperties)
{
    Q_UNUSED(invalidatedProperties);

    if (interface != AETHERCAST_MANAGER_IFACE)
        return;

    setProperties(changedProperties);
}

void Displays::setProperties(const QMap<QString,QVariant> &properties)
{
    QMapIterator<QString,QVariant> it(properties);
    while (it.hasNext()) {
        it.next();
        updateProperty(it.key(), it.value());
    }
}

void Displays::setEnabled(bool enabled)
{
    if (!m_manager)
        return;

    m_manager->setEnabled(enabled);
    Q_EMIT enabledChanged(enabled);
}

void Displays::handleConnectError(QDBusError error)
{
    if (error.name() == "org.aethercast.Error.None")
        Q_EMIT(connectError(Error::None));
    else if (error.name() == "org.aethercast.Error.Failed")
        Q_EMIT(connectError(Error::Failed));
    else if (error.name() == "org.aethercast.Error.Already")
        Q_EMIT(connectError(Error::Already));
    else if (error.name() == "org.aethercast.Error.ParamInvalid")
        Q_EMIT(connectError(Error::ParamInvalid));
    else if (error.name() == "org.aethercast.Error.InvalidState")
        Q_EMIT(connectError(Error::InvalidState));
    else if (error.name() == "org.aethercast.Error.NotConnected")
        Q_EMIT(connectError(Error::NotConnected));
    else if (error.name() == "org.aethercast.Error.NotReady")
        Q_EMIT(connectError(Error::NotReady));
    else
        Q_EMIT(connectError(Error::Unknown));
}

void Displays::callFinishedSlot(QDBusPendingCallWatcher *call)
{
    QDBusPendingReply<void> reply = *call;
    if (reply.isFinished() && reply.isError())
        handleConnectError(reply.error());
    call->deleteLater();
}

void Displays::updateProperty(const QString &key, const QVariant &value)
{
    if (key == "Scanning")
        Q_EMIT(scanningChanged(value.toBool()));
    if (key == "State")
        Q_EMIT(stateChanged());
    if (key == "Enabled")
        Q_EMIT(enabledChanged(value.toBool()));
}
