/*
 * Copyright (C) 2015 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtTest 1.0
import Lomiri.SelfTest 0.1
import Lomiri.Components 1.3
import Lomiri.Components.ListItems 1.3
import "../../qml"

Item {
    id: root
    width: units.gu(80)
    height: units.gu(70)

    DisabledScreenNotice {
        id: touchScreenPad
        anchors.fill: parent
        anchors.rightMargin: units.gu(40)

        // Mock some things here
        property int internalGu: units.gu(1)

        screen: QtObject {
            property int orientation: {
                switch (orientationSelector.selectedIndex) {
                case 0:
                    return Qt.PortraitOrientation;
                case 1:
                    return Qt.LandscapeOrientation;
                case 2:
                    return Qt.InvertedPortraitOrientation;
                case 3:
                    return Qt.InvertedLandscapeOrientation;
                }
            }
            property int primaryOrientation: {
                switch (primaryOrientationSelector.selectedIndex) {
                case 0:
                    return Qt.PortraitOrientation;
                case 1:
                    return Qt.LandscapeOrientation;
                case 2:
                    return Qt.InvertedPortraitOrientation;
                case 3:
                    return Qt.InvertedLandscapeOrientation;
                }
            }
        }

        Component.onCompleted: {
            var container = testCase.findChild(touchScreenPad, "contentContainer")
            container.angleFromPrimary = Qt.binding( function() { return Screen.angleBetween(screen.primaryOrientation, screen.orientation) })
        }
    }

    Column {
        anchors { top: parent.top; right: parent.right; bottom: parent.bottom }
        width: units.gu(40)
        spacing: units.gu(1)

        ItemSelector {
            id: primaryOrientationSelector
            text: "Primary Orientation"
            model: ["Portrait", "Landscape", "InvertedPortrait", "InvertedLandscape"]
            selectedIndex: 0
        }
        ItemSelector {
            id: orientationSelector
            text: "Physical orientation"
            model: ["Portrait", "Landscape", "InvertedPortrait", "InvertedLandscape"]
            selectedIndex: 0
        }

        Button {
            text: "Reset first run settings"
            onClicked: {
                var settings = testCase.findInvisibleChild(touchScreenPad, "virtualTouchPadSettings");
                settings.touchpadTutorialHasRun = false;
            }
        }
        Button {
            text: "Run tutorial now"
            onClicked: {
                var touchPad = testCase.findChild(touchScreenPad, "virtualTouchPad")
                touchPad.runTutorial();
            }
        }
    }

    LomiriTestCase {
        id: testCase
        name: "DisabledScreenNotice"
        when: windowShown

        function test_rotation_button_visibility_data() {
            return [
                {tag: "portrait-portrait", primaryOrientation: 0, selectedOrientation: 0, expectedVisible: false},
                {tag: "portrait-landscape", primaryOrientation: 0, selectedOrientation: 1, expectedVisible: true},
                {tag: "portrait-invertedportrait", primaryOrientation: 0, selectedOrientation: 2, expectedVisible: true},
                {tag: "portrait-invertetlandscape", primaryOrientation: 0, selectedOrientation: 3, expectedVisible: true},
                {tag: "landscape-portrait", primaryOrientation: 1, selectedOrientation: 0, expectedVisible: true},
                {tag: "landscape-landscape", primaryOrientation: 1, selectedOrientation: 1, expectedVisible: false},
                {tag: "landscape-invertedportrait", primaryOrientation: 1, selectedOrientation: 2, expectedVisible: true},
                {tag: "landscape-invertetlandscape", primaryOrientation: 1, selectedOrientation: 3, expectedVisible: true},
                {tag: "invertedportrait-portrait", primaryOrientation: 2, selectedOrientation: 0, expectedVisible: true},
                {tag: "invertedportrait-landscape", primaryOrientation: 2, selectedOrientation: 1, expectedVisible: true},
                {tag: "invertedportrait-invertedportrait", primaryOrientation: 2, selectedOrientation: 2, expectedVisible: false},
                {tag: "invertedportrait-invertetlandscape", primaryOrientation: 2, selectedOrientation: 3, expectedVisible: true},
                {tag: "invertetlandscape-portrait", primaryOrientation: 3, selectedOrientation: 0, expectedVisible: true},
                {tag: "invertetlandscape-landscape", primaryOrientation: 3, selectedOrientation: 1, expectedVisible: true},
                {tag: "invertetlandscape-invertedportrait", primaryOrientation: 3, selectedOrientation: 2, expectedVisible: true},
                {tag: "invertetlandscape-invertetlandscape", primaryOrientation: 3, selectedOrientation: 3, expectedVisible: false}
            ]
        }

        function test_rotation_button_visibility(data) {
            // simulate the primary orientation
            primaryOrientationSelector.selectedIndex = data.primaryOrientation;

            // simulate the physical orientation
            orientationSelector.selectedIndex = data.selectedOrientation;

            // test visibility of the rotate button
            // rotation angle is always 0 in this test
            var rotateButton = testCase.findChild(touchScreenPad, "rotateButton")
            compare(rotateButton.visible, data.expectedVisible, "Rotate button should be hidden if the current rotation and physical orientation matches and shown if not")
        }

        function test_rotation_data() {
            return [
                {tag: "portrait-portrait", primaryOrientation: 0, selectedOrientation: 0, expectedAngle: 0},
                {tag: "portrait-landscape", primaryOrientation: 0, selectedOrientation: 1, expectedAngle: 270},
                {tag: "portrait-invertedportrait", primaryOrientation: 0, selectedOrientation: 2, expectedAngle: 180},
                {tag: "portrait-invertetlandscape", primaryOrientation: 0, selectedOrientation: 3, expectedAngle: 90},
                {tag: "reset-portrait-portrait", primaryOrientation: 0, selectedOrientation: 0, expectedAngle: 0},
                {tag: "landscape-portrait", primaryOrientation: 1, selectedOrientation: 0, expectedAngle: 90},
                {tag: "landscape-landscape", primaryOrientation: 1, selectedOrientation: 1, expectedAngle: 0},
                {tag: "landscape-invertedportrait", primaryOrientation: 1, selectedOrientation: 2, expectedAngle: 270},
                {tag: "landscape-invertetlandscape", primaryOrientation: 1, selectedOrientation: 3, expectedAngle: 180},
                {tag: "reset-landscape-landscape", primaryOrientation: 1, selectedOrientation: 1, expectedAngle: 0},
                {tag: "invertedportrait-portrait", primaryOrientation: 2, selectedOrientation: 0, expectedAngle: 180},
                {tag: "invertedportrait-landscape", primaryOrientation: 2, selectedOrientation: 1, expectedAngle: 90},
                {tag: "invertedportrait-invertedportrait", primaryOrientation: 2, selectedOrientation: 2, expectedAngle: 0},
                {tag: "invertedportrait-invertetlandscape", primaryOrientation: 2, selectedOrientation: 3, expectedAngle: 270},
                {tag: "reset-invertedportrait-invertedportrait", primaryOrientation: 2, selectedOrientation: 2, expectedAngle: 0},
                {tag: "invertetlandscape-portrait", primaryOrientation: 3, selectedOrientation: 0, expectedAngle: 270},
                {tag: "invertetlandscape-landscape", primaryOrientation: 3, selectedOrientation: 1, expectedAngle: 180},
                {tag: "invertetlandscape-invertedportrait", primaryOrientation: 3, selectedOrientation: 2, expectedAngle: 90},
                {tag: "invertetlandscape-invertetlandscape", primaryOrientation: 3, selectedOrientation: 3, expectedAngle: 0}
            ];
        }

        function test_rotation(data) {
            var content = findChild(touchScreenPad, "contentContainer");

            // simulate the primary orientation
            primaryOrientationSelector.selectedIndex = data.primaryOrientation;

            // simulate the physical orientation
            orientationSelector.selectedIndex = data.selectedOrientation;

            // click on the rotate button if visible
            var rotateButton = testCase.findChild(touchScreenPad, "rotateButton")
            if (rotateButton.visible) {
                rotateButton.clicked();
            }

            // And make sure it catches up to the expected angle
            tryCompare(content, "rotation", data.expectedAngle);
        }
    }
}
