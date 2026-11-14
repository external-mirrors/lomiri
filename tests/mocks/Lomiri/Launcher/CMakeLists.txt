qt_add_qml_module(mocklauncherplugin
    URI Lomiri.Launcher
    VERSION 0.1
    PLUGIN_TARGET mocklauncherplugin
    SOURCES
        MockAppDrawerModel.cpp
        MockLauncherItem.cpp
        MockLauncherModel.cpp
        MockQuickListModel.cpp
        plugin.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/applicationsfiltermodel.cpp
)

target_include_directories(mocklauncherplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher)

target_link_libraries(mocklauncherplugin PRIVATE
    lomiri-paths
    lomiri-shell-application
    lomiri-shell-launcher
    Qt::Core
    Qt::Quick
)

install_qml_module(mocklauncherplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
