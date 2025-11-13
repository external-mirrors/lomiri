/*
 * Copyright (C) 2025 UBports Foundation
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
import Lomiri.Components 1.3
import Lomiri.Components.Extras 0.2 as Extras
import Lomiri.Content 1.1
import Utils 0.1

Item {
    id: root
    visible: false

    property var itemGrabber : null
    property var panel : null
    property var launcher : null
    property var greeter : null
    property var wizard : null

    property string prevLauncherState : "visible"

    Connections {
        target: panel

        // Hide the launcher if the indicator panel has been tapped
        function onFullyClosedChanged() {
            if (!root.visible)
                return;

            if (panel.fullyClosed)
                launcher.switchToNextState("");
        }
    }

    function show(path) {
        if (wizard.active)
            return;

        screenshotSharePicker.filePath = path;
        visible = true;
        screenshotEditor.open(path);
        prevLauncherState = launcher.state;
        launcher.switchToNextState("");
    }

    function hide() {
        screenshotSharePicker.visible = false;
        screenshotSharePicker.filePath = "";
        visible = false;
        launcher.switchToNextState(root.prevLauncherState);
    }

    // Make locking the screen abort the editing session, otherwise we
    // would show the editor above the lockscreen.
    Connections {
        target: greeter
        function onLockedChanged() {
            if (!root.visible)
                return;

            if (greeter.locked)
                root.hide()
        }
    }

    PageHeader {
        id: screenshotEditorHeader
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: panel.panelHeight
        height: implicitHeight
        leadingActionBar {
            actions: [
                Action {
                    iconName: "edit-delete"
                    text: i18n.tr("Delete")
                    onTriggered: {
                        FileIo.remove(screenshotSharePicker.filePath);
                        root.hide();
                    }
                }
            ]
        }
        trailingActionBar {
            actions: [
                Action {
                    iconName: "document-save"
                    text: i18n.tr("Save")
                    onTriggered: {
                        screenshotEditor.close(true);
                        root.hide();
                    }
                },
                Action {
                    iconName: "share"
                    text: i18n.tr("Share")
                    onTriggered: {
                        screenshotEditor.close(true);
                        screenshotSharePicker.visible = true;
                    }
                }
            ]
        }
    }

    Extras.PhotoEditor {
        id: screenshotEditor
        y: panel.panelHeight + screenshotEditorHeader.height
        width: parent.width
        height: parent.height - screenshotEditorHeader.height - panel.panelHeight
    }

    ContentPeerPicker {
        id: screenshotSharePicker
        anchors {
            fill: parent
            topMargin: panel.panelHeight
        }
        visible: false
        showTitle: true
        contentType: ContentType.Pictures
        handler: ContentHandler.Share

        property string filePath : ""

        Component {
            id: resultComponent
            ContentItem {}
        }

        onPeerSelected: {
            let activeTransfer = peer.request();
            activeTransfer.stateChanged.connect(function() {
                if (activeTransfer.state === ContentTransfer.InProgress) {
                    const url = "file://" + screenshotSharePicker.filePath
                    console.log("In progress: " + url);
                    activeTransfer.items = [ resultComponent.createObject(parent,
                                                                          {"url": url})
                            ];
                    activeTransfer.state = ContentTransfer.Charged;
                    root.hide();
                }
            })
        }

        onCancelPressed: {
            root.hide();
        }
    }
}
