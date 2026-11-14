qt_add_qml_module(platformplugin
    URI Lomiri.Platform
    VERSION 1.0
    PLUGIN_TARGET platformplugin
    SOURCES
        platform.cpp
        plugin.cpp
)

target_link_libraries(platformplugin PRIVATE Qt::DBus Qt::Qml)

install_qml_module(platformplugin DESTINATION ${SHELL_INSTALL_QML})
