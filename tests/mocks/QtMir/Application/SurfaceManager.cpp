/*
 * Copyright (C) 2014-2016 Canonical Ltd.
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

#include "SurfaceManager.h"

#include "ApplicationInfo.h"
#include "VirtualKeyboard.h"
#include "../../WindowManager/WindowManagementPolicy.h"

#include <paths.h>

#define SURFACEMANAGER_DEBUG 1

#if SURFACEMANAGER_DEBUG
#define DEBUG_MSG(params) qDebug().nospace() << "SurfaceManager[" << (void*)this << "]::" << __func__  << params
#else
#define DEBUG_MSG(params) ((void)0)
#endif

namespace lomiriapi = lomiri::shell::application;

SurfaceManager *SurfaceManager::m_instance = nullptr;

SurfaceManager *SurfaceManager::instance()
{
    return m_instance;
}

SurfaceManager::SurfaceManager(QObject *)
{
    DEBUG_MSG("");

    Q_ASSERT(m_instance == nullptr);
    m_instance = this;

    connect(WindowManagementPolicy::instance(), &WindowManagementPolicy::surfaceAdded,
            this, &SurfaceManager::surfaceCreated);

    connect(WindowManagementPolicy::instance(), &WindowManagementPolicy::surfacesAddedToWorkspace,
            this, &SurfaceManager::surfacesAddedToWorkspace);

    connect(WindowManagementPolicy::instance(), &WindowManagementPolicy::surfacesAboutToBeRemovedFromWorkspace,
            this, &SurfaceManager::surfacesAboutToBeRemovedFromWorkspace);
}

SurfaceManager::~SurfaceManager()
{
    DEBUG_MSG("");

    releaseInputMethodSurface();

    Q_ASSERT(m_instance == this);
    m_instance = nullptr;
}

bool SurfaceManager::isRegistered(MirSurfaceInterface *surface) const
{
    return std::find(m_surfaces.begin(), m_surfaces.end(), surface) != m_surfaces.end();
}

MirSurface *SurfaceManager::createSurface(const QString& name,
                                          Mir::Type type,
                                          Mir::State state,
                                          MirSurface *parentSurface,
                                          const QUrl &screenshot,
                                          const QUrl &qmlFilePath)
{
    MirSurface* surface = new MirSurface(name, type, state, parentSurface, screenshot, qmlFilePath);
    registerSurface(surface);
    if (parentSurface) {
        static_cast<MirSurfaceListModel*>(parentSurface->childSurfaceList())->addSurface(surface);
    }
    return surface;
}

void SurfaceManager::registerSurface(MirSurface *surface)
{
    m_surfaces.prepend(surface);

    if (!surface->parentSurface()) {
        surface->setMinimumWidth(m_newSurfaceMinimumWidth);
        surface->setMaximumWidth(m_newSurfaceMaximumWidth);
        surface->setMinimumHeight(m_newSurfaceMinimumHeight);
        surface->setMaximumHeight(m_newSurfaceMaximumHeight);
        surface->setWidthIncrement(m_newSurfaceWidthIncrement);
        surface->setHeightIncrement(m_newSurfaceHeightIncrement);
    }

    connect(surface, &MirSurface::stateRequested, this, [=](Mir::State state) {
        this->onStateRequested(surface, state);
    });

    connect(surface, &QObject::destroyed, this, [=]() {
        if (isRegistered(surface)) {
            WindowManagementPolicy::instance()->removeSurface(surface);
            this->onSurfaceDestroyed(surface);
        }
    });
}

void SurfaceManager::notifySurfaceCreated(lomiriapi::MirSurfaceInterface *surface)
{
    if (Q_UNLIKELY(!isRegistered(surface))) {
        Q_EMIT surfaceCreated(surface);
        return;
    }

    WindowManagementPolicy::instance()->addSurface(surface);
}

void SurfaceManager::setNewSurfaceMinimumWidth(int value)
{
    if (m_newSurfaceMinimumWidth != value) {
        m_newSurfaceMinimumWidth = value;
        Q_EMIT newSurfaceMinimumWidthChanged(m_newSurfaceMinimumWidth);
    }
}

void SurfaceManager::setNewSurfaceMaximumWidth(int value)
{
    if (m_newSurfaceMaximumWidth != value) {
        m_newSurfaceMaximumWidth = value;
        Q_EMIT newSurfaceMaximumWidthChanged(m_newSurfaceMaximumWidth);
    }
}

void SurfaceManager::setNewSurfaceMinimumHeight(int value)
{
    if (m_newSurfaceMinimumHeight != value) {
        m_newSurfaceMinimumHeight = value;
        Q_EMIT newSurfaceMinimumHeightChanged(m_newSurfaceMinimumHeight);
    }
}

void SurfaceManager::setNewSurfaceMaximumHeight(int value)
{
    if (m_newSurfaceMaximumHeight != value) {
        m_newSurfaceMaximumHeight = value;
        Q_EMIT newSurfaceMaximumHeightChanged(m_newSurfaceMaximumHeight);
    }
}

void SurfaceManager::setNewSurfaceWidthIncrement(int value)
{
    if (m_newSurfaceWidthIncrement != value) {
        m_newSurfaceWidthIncrement = value;
        Q_EMIT newSurfaceWidthIncrementChanged(m_newSurfaceWidthIncrement);
    }
}

void SurfaceManager::setNewSurfaceHeightIncrement(int value)
{
    if (m_newSurfaceHeightIncrement != value) {
        m_newSurfaceHeightIncrement = value;
        Q_EMIT newSurfaceHeightIncrementChanged(m_newSurfaceHeightIncrement);
    }
}

void SurfaceManager::raise(lomiriapi::MirSurfaceInterface *surface)
{
    if (m_underModification)
        return;

    DEBUG_MSG("("<<surface<<") started");
    Q_EMIT modificationsStarted();
    m_underModification = true;

    doRaise(surface);

    m_underModification = false;
    Q_EMIT modificationsEnded();
    DEBUG_MSG("("<<surface<<") ended");
}

void SurfaceManager::doRaise(lomiriapi::MirSurfaceInterface *apiSurface)
{
    auto surface = static_cast<MirSurface*>(apiSurface);
    int index = m_surfaces.indexOf(surface);
    Q_ASSERT(index != -1);
    m_surfaces.move(index, 0);

    Q_EMIT surfacesRaised({surface});
}

void SurfaceManager::activate(lomiriapi::MirSurfaceInterface *apiSurface)
{
    auto surface = static_cast<MirSurface*>(apiSurface);

    if (surface == m_focusedSurface) {
        return;
    }

    Q_ASSERT(!m_underModification);

    DEBUG_MSG("("<<surface<<") started");
    Q_EMIT modificationsStarted();
    m_underModification = true;
    if (m_focusedSurface) {
        m_focusedSurface->setFocused(false);
    }
    if (surface) {
        if (surface->state() == Mir::HiddenState || surface->state() == Mir::MinimizedState) {
            if (surface->previousState() != Mir::UnknownState) {
                surface->setState(surface->previousState());
            } else {
                surface->setState(Mir::RestoredState);
            }
        }
        surface->setFocused(true);
        doRaise(surface);
    }
    m_focusedSurface = surface;
    m_underModification = false;
    Q_EMIT modificationsEnded();
    DEBUG_MSG("("<<surface<<") ended");
}

void SurfaceManager::forEachSurfaceInWorkspace(const std::shared_ptr<miral::Workspace> &workspace,
                                               const std::function<void(lomiri::shell::application::MirSurfaceInterface*)> &callback)
{
    WindowManagementPolicy::instance()->forEachSurfaceInWorkspace(workspace, callback);
}

void SurfaceManager::moveSurfaceToWorkspace(lomiri::shell::application::MirSurfaceInterface* surface,
                                            const std::shared_ptr<miral::Workspace> &workspace)
{
    if (isRegistered(surface)) {
        WindowManagementPolicy::instance()->moveSurfaceToWorkspace(surface, workspace);
    }
}

void SurfaceManager::moveWorkspaceContentToWorkspace(const std::shared_ptr<miral::Workspace> &to,
                                                     const std::shared_ptr<miral::Workspace> &from)
{
    WindowManagementPolicy::instance()->moveWorkspaceContentToWorkspace(to, from);
}

void SurfaceManager::onStateRequested(MirSurface *surface, Mir::State state)
{
    DEBUG_MSG("("<<surface<<","<<state<<") started");
    Q_EMIT modificationsStarted();
    m_underModification = true;

    surface->setPreviousState(surface->state());
    surface->setState(state);

    if ((state == Mir::MinimizedState || state == Mir::HiddenState) && surface->focused()) {
        Q_ASSERT(m_focusedSurface == surface);
        surface->setFocused(false);
        m_focusedSurface = nullptr;
        focusFirstAvailableSurface();
    }

    m_underModification = false;
    Q_EMIT modificationsEnded();
    DEBUG_MSG("("<<surface<<","<<state<<") ended");
}

void SurfaceManager::onSurfaceDestroyed(MirSurface *surface)
{
    m_surfaces.removeAll(surface);

    if (m_focusedSurface == surface) {
        m_focusedSurface = nullptr;

        Q_EMIT modificationsStarted();
        m_underModification = true;

        focusFirstAvailableSurface();

        m_underModification = false;
        Q_EMIT modificationsEnded();
    }
    Q_EMIT surfaceRemoved(surface);
}

void SurfaceManager::focusFirstAvailableSurface()
{
    MirSurface *chosenSurface = nullptr;
    for (int i = 0; i < m_surfaces.count() && !chosenSurface; ++i) {
        auto *surface = m_surfaces[i];
        if (surface->state() != Mir::HiddenState && surface->state() != Mir::MinimizedState) {
            chosenSurface = surface;
        }
    }

    if (!chosenSurface) {
        return;
    }

    if (m_focusedSurface) {
        m_focusedSurface->setFocused(false);
    }

    chosenSurface->setFocused(true);
    doRaise(chosenSurface);

    m_focusedSurface = chosenSurface;
}

void SurfaceManager::createInputMethodSurface()
{
    if (!m_virtualKeyboard) {
        m_virtualKeyboard = new VirtualKeyboard;
        registerSurface(m_virtualKeyboard);

        WindowManagementPolicy::instance()->addSurface(m_virtualKeyboard);
    }
}

void SurfaceManager::releaseInputMethodSurface()
{
    if (m_virtualKeyboard) {
        m_virtualKeyboard->setLive(false);
        m_virtualKeyboard = nullptr;
    }
}
