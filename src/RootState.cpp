/*
 * Copyright (C) 2026 UBports Foundation.
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

#include "RootState.h"

RootState::RootState(QObject* parent) : QObject(parent),
    m_skipGreeterAtStart(true)
{
}

void RootState::reset()
{
    const bool oldSkipGreeterAtStart = m_skipGreeterAtStart;
    m_skipGreeterAtStart = true;
    if (oldSkipGreeterAtStart != m_skipGreeterAtStart) {
        Q_EMIT skipGreeterAtStartChanged();
    }
}
