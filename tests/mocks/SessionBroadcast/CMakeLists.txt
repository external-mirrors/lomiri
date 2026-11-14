qt_add_qml_module(mocksessionbroadcastplugin
    URI SessionBroadcast
    VERSION 0.1
    PLUGIN_TARGET mocksessionbroadcastplugin
    SOURCES
        plugin.cpp
        SessionBroadcast.cpp
)

target_link_libraries(mocksessionbroadcastplugin PRIVATE Qt::Qml)

install_qml_module(mocksessionbroadcastplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
