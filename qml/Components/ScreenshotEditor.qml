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

    property var panel : null
    property var launcher : null

    property string prevLauncherState : ""

    function show(path) {
        if (!root.enabled)
            return;

        screenshotSharePicker.filePath = path;
        visible = true;
        screenshotEditor.open(path);
    }

    function hide() {
        screenshotSharePicker.visible = false;
        screenshotSharePicker.filePath = "";
        visible = false;
    }

    // Don't store and restore the wrong state once the editor has been opened already
    onVisibleChanged: {
        if (visible) {
            prevLauncherState = launcher.state;
            launcher.switchToNextState("");
        } else {
            launcher.switchToNextState(root.prevLauncherState);
        }
    }

    Extras.PhotoEditor {
        id: screenshotEditor
        y: panel.panelHeight + screenshotEditorHeader.height
        width: parent.width
        height: parent.height - screenshotEditorHeader.height - panel.panelHeight
    }

    // Place the PageHeader below the editor for proper z-level layering,
    // otherwise pictures would overlay and peek out over the header.
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
            const activeTransfer = peer.request();
            activeTransfer.stateChanged.connect(function() {
                if (activeTransfer.state === ContentTransfer.InProgress) {
                    const url = "file://" + screenshotSharePicker.filePath
                    console.log("File transfer in progress: " + url);
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
