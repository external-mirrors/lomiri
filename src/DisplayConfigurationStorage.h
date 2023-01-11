/*
 * Copyright (C) 2017 Canonical Ltd.
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

#ifndef LOMIRI_DISPLAYCONFIGURATIONSTORAGE_H
#define LOMIRI_DISPLAYCONFIGURATIONSTORAGE_H

#ifndef USE_MIROIL
#include <qtmir/miral/display_configuration_storage.h>
namespace miroil = miral;
#else
#include <miroil/display_configuration_storage.h>
#endif

class DisplayConfigurationStorage : public miroil::DisplayConfigurationStorage
{
public:
    DisplayConfigurationStorage();

    void save(const miroil::DisplayId& displayId, const miroil::DisplayConfigurationOptions& options) override;
    bool load(const miroil::DisplayId& displayId, miroil::DisplayConfigurationOptions& options) const override;
};

#endif // LOMIRI_DISPLAYCONFIGURATIONSTORAGE_H
