qt_add_qml_module(mockpowerdplugin
    URI Powerd
    VERSION 0.1
    PLUGIN_TARGET mockpowerdplugin
    SOURCES
        plugin.cpp
        Powerd.cpp
)

target_link_libraries(mockpowerdplugin PRIVATE Qt::Qml)

install_qml_module(mockpowerdplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
