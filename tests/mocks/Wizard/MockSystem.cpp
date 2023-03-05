/*
 * Copyright (C) 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QSettings>

#include "MockSystem.h"

MockSystem::MockSystem()
    : QObject(),
      m_wizardEnabled(false),
      m_version("Lomiri 17.04.12")
{
}

bool MockSystem::wizardEnabled() const
{
    return m_wizardEnabled;
}

void MockSystem::setWizardEnabled(bool enabled)
{
    m_wizardEnabled = enabled;
    Q_EMIT wizardEnabledChanged();
}

bool MockSystem::isUpdate() const
{
    return m_isUpdate;
}

void MockSystem::setIsUpdate(bool update)
{
    m_isUpdate = update;
    Q_EMIT isUpdateChanged();
}

QString MockSystem::version() const
{
    return m_version;
}

void MockSystem::updateSessionLocale(const QString &locale)
{
    Q_EMIT updateSessionLocaleCalled(locale);
}

void MockSystem::skipUntilFinishedPage()
{
    Q_EMIT wouldHaveSetSkipUntilFinish();
}

QString MockSystem::distroName() const
{
    return QStringLiteral("Lomiri");
}
