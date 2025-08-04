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

#ifndef DISPLAYS_H
#define DISPLAYS_H

#include <QObject>
#include <QtDBus>
#include <org_aethercast.h>
#include <freedesktop_properties.h>

class Displays : public QObject
{
    Q_OBJECT

    Q_PROPERTY (bool scanning
                READ scanning
                NOTIFY scanningChanged)

    Q_PROPERTY (bool enabled
                READ enabled
                WRITE setEnabled
                NOTIFY enabledChanged)

    Q_PROPERTY (QString state
                READ state
                NOTIFY stateChanged)

public:
    enum State { Idle=1, Disconnected=2, Association=4, Configuration=8, Connected=16, Failure=32 };
    Q_ENUMS(State)
    Q_DECLARE_FLAGS(States, State)

    explicit Displays(QObject *parent = nullptr);
    explicit Displays(const QDBusConnection &dbus, QObject *parent = nullptr);
    ~Displays() {}

    enum Error {
        None,
        Failed,
        Already,
        ParamInvalid,
        InvalidState,
        NotConnected,
        NotReady,
        Unknown
    };
    Q_ENUMS(Error)

    void setProperties(const QMap<QString,QVariant> &properties);
    bool scanning() const { return m_manager->scanning(); }
    bool enabled() const { return m_manager->enabled(); }
    void setEnabled(bool);
    QString state() const { return m_manager->state(); }

Q_SIGNALS:
    void scanningChanged(bool isActive);
    void enabledChanged(bool enabled);
    void stateChanged();
    void connectedDevicesChanged();
    void disconnectedDevicesChanged();
    void connectError(int error);

private Q_SLOTS:
    void slotPropertiesChanged(const QString &interface, const QVariantMap &changedProperties,
                               const QStringList &invalidatedProperties);
    void callFinishedSlot(QDBusPendingCallWatcher *call);

private:
    void getAll();

    QDBusConnection m_dbus;
    OrgAethercastManagerInterface* m_manager;
    QScopedPointer<OrgFreedesktopDBusPropertiesInterface> m_aethercastProperties;
    void updateProperties(QSharedPointer<QDBusInterface>);
    void updateProperty(const QString &key, const QVariant &value);
    void handleConnectError(QDBusError error);
};

#endif // DISPLAYS_H
