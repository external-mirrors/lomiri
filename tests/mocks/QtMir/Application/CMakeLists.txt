qt_add_qml_module(mockqtmirapplicationplugin
    URI QtMir.Application
    VERSION 0.1
    PLUGIN_TARGET mockqtmirapplicationplugin
    SOURCES
        ApplicationInfo.cpp
        ApplicationManager.cpp
        MirMock.cpp
        MirSurface.cpp
        MirSurfaceItem.cpp
        MirSurfaceListModel.cpp
        ObjectListModel.h
        plugin.cpp
        SurfaceManager.cpp
        VirtualKeyboard.cpp
        resources/surfaces.qrc
)

target_link_libraries(mockqtmirapplicationplugin PRIVATE
    lomiri-paths
    lomiri-shell-application
    mockwindowmanagmentpolicy
    PkgConfig::MIRAL
    Qt::Core
    Qt::DBus
    Qt::Quick
)

install_qml_module(mockqtmirapplicationplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
