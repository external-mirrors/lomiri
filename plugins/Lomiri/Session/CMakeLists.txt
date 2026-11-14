qt_add_qml_module(sessionplugin
    URI Lomiri.Session
    VERSION 0.1
    PLUGIN_TARGET sessionplugin
    SOURCES
        dbuslomirisessionservice.cpp
        orientationlock.cpp
        plugin.cpp
)

target_link_libraries(sessionplugin PRIVATE
    lomiri-private
    PkgConfig::GIO
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

install_qml_module(sessionplugin DESTINATION ${SHELL_INSTALL_QML})
