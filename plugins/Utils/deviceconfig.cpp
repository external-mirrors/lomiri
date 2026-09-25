/*
 * Copyright 2016 Canonical Ltd.
 * Copyright 2019-2022 UBports Foundation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "deviceconfig.h"

#include <deviceinfo.h>
#include <QDebug>
#include <QRegularExpression>

DeviceConfig::DeviceConfig(QObject *parent):
    QObject(parent),
    m_info(std::make_unique<DeviceInfo>())
{
}

DeviceConfig::~DeviceConfig() = default;

QString DeviceConfig::name() const
{
    return QString::fromStdString(m_info->name());
}

Qt::ScreenOrientation DeviceConfig::primaryOrientation() const
{
    return stringToOrientation(m_info->primaryOrientation(), Qt::PrimaryOrientation);
}

Qt::ScreenOrientations DeviceConfig::supportedOrientations() const
{
    auto values = m_info->supportedOrientations();
    if (values.empty()) {
        return Qt::PortraitOrientation
                | Qt::InvertedPortraitOrientation
                | Qt::LandscapeOrientation
                | Qt::InvertedLandscapeOrientation;
    }

    Qt::ScreenOrientations ret = Qt::PrimaryOrientation;
    for (auto orientationString : values) {
        ret |= stringToOrientation(orientationString, Qt::PrimaryOrientation);
    }
    return ret;
}

Qt::ScreenOrientation DeviceConfig::landscapeOrientation() const
{
    return stringToOrientation(m_info->landscapeOrientation(), Qt::LandscapeOrientation);
}

Qt::ScreenOrientation DeviceConfig::invertedLandscapeOrientation() const
{
    return stringToOrientation(m_info->invertedLandscapeOrientation(), Qt::InvertedLandscapeOrientation);
}

Qt::ScreenOrientation DeviceConfig::portraitOrientation() const
{
    return stringToOrientation(m_info->portraitOrientation(), Qt::PortraitOrientation);
}

Qt::ScreenOrientation DeviceConfig::invertedPortraitOrientation() const
{
    return stringToOrientation(m_info->invertedPortraitOrientation(), Qt::InvertedPortraitOrientation);
}

QString DeviceConfig::category() const
{
    QStringList supportedValues = {"phone", "tablet", "desktop"};
    QString value = QString::fromStdString(DeviceInfo::deviceTypeToString(m_info->deviceType()));
    if (!supportedValues.contains(value)) {
        qWarning().nospace().noquote() << "Unknown option \"" << value
                    << ". Supported options are: " << supportedValues.join(", ") << ".";
        return "phone";
    }
    return value;
}

Qt::ScreenOrientation DeviceConfig::stringToOrientation(const std::string &orientationString, Qt::ScreenOrientation defaultValue) const
{
    if (orientationString == "Landscape") {
        return Qt::LandscapeOrientation;
    }
    if (orientationString == "InvertedLandscape") {
        return Qt::InvertedLandscapeOrientation;
    }
    if (orientationString == "Portrait") {
        return Qt::PortraitOrientation;
    }
    if (orientationString == "InvertedPortrait") {
        return Qt::InvertedPortraitOrientation;
    }
    if (!orientationString.empty()) {
        // Some option we don't know. Give some hint on what went wrong.
        qWarning().nospace().noquote() << "Unknown option \"" << QString::fromStdString(orientationString)
                    << ". Supported options are: Landscape, InvertedLandscape, Portrait and InvertedPortrait.\"";
    }
    return defaultValue;
}

bool DeviceConfig::supportsMultiColorLed() const
{
    return m_info->contains("supportsMultiColorLed");
}

quint16 DeviceConfig::sensorLocationX() const
{
    return QString::fromStdString(m_info->get("udfpLocationX", "0")).toUInt();
}

quint16 DeviceConfig::sensorLocationY() const
{
    return QString::fromStdString(m_info->get("udfpLocationY", "0")).toUInt();
}

quint16 DeviceConfig::sensorRadius() const
{
    return QString::fromStdString(m_info->get("udfpSensorRadius", "0")).toUInt();
}

bool DeviceConfig::sensorLocalHBM() const
{
    // Such panels light the sensor area themselves.
    return QString::fromStdString(m_info->get("udfpLocalHBM", "false")).toLower() == "true";
}

qreal DeviceConfig::sensorDimOpacity(int brightness) const
{
    // How much dimming cancels high brightness mode depends on the brightness
    // setting, and the relation is a property of the panel: pairs of
    // "<brightness>,<alpha out of 255>", interpolated in between.
    const QString table = QString::fromStdString(
        m_info->get("udfpDimmingBrightnessAlphaArray", ""));

    qreal previousBrightness = 0;
    qreal previousAlpha = -1;

    const auto entries = table.split(QRegularExpression(QStringLiteral("\\s+")),
                                     Qt::SkipEmptyParts);
    for (const QString &entry : entries) {
        const auto pair = entry.split(QLatin1Char(','));
        if (pair.size() != 2) {
            qWarning().nospace().noquote()
                << "Ignoring malformed udfpDimmingBrightnessAlphaArray entry \""
                << entry << "\". Expected <brightness>,<alpha>.";
            continue;
        }

        const qreal entryBrightness = pair[0].toDouble();
        const qreal entryAlpha = pair[1].toDouble();

        if (entryBrightness >= brightness) {
            if (previousAlpha < 0 || entryBrightness <= previousBrightness)
                return entryAlpha / 255;

            const qreal position = (brightness - previousBrightness)
                                 / (entryBrightness - previousBrightness);
            return (previousAlpha + position * (entryAlpha - previousAlpha)) / 255;
        }

        previousBrightness = entryBrightness;
        previousAlpha = entryAlpha;
    }

    // Brighter than the table goes, or no table at all.
    return previousAlpha < 0 ? 0.9 : previousAlpha / 255;
}

quint16 DeviceConfig::collapsedPanelHeight() const
{
    return QString::fromStdString(m_info->get("CollapsedPanelHeight", "0")).toUInt();
}

void DeviceConfig::reload()
{
    m_info = std::make_unique<DeviceInfo>();
    Q_EMIT changed();
}

bool DeviceConfig::supportsRebootToRecovery() const
{
    return m_info->get("supportsRebootToRecovery", "false") == "true";
}
