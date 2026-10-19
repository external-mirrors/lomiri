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

#include "WindowManagementPolicy.h"

#include <QDebug>

WindowManagementPolicy::WindowManagementPolicy()
    : m_dummyWorkspace(std::shared_ptr<miral::Workspace>())
{
    wmPolicyInterface = this;
    m_activeWorkspace = m_dummyWorkspace;
}

WindowManagementPolicy *WindowManagementPolicy::instance()
{
    static WindowManagementPolicy* wmPolicy(new WindowManagementPolicy);
    return wmPolicy;
}

std::shared_ptr<miral::Workspace> WindowManagementPolicy::createWorkspace()
{
    auto workspace = std::make_shared<miral::Workspace>();
    m_workspaces.insert(workspace);

    if (m_activeWorkspace.lock() == m_dummyWorkspace) {
        moveWorkspaceContentToWorkspace(workspace, m_dummyWorkspace);
        m_activeWorkspace = workspace;
    }
    return workspace;
}

void WindowManagementPolicy::releaseWorkspace(const std::shared_ptr<miral::Workspace> &workspace)
{
    auto iter = m_workspaces.find(workspace);
    if (iter != m_workspaces.end()) m_workspaces.erase(iter);

    if (m_workspaces.size() == 0) {
        m_activeWorkspace = m_dummyWorkspace;
        moveWorkspaceContentToWorkspace(m_dummyWorkspace, workspace);
    }
}

void WindowManagementPolicy::setActiveWorkspace(const std::shared_ptr<miral::Workspace> &workspace)
{
    if (m_activeWorkspace.lock() == workspace)
        return;
    m_activeWorkspace = workspace ? workspace : m_dummyWorkspace;
}

void WindowManagementPolicy::addSurface(Surface *surface)
{
    Q_EMIT surfaceAdded(surface);

    auto activeWorkspace = m_activeWorkspace.lock();
    if (activeWorkspace) {
        m_surfaces.insert(activeWorkspace, surface);

        Q_EMIT surfacesAddedToWorkspace(activeWorkspace, {surface});
    }
}

void WindowManagementPolicy::removeSurface(Surface *surface)
{
    WorkspaceSurfaces::iterator i = m_surfaces.begin();
    while (i != m_surfaces.end()) {
        if (i.value() == surface) {
            Q_EMIT surfacesAboutToBeRemovedFromWorkspace(i.key(), { surface });
            i = m_surfaces.erase(i);
        } else {
            ++i;
        }
    }
    Q_EMIT surfaceRemoved(surface);
}

void WindowManagementPolicy::forEachSurfaceInWorkspace(const std::shared_ptr<miral::Workspace> &workspace, const std::function<void(Surface*)> &callback)
{
    WorkspaceSurfaces::iterator i = m_surfaces.find(workspace);
    while (i != m_surfaces.end() && i.key() == workspace) {
        callback(i.value());
        ++i;
    }
}

void WindowManagementPolicy::moveSurfaceToWorkspace(Surface *surface, const std::shared_ptr<miral::Workspace> &workspace)
{
    auto from = m_surfaces.key(surface);
    if (from) {
        auto iter = m_surfaces.find(from, surface);
        Q_EMIT surfacesAboutToBeRemovedFromWorkspace(from, { surface });
        m_surfaces.erase(iter);
    }

    m_surfaces.insert(workspace, surface);
    Q_EMIT surfacesAddedToWorkspace(workspace, { surface });
}

void WindowManagementPolicy::moveWorkspaceContentToWorkspace(const std::shared_ptr<miral::Workspace> &to, const std::shared_ptr<miral::Workspace> &from)
{
    QVector<Surface*> surfaces;

    WorkspaceSurfaces::iterator i = m_surfaces.find(from);
    while (i != m_surfaces.end() && i.key() == from) {
        surfaces.push_back(i.value());
        ++i;
    }
    Q_EMIT surfacesAboutToBeRemovedFromWorkspace(from, surfaces);
    m_surfaces.remove(from);

    Q_FOREACH(Surface *surface, surfaces) {
        m_surfaces.insert(to, surface);
    }
    Q_EMIT surfacesAddedToWorkspace(to, surfaces);
}
