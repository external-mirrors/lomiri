/*
 * Copyright (C) 2017 Canonical Ltd.
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

#include "AvailableDesktopArea.h"

#include <QGuiApplication>
#include <QQuickWindow>
#include <qpa/qplatformnativeinterface.h>

AvailableDesktopArea::AvailableDesktopArea(QQuickItem *parent)
    : QQuickItem(parent)
{
    auto queued = Qt::QueuedConnection;

    connect(this, &QQuickItem::xChanged,
            this, &AvailableDesktopArea::requestUpdate,
            queued);

    connect(this, &QQuickItem::yChanged,
            this, &AvailableDesktopArea::requestUpdate,
            queued);

    connect(this, &QQuickItem::widthChanged,
            this, &AvailableDesktopArea::requestUpdate,
            queued);

    connect(this, &QQuickItem::heightChanged,
            this, &AvailableDesktopArea::requestUpdate,
            queued);
}

void AvailableDesktopArea::bindToWindow(QWindow *w)
{
    if (!w)
        return;


    auto queued = Qt::QueuedConnection;

    connect(w, &QWindow::widthChanged,
            this, &AvailableDesktopArea::requestUpdate, queued);
    connect(w, &QWindow::heightChanged,
            this, &AvailableDesktopArea::requestUpdate, queued);
    connect(w, &QWindow::xChanged,
            this, &AvailableDesktopArea::requestUpdate, queued);
    connect(w, &QWindow::yChanged,
            this, &AvailableDesktopArea::requestUpdate, queued);
    connect(w, &QWindow::visibilityChanged,
            this, &AvailableDesktopArea::requestUpdate, queued);
    connect(w, &QWindow::windowStateChanged,
            this, &AvailableDesktopArea::requestUpdate, queued);

    connect(w, SIGNAL(afterAnimating()),
            this, SLOT(requestUpdate()),
            queued);


    // Le signal qui fixe vraiment ton problème fullscreen
    // connect(w, &QQuickWindow::afterAnimating,
    //         this, &AvailableDesktopArea::requestUpdate, queued);

}

void AvailableDesktopArea::itemChange(ItemChange change,
                                      const ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);

    if (change == ItemSceneChange) {

        QWindow *w = window();

        if (w) {
            bindToWindow(w);
            QMetaObject::invokeMethod(this,
                                      &AvailableDesktopArea::requestUpdate,
                                      Qt::QueuedConnection);
        }
    }
}

void AvailableDesktopArea::requestUpdate()
{
    // -> Prevent from flooding changes
    if (!m_updatePending) {
        m_updatePending = true;

        QTimer::singleShot(0, this, &AvailableDesktopArea::updatePlatformWindowProperty);

    }
}

void AvailableDesktopArea::updatePlatformWindowProperty()
{

    m_updatePending = false;

    if (!window())
        return;

    auto *nativeInterface = QGuiApplication::platformNativeInterface();

    QRect rect(x(), y(), width(), height());

    nativeInterface->setWindowProperty(window()->handle(),
                                       "availableDesktopArea",
                                       QVariant(rect));
}
