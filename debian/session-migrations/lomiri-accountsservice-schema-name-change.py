#!/usr/bin/python3
# -*- coding: utf-8; indent-tabs-mode: nil; tab-width: 4 -*-
#
# Copyright (C) 2016 Canonical Ltd.
# Copyright (C) 2021 UBports Foundation
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; version 3.
#
# This program is distributed in the hope that it will be useful, but WITHOUTa
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Ratchanan Srirattanamet <ratchanan@ubports.com>

import dbus
import os
import sys

from typing import List, Tuple
from pathlib import Path

AS_SCHEMAS: List[Tuple[str, str]] = [
    ('com.canonical.unity.AccountsService', 'com.lomiri.shell.AccountsService'),
    ('com.canonical.unity.AccountsService.Private', 'com.lomiri.shell.AccountsService.Private'),
]
# session-migration says we should be idempotent. However, we cannot determine
# that from AccountsService as it will happily provide us the default value in
# the schema. So, we need an out-of-band method to determine if we have run this
# or not. In this case, we simply use a marker file.
marker_path = Path('~/.config/lomiri/accountsservice-schema-migration-has-run').expanduser()

if marker_path.exists():
    print(f'{marker_path} exists, which mean the migration has run. Exit now.')
    sys.exit(0)

# Due to the mistake in the mtime workaround [1], it means this script could be
# run after the first boot on Focal. In that case, we must NOT migrate the
# settings, as otherwise we'll overwrite existing settings.
#
# Here, we rely on the fact that `luitk-config-migration.sh` runs after us
# (session-migration sorts the scripts before running). So, if LUITK's theme.ini
# exists by this time, it must mean that renamed Lomiri has run at least once.
#
# [1] https://gitlab.com/ubports/ubuntu-touch/-/issues/2177

luitk_theme_path = Path('~/.config/lomiri-ui-toolkit/theme.ini').expanduser()
if luitk_theme_path.exists():
    print("LUITK theme settings exist, which mean Lomiri has run. Don't overwrite settings!")
    marker_path.touch(mode=0o644)
    sys.exit(0)

system_bus = dbus.SystemBus()
manager_proxy = system_bus.get_object('org.freedesktop.Accounts',
                                      '/org/freedesktop/Accounts')
object_path = manager_proxy.FindUserById(
    os.getuid(), dbus_interface='org.freedesktop.Accounts'
)
user_proxy = system_bus.get_object('org.freedesktop.Accounts', object_path)
user_properties_if = dbus.Interface(user_proxy, dbus.PROPERTIES_IFACE)

for (src_schema, dst_schema) in AS_SCHEMAS:
    print(f'Migrating {src_schema} to {dst_schema}')

    src_props = user_properties_if.GetAll(src_schema)
    for (key, value) in src_props.items():
        user_properties_if.Set(dst_schema, key, value)

marker_path.parent.mkdir(mode=0o755, parents=True, exist_ok=True)
marker_path.touch(mode=0o644)

print('Migrating Lomiri AccountsService settings is successful.')
