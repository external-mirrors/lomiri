qt_add_qml_module(mockconnectivityplugin
    URI Lomiri.Connectivity
    VERSION 1.0
    PLUGIN_TARGET mockconnectivityplugin
    SOURCES
        networking-status.cpp
        plugin.cpp
)

target_link_libraries(mockconnectivityplugin PRIVATE Qt::Qml)

install_qml_module(mockconnectivityplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
