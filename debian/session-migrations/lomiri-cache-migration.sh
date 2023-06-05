#!/bin/sh -euf
#
# Copyright (C) 2023 UBports Foundation
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Ratchanan Srirattanamet <ratchanan@ubports.com>

# Note: can afford to do destructive migration since this is just a cache.

# Contains old qmlcache, most of which is obsoleted due to renames.
old_path="${HOME}/.cache/Canonical/unity8"

if [ -d "$old_path" ]; then
    rm -r "$old_path"
fi

# Contains qmlcache, but this time a new one.
old_path="${HOME}/.cache/Canonical/lomiri"
new_path="${HOME}/.cache/UBports/lomiri"

if [ -d "$old_path" ]; then
    if ! [ -d "$new_path" ]; then
        mkdir -p "$(dirname "$new_path")"
        mv "$old_path" "$new_path"
    else
        rm -r "$old_path"
    fi
fi

# rmdir remove folder only if it's empty. It should be by now, but just in case.
rmdir --ignore-fail-on-non-empty "${HOME}/.cache/Canonical"

# Contains "windowstatestorage.sqlite".
old_path="${HOME}/.cache/unity8"
new_path="${HOME}/.cache/lomiri"

if [ -d "$old_path" ]; then
    if ! [ -d "$new_path" ]; then
        mv "$old_path" "$new_path"
    else
        rm -r "$old_path"
    fi
fi
