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

    // Shell and Greeter ids are out of scope in this file, so both are passed in.
    property Item shellRoot
    property QtObject biometryd

    DeviceConfig {
        id: deviceConfig
    }

    property bool fingerDown: false
    readonly property bool sensorConfigured: deviceConfig.sensorRadius > 0

    /* Greeter is destroyed as soon as the fingerprint is accepted, so the
       release may never arrive. */
    function fingerUp() {
        if (!fingerDown) {
            return;
        }
        fingerDown = false;

        shellRoot.enableUDFPSDimmer(false);
        if (Biometryd.available && Biometryd.defaultDevice) {
            try {
                Biometryd.defaultDevice.sendFingerUp();
            } catch (e) {
                console.warn("Failed to call Biometryd.sendFingerUp:", e);
            }
        }
    }

    onVisibleChanged: if (!visible) fingerUp()
    Component.onDestruction: fingerUp()

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
                if (!udfpsensor.visible || !udfpsensor.shellRoot || !udfpsensor.biometryd) {
                    return;
                }

                var absoluteX = mouseX + udfpsensor.x;
                var absoluteY = mouseY + udfpsensor.y;
                var minor = udfpsensor.width / 2;
                var major = minor;

                if (Biometryd.available && Biometryd.defaultDevice) {
                    try {
                        udfpsensor.fingerDown = true;
                        udfpsensor.shellRoot.enableUDFPSDimmer(true);
                        Biometryd.defaultDevice.sendFingerDown(absoluteX, absoluteY, minor, major);
                        udfpsensor.biometryd.startOperation();
                    } catch (e) {
                        console.warn("Failed to call Biometryd.sendFingerDown:", e);
                    }
                }
            }
            onReleased: {
                udfpsensor.fingerUp();

                if (udfpsensor.visible && udfpsensor.biometryd) {
                    udfpsensor.biometryd.cancelOperation();
                }
            }
            onCanceled: udfpsensor.fingerUp()
        }
    }
}
