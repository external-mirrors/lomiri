/*
 * Copyright (C) 2015 Canonical Ltd.
 * Copyright (C) 2021 UBports Foundation
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
import QtTest 1.0
import Lomiri.SelfTest 0.1

import "../../../qml/Components"


Image {
    id: root
    width: 70
    height: 70

    source: imageResolver.resolvedImage

    readonly property url blue: Qt.resolvedUrl("../../data/lomiri/backgrounds/blue.png")
    readonly property url red: Qt.resolvedUrl("../../data/lomiri/backgrounds/red.png")
    readonly property url big: Qt.resolvedUrl("../../graphics/applicationIcons/dash.png")

    ImageResolver {
        id: imageResolver

        property var pastImages: []

        onResolvedImageChanged: pastImages.push(resolvedImage)
    }

    SignalSpy {
        id: spy
        signalName: "resolvedImageChanged"
        target: imageResolver
    }

    LomiriTestCase {
        id: testCase
        name: "ImageResolver"
        when: windowShown

        function test_background_data() {
            return [
                {tag: "empty-candidates",
                 list: [],
                 output: ""},

                {tag: "blank-candidate",
                 list: [""],
                 output: ""},

                {tag: "blank-urls",
                 list: [Qt.resolvedUrl(""), Qt.resolvedUrl(""), root.blue],
                 output: root.blue},

                {tag: "invalid-urls",
                 list: [Qt.resolvedUrl("/first"), Qt.resolvedUrl("/middle"), root.blue],
                 output: root.blue},

                {tag: "valid-after-blanks",
                 list: ["", "", root.red],
                 output: root.red},

                // Ensure that the ImageResolver doesn't get stuck if it
                // sees the same invalid wallpaper multiple times in a row
                {tag: "valid-after-the-same-invalid",
                 list: ["/first", "/first", "/first", root.red],
                 output: root.red},

                {tag: "naughty",
                 list: [null, undefined, "", NaN, 1.0, 1, root.red, null],
                 output: root.red},

                {tag: "none-valid",
                 list: ["/first", "/middle", "/last"],
                 output: Qt.resolvedUrl("/last")},

                {tag: "first-valid",
                 list: [root.blue, "/middle", "/last"],
                 output: root.blue},

                {tag: "middle-valid",
                 list: ["/first", root.red, "/last"],
                 output: root.red},

                {tag: "last-valid",
                 list: ["/first", "/middle", root.red],
                 output: root.red},

                {tag: "multiple-valid",
                 list: [root.blue, root.red],
                 output: root.blue},

                {tag: "multiple-valid-after-multiple-invalid",
                 list: ["/first", "/middle", "/last", root.blue, root.red],
                 output: root.blue},

            ]
        }

        function init() {
            // Make sure we don't have our next test compare() to the results
            // of the last test by exercising the resolver
            imageResolver.cache = true;
            imageResolver.candidates = [];
            tryCompare(imageResolver, "resolvedImage", "");
            imageResolver.pastImages = [];
            imageResolver.candidates = [root.blue, root.blue];
            tryCompare(imageResolver, "resolvedImage", root.blue);
            imageResolver.candidates = [];
            tryCompare(imageResolver, "resolvedImage", "");
            tryCompare(imageResolver, "pastImages", [root.blue, Qt.resolvedUrl("")])
            imageResolver.pastImages = [];
        }

        function test_background(data) {
            imageResolver.candidates = data.list;
            tryCompare(imageResolver, "resolvedImage", data.output);
        }

        function test_reload_with_blanks() {
            imageResolver.candidates = ["", "", root.red];
            tryCompare(imageResolver, "resolvedImage", root.red);
            imageResolver.candidates = ["", "", root.blue];
            tryCompare(imageResolver, "resolvedImage", root.blue);
        }

        // ImageResolver loads images asynchronously. It's important to make
        // sure that it never returns the wrong image just because they loaded
        // in the wrong order. So we set its images 100 times.
        function test_images_changing() {
            imageResolver.cache = false;
            for (var i = 0; i < 50; i++) {
                // We don't spy on the first one because the wallpaper doesn't
                // transition from a set url to "" the first time.
                imageResolver.candidates = [root.red, root.big, root.blue];
                tryCompare(imageResolver, "resolvedImage", root.red);

                spy.clear();
                imageResolver.pastImages = [];
                imageResolver.candidates = [root.big, root.blue, root.red];
                tryCompare(imageResolver, "resolvedImage", root.big);
                compare(imageResolver.pastImages, ["", root.big])
                compare(spy.count, 4);
            }
        }
    }
}
