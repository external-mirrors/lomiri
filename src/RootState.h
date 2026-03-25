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

#ifndef ROOTSTATE_H
#define ROOTSTATE_H

#include <QObject>

class RootState : public QObject
{
    Q_OBJECT

    // Only read in lomiri-full-shell mode
    Q_PROPERTY(bool skipGreeterAtStart MEMBER m_skipGreeterAtStart NOTIFY skipGreeterAtStartChanged)

public:
    RootState(QObject* parent = nullptr);

private:
    bool m_skipGreeterAtStart;

Q_SIGNALS:
    void skipGreeterAtStartChanged();
};

#endif // ROOTSTATE_H
