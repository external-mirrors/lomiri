/*
 * Copyright (C) 2016-2017 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOMIRI_SCREENWINDOW_H
#define LOMIRI_SCREENWINDOW_H

#include <QQuickWindow>
#include <QPointer>

#include "ucunits.h"
#include "Screen.h"

class ScreenAdapter;

/*
 * ScreenWindow - wrapper of QQuickWindow to enable QML to specify destination screen.
**/
class ScreenWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(ConcreteScreen *screen READ screenWrapper WRITE setScreenWrapper NOTIFY screenWrapperChanged)
    Q_PROPERTY(int winId READ winId CONSTANT)
    Q_PROPERTY(UCUnits* units READ units NOTIFY unitsChanged)

public:
    explicit ScreenWindow(QQuickWindow *parent = 0);
    ~ScreenWindow();

    ConcreteScreen *screenWrapper() const;
    void setScreenWrapper(ConcreteScreen *screen);
    UCUnits* units();

Q_SIGNALS:
    void screenWrapperChanged(ConcreteScreen* screen);
    void unitsChanged();

private:
    QPointer<ConcreteScreen> m_screen;
    UCUnits* m_units = nullptr;
};

#endif // LOMIRI_SCREENWINDOW_H
