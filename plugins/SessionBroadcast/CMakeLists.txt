qt_add_qml_module(sessionbroadcastplugin
    URI SessionBroadcast
    VERSION 0.1
    PLUGIN_TARGET sessionbroadcastplugin
    SOURCES
        plugin.cpp
        SessionBroadcast.cpp
)

target_link_libraries(sessionbroadcastplugin PRIVATE
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

install_qml_module(sessionbroadcastplugin DESTINATION ${SHELL_INSTALL_QML})
