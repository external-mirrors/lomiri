/*
 * Copyright (C) 2013-2014 Canonical Ltd.
 * Copyright (C) 2020 UBports Foundation
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
import QtQuick.Window 2.15 as QtQuickWindow
import Lomiri.Components 1.3
import Lomiri.Session 0.1
import ".."
import "../Components"

Item {
    id: root
    implicitWidth: flickable.width
    implicitHeight: units.gu(3)

    property int align: Qt.AlignRight
    property int orientation: Qt.Horizontal
    property real constantSize: -1
    property bool clip: true
    property alias interactive: flickable.interactive
    property var collapsedCutouts: []
    property var expandedCutouts: []
    property real collapsedHeight: units.gu(3)

    DeviceConfiguration {
        id: deviceConfig
    }

    Component.onCompleted: {
        const parts = deviceConfig.cutouts.split(";");
        root.collapsedHeight = parseFloat(parts[0]);
        const parseCutouts = (cutout) => {
            const rect = cutout.split(",").map((val) => parseFloat(val));
            return Qt.rect(rect[0], rect[1], rect[2], rect[3]);
        };
        root.collapsedCutouts = parts[1].split("/").map(parseCutouts);
        root.expandedCutouts = parts[2].split("/").map(parseCutouts);
    }

    property bool isPortrait: QtQuickWindow.Screen.orientation == Qt.PortraitOrientation
    property var oldRotation: Qt.PortraitOrientation
    onIsPortraitChanged: {
        if (!OrientationLock.enabled) {
            oldRotation = QtQuickWindow.Screen.orientation;
        }
    }
    property var cutouts: {
        if (oldRotation != Qt.PortraitOrientation) {
            return [];
        }
        return expanded ? root.expandedCutouts : root.collapsedCutouts;
    }

    onCutoutsChanged: {
        d.recalculateItems();
        // FIXME: screen rotation has an animation, get info when its done to recalculate
        rotationHackTimer.start();
    }

    property bool hideRow: false
    property QtObject model: null
    property real overFlowWidth: width
    property bool expanded: false

    property var currentItem: null
    property int currentItemIndex: 0

    onCurrentItemIndexChanged: {
        root.alignCurrentItem();
    }

    onHeightChanged: {
        root.alignCurrentItem(true);
    }

    function alignCurrentItem(underFinger) {
        currentItem = repeater.itemAt(currentItemIndex);
        if (!currentItem) {
            return;
        }

        const targetPos = underFinger ? lateralPosition :
            currentItem.x + currentItem.width + 40 > flickable.width + flickable.contentX
                ? flickable.width - currentItem.width - 40
                : currentItem.x - 40 < flickable.contentX
                        ? currentItem.width + 40
                        : -1;

        if (targetPos == -1) {
            return;
        }

        let distX = targetPos - currentItem.x - currentItem.width / 2 + flickable.contentX;
        if (Math.abs(distX) > 5) {
            flickable.contentX -= distX;
        }
        d.recalculateItems();
    }

    property real unitProgress: 0.0
    property real selectionChangeBuffer: units.gu(2)
    property bool enableLateralChanges: false
    property bool lightMode: false

    property alias delegate: repeater.delegate
    property alias contentX: flickable.contentX

    property real lateralPosition: -1
    onLateralPositionChanged: {
        updateItemFromLateralPosition();
    }

    onEnableLateralChangesChanged: {
        updateItemFromLateralPosition();
    }

    function updateItemFromLateralPosition() {
        if (!enableLateralChanges || lateralPosition === -1)
            return;

        if (!currentItem) {
            selectItemAt(lateralPosition);
            return;
        }

        var maximumBufferOffset = selectionChangeBuffer * unitProgress;
        var proposedItem = indicatorAt(lateralPosition, 0);
        if (proposedItem) {
            var bufferExceeded = false;

            if (proposedItem !== currentItem) {
                // Proposed item is not directly adjacent to current?
                if (Math.abs(proposedItem.ownIndex - currentItem.ownIndex) > 1) {
                    bufferExceeded = true;
                } else {
                    // no
                    var currentItemLateralPosition = root.mapToItem(proposedItem, lateralPosition, 0).x;

                    // Is the distance into proposed item greater than max buffer?
                    // Proposed item is before current item
                    if (proposedItem.x < currentItem.x) {
                        bufferExceeded = (proposedItem.width - currentItemLateralPosition) > maximumBufferOffset;
                    } else {
                        // After
                        bufferExceeded = currentItemLateralPosition > maximumBufferOffset;
                    }
                }
                if (bufferExceeded) {
                    selectItemAt(lateralPosition, true);
                }
            }
        } else {
            selectItemAt(lateralPosition, true);
        }
    }

    function indicatorAt(x, y) {
        // FIXME: y
        const pos = x + flickable.contentX - (x < 40 ? 40 : 0);
        // NOTE: this is a bit of a mess to grasp
        // the x coordinate grows right to left, but indexes go left to right
        // meaning indicator 0 is the leftmost one with the highest x coordinate
        for (let i = 0; i < repeater.count; i++) {
            const candidate = repeater.itemAt(i);
            // next indicator is the higher index, on the right, with the lower x coord
            const distanceToNext = i < repeater.count - 1 ? candidate.x - repeater.itemAt(i + 1).width - repeater.itemAt(i + 1).x : 0;
            const distanceToPrev = i > 0 ? repeater.itemAt(i - 1).x - candidate.width - candidate.x : 0;
            const addToX = distanceToNext / 2;
            const addToW = distanceToPrev / 2;
            const cX = candidate.x - addToX;
            const cW = candidate.width + addToW;
            if (cX <= pos && candidate.x + cW > pos && candidate.hasOwnProperty('ownIndex')) {
                return candidate;
            }
        }
    }

    function resetCurrentItem() {
        root.currentItemIndex = -1;
    }

    function selectPreviousItem() {
        let indexToSelect = currentItemIndex - 1;
        while (indexToSelect >= 0) {
            if (setCurrentItemIndex(indexToSelect)) {
                return;
            }
            indexToSelect -= 1;
        }
    }

    function selectNextItem() {
        let indexToSelect = currentItemIndex + 1;
        while (indexToSelect < repeater.count) {
            if (setCurrentItemIndex(indexToSelect)) {
                return;
            }
            indexToSelect += 1;
        }
    }

    function setCurrentItemIndex(index) {
        for (let i = 0; i < repeater.count; i++) {
            const candidate = repeater.itemAt(i);
            if (candidate.hasOwnProperty('ownIndex') && candidate.ownIndex === index && candidate.enabled) {
                root.currentItemIndex = index;
                return true;
            }
        }

        return false;
    }

    /**
     * Selects the item at the specified X coordinate
     *
     * @param {number} x
     * @param {boolean} [noWrap=false] whether to wrap to start/end if the item is not found
     */
    function selectItemAt(x, noWrap) {
        const item = indicatorAt(x, 0);
        if (item && item.opacity > 0 && item.enabled) {
            root.currentItemIndex = item.ownIndex;
        } else if (!noWrap) {
            const searchIndex = x <= width ? repeater.count - 1 : 0;
            setCurrentItemIndex(searchIndex);
        }
    }

    Timer {
        id: rotationHackTimer
        interval: 50
        running: false
        onTriggered: {
            stop();
            d.recalculateItems();
        }
    }

    QtObject {
        id: d
        property var previousItem
        property bool forceAlignmentAnimationDisabled: false

        property bool isFlipped: {
            root.align === Qt.AlignRight && root.orientation === Qt.Horizontal || root.align === Qt.AlignBottom && root.orientation === Qt.Vertical;
        }
        property bool isHorizontal: root.orientation === Qt.Horizontal
        property var positions: []
        property var cutoutsModel: ListModel {}

        function recalculateItems() {
            const sizeField = isHorizontal ? 'width' : 'height';
            const posField = isHorizontal ? 'x' : 'y';
            const flickableField = isHorizontal ? 'contentX' : 'contentY';
            let currentX = 0;
            let screenX = 0;
            let itemMaxSize = 0;

            for (let i = 0; i < repeater.count; i++) {
                const item = repeater.itemAt(repeater.count - 1 - i);
                const itemSize = Math.ceil(item[sizeField]);

                if (itemSize > itemMaxSize) {
                    itemMaxSize = itemSize;
                }

                screenX = currentX - flickable[flickableField];

                for (let ci = 0; ci < root.cutouts.length; ci++) {
                    const cutout = root.cutouts[ci];
                    const cutoutSize = Math.floor(cutout[sizeField]);
                    const cutoutPos = Math.floor(d.isFlipped ? root[sizeField] - cutout[posField] - cutoutSize : cutout[posField]);

                    if (screenX > cutoutPos + cutoutSize || screenX + itemSize <= cutoutPos) {
                        continue;
                    }

                    screenX = cutoutPos + cutoutSize;
                    currentX = screenX + flickable[flickableField];
                }

                item[posField] = currentX;
                item.rotation = d.isFlipped ? -180 : 0;
                currentX += itemSize;
            }

            const lastCutout = root.cutouts[root.cutouts.length - 1] || { x: 0, y: 0 };
            const lastSectionSize = Math.floor(root[sizeField] - lastCutout[posField] - lastCutout[sizeField]);
            const lastItemSize = repeater.itemAt(repeater.count - 1) ? Math.ceil(repeater.itemAt(repeater.count - 1)[sizeField]) : 0;
            const cutoutsSize = root.cutouts.reduce((prev, curr) => prev + curr[sizeField], 0);
            if (lastSectionSize < lastItemSize) {
                // TODO: this is not the proper solution
                //       with this, you can slide the last item too far in the direction of the alignment
                //       but otherwise the last item will be forced outside the bounds
                currentX += itemMaxSize + cutoutsSize;
            }

            flickable[isHorizontal ? 'contentWidth' : 'contentHeight'] = currentX;
        }
    }

    Flickable {
        id: flickable
        pixelAligned: true
        anchors.fill: root
        interactive: false
        flickableDirection: d.isHorizontal ? Flickable.HorizontalFlick : Flickable.VerticalFlick
        rotation: d.isFlipped ? 0 : 180

        Behavior on contentX {
            enabled: enableLateralChanges
            NumberAnimation {
                duration: LomiriAnimation.BriskDuration
                easing: LomiriAnimation.StandardEasing
            }
        }

        onContentXChanged: {
            d.recalculateItems();
        }
        onContentYChanged: {
            d.recalculateItems();
        }
        onContentWidthChanged: {
            if (!interactive) {
                rotationHackTimer.start();
            }
        }

        Repeater {
            id: repeater
            model: root.model
            objectName: "panelRow"
        }
    }

    Rectangle {
        id: highlight
        objectName: "highlight"

        anchors.bottom: repeater.bottom
        height: units.dp(2)
        color: theme.palette.normal.foregroundText
        visible: currentItem !== null
        opacity: 0.0

        width: currentItem ? currentItem.width : 0
        Behavior on width {
            enabled: enableLateralChanges && expanded
            LomiriNumberAnimation {
                duration: LomiriAnimation.FastDuration
                easing: LomiriAnimation.StandardEasing
            }
        }

        // micromovements of the highlight line when user moves the finger across the items while pulling
        // the handle downwards.
        property real highlightCenterOffset: {
            if (!currentItem || lateralPosition == -1 || !enableLateralChanges)
                return 0;

            var itemMapped = root.mapToItem(currentItem, lateralPosition, 0);

            var distanceFromCenter = -itemMapped.x + currentItem.width / 2;
            if (distanceFromCenter > 0) {
                distanceFromCenter = Math.max(0, distanceFromCenter - currentItem.width / 8);
            } else {
                distanceFromCenter = Math.min(0, distanceFromCenter + currentItem.width / 8);
            }

            if (currentItem && currentItem.ownIndex === 0 && distanceFromCenter < 0) {
                return 0;
            } else if (currentItem && currentItem.ownIndex === row.count - 1 & distanceFromCenter > 0) {
                return 0;
            }
            return (distanceFromCenter / (currentItem.width / 4)) * units.gu(1);
        }

        Behavior on highlightCenterOffset {
            NumberAnimation {
                duration: LomiriAnimation.FastDuration
                easing: LomiriAnimation.StandardEasing
            }
        }

        property real currentItemX: currentItem ? currentItem.x - flickable.contentX : 0
        Behavior on currentItemX {
            id: currentItemXBehavior
            enabled: enableLateralChanges && expanded && !d.forceAlignmentAnimationDisabled && !flickable.moving
            NumberAnimation {
                duration: LomiriAnimation.FastDuration
                easing: LomiriAnimation.StandardEasing
            }
        }
        x: currentItemX + highlightCenterOffset
    }

    states: [
        State {
            name: "minimised"
            when: !expanded
        },
        State {
            name: "expanded"
            when: expanded
            PropertyChanges {
                target: highlight
                opacity: 0.9
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                properties: "opacity"
                duration: LomiriAnimation.SnapDuration
                easing: LomiriAnimation.StandardEasing
            }
        }
    ]
}
