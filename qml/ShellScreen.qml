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

import QtQuick 2.12
import Lomiri.Components 1.3
import WindowManager 1.0
import Cursor 1.1
import "Components"

ScreenWindow {
    id: screenWindow

    color: "black"
    title: "Lomiri Shell"

    property int screenIndex: -1
    property bool primary: {
        if (loader.sourceComponent == disabledScreenComponent)
            return false;

        // If this is the only screen then it's the primary one
        if (Screens.count === 1)
            return true;

        const thisFormFactor = screenWindow.screen.formFactor;

        // Tablet & phone devices can only have 2 screens at max
        if (Screens.count === 2) {
            const internalFormFactor = Screens.get(0).formFactor;

            if (thisFormFactor === internalFormFactor === Screen.Tablet)
                return true;

            if (internalFormFactor === Screen.Phone && thisFormFactor !== Screen.Phone)
                return true;

            if (internalFormFactor === Screen.Phone && thisFormFactor === Screen.Phone)
                return false;
        }

        return (Screens.count >= 1 && screenIndex === 0);
    }

    Loader {
        id: loader
        width: screenWindow.width
        height: screenWindow.height

        sourceComponent: {
            if (Screens.count > 1 && screenWindow.screen.formFactor === Screen.Phone) {
                return disabledScreenComponent;
            }
            return shellComponent;
        }
    }

    Component {
        id: shellComponent
        OrientedShell {
            implicitWidth: screenWindow.width
            implicitHeight: screenWindow.height
            screen: screenWindow.screen
            visible: true

            deviceConfiguration {
                overrideName: Screens.count > 1 ? "desktop" : false
            }
        }
    }

    Component {
        id: disabledScreenComponent
        DisabledScreenNotice {
            screen: screenWindow.screen
            oskEnabled: Screens.count > 1
        }
    }
}
