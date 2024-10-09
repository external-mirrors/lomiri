/*
 * Copyright (C) 2016 Canonical Ltd.
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
import QtGraphicalEffects 1.12
import Lomiri.Components 1.3

LomiriShape {
    id: root

    // This property holds the delay (milliseconds) after which the tool tip is shown.
    // A tooltip with a negative delay is shown immediately. The default value is 500 ms.
    property int delay:  500

    // This property holds the text shown on the tool tip.
    property alias text: label.text

    readonly property bool lightMode: true

    aspect: LomiriShape.Flat
    color: theme.palette.normal.background
    width: label.implicitWidth + units.gu(4)
    height: label.implicitHeight + units.gu(2)
    opacity: 0

    Image {
        id: arrow
        anchors {
            right: parent.left
            rightMargin: -units.dp(4)
            verticalCenter: parent.verticalCenter
        }
        source: "graphics/quicklist_tooltip.png"
        rotation: 90
        visible: !root.lightMode
    }

    ColorOverlay {
        anchors.fill: arrow
        source: arrow
        color: root.color
        rotation: arrow.rotation
        visible: root.lightMode
    }

    Label {
        id: label
        anchors.centerIn: parent
        color: theme.palette.normal.backgroundText
    }

    states: [
        State {
            name: "visible"
            when: root.visible
            PropertyChanges {
                target: root
                opacity: 0.95
            }
        }
    ]

    transitions: [
        Transition {
            from: ""; to: "visible"
            SequentialAnimation {
                PauseAnimation { duration: root.delay }
                LomiriNumberAnimation { target: root; property: "opacity"; duration: LomiriAnimation.BriskDuration }
            }
        }
    ]
}
