/*
 * Copyright 2026 Volla Systeme GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.12
import Lomiri.Components 1.3
import Biometryd 0.0
import Utils 0.1
import Powerd 0.1


Item {
    id: udfpsensor
    DeviceConfig {
        id: deviceConfig
    }

    // TODO: read USFPDS position from biometryd
    x: deviceConfig.sensorLocationX - deviceConfig.sensorRadius
    y: deviceConfig.sensorLocationY - deviceConfig.sensorRadius
    z: 99

    width: deviceConfig.sensorRadius * 2
    height: width

    Image {
        id: fpimage
        source: "graphics/fingerprint.svg"
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit

        ColorOverlay {
            anchors.fill: fpimage
            source: fpimage
            color: "white"
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                if (!udfpsensor.visible) {
                    return;
                }

                var absoluteX = mouseX + udfpsensor.x;
                var absoluteY = mouseY + udfpsensor.y;
                var minor = udfpsensor.width / 2;
                var major = minor;

                if (Biometryd.available && Biometryd.defaultDevice) {
                    try {
                        Powerd.setHighBrightnessMode(true)
                        Biometryd.defaultDevice.sendFingerDown(absoluteX, absoluteY, minor, major);
                        biometryd.startOperation()
                    } catch (e) {
                        console.warn("Failed to call Biometryd.sendFingerDown:", e);
                    }
                }
            }
            onReleased: {
                if (!udfpsensor.visible) {
                    return;
                }

                if (Biometryd.available && Biometryd.defaultDevice) {
                    try {
                        Powerd.setHighBrightnessMode(false)
                        Biometryd.defaultDevice.sendFingerUp();
                        biometryd.cancelOperation()
                    } catch (e) {
                        console.warn("Failed to call Biometryd.sendFingerUp:", e);
                    }
                }
            }
        }
    }
}
