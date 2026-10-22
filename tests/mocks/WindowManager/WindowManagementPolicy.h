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

#ifndef MOCKWINDOMANAGEMENTPOLICY_H
#define MOCKWINDOMANAGEMENTPOLICY_H

#include "wmpolicyinterface.h"

#include <QObject>
#include <QMultiMap>
#include <QVector>

#include <memory>
#include <unordered_set>

namespace miral { class Workspace {}; }
namespace lomiri::shell::application { class MirSurfaceInterface; }

// A Fake window management policy for the mock.
class Q_DECL_EXPORT WindowManagementPolicy : public QObject,
                                             public WMPolicyInterface
{
    Q_OBJECT
public:
    typedef lomiri::shell::application::MirSurfaceInterface Surface;

    WindowManagementPolicy();

    // for use in mocks
    static WindowManagementPolicy *instance();

    // From WMPolicyInterface
    std::shared_ptr<miral::Workspace> createWorkspace() override;
    void releaseWorkspace(const std::shared_ptr<miral::Workspace> &workspace) override;
    void setActiveWorkspace(const std::shared_ptr<miral::Workspace> &workspace) override;

    void addSurface(Surface *surface);
    void removeSurface(Surface *surface);

    void forEachSurfaceInWorkspace(std::shared_ptr<miral::Workspace> const &workspace,
                                   std::function<void(Surface*)> const &callback);

    void moveSurfaceToWorkspace(Surface *surface, const std::shared_ptr<miral::Workspace> &workspace);

    void moveWorkspaceContentToWorkspace(const std::shared_ptr<miral::Workspace> &to,
                                         const std::shared_ptr<miral::Workspace> &from);

Q_SIGNALS:
    void surfaceAdded(Surface *surface);
    void surfaceRemoved(Surface *surface);
    void surfacesAddedToWorkspace(const std::shared_ptr<miral::Workspace> &workspace, const QVector<Surface*> &surfaces);
    void surfacesAboutToBeRemovedFromWorkspace(const std::shared_ptr<miral::Workspace> &workspace, const QVector<Surface*> &surfaces);

private:
    std::weak_ptr<miral::Workspace> m_activeWorkspace;
    std::shared_ptr<miral::Workspace> m_dummyWorkspace;
    std::unordered_set<std::shared_ptr<miral::Workspace>> m_workspaces;

    // Pointers are automatically removed when destroyed (see SurfaceManager::registerSurface)
    typedef QMultiMap<std::shared_ptr<miral::Workspace>, Surface*> WorkspaceSurfaces;
    WorkspaceSurfaces m_surfaces;
};
#endif // LOMIRI_WINDOWMANAGEMENTPOLICY_H
