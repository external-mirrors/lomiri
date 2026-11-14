qt_add_qml_module(mockhfdplugin
    URI Hfd
    VERSION 0.1
    PLUGIN_TARGET mockhfdplugin
    SOURCES
        Leds.cpp
        plugin.cpp
)

target_link_libraries(mockhfdplugin PRIVATE Qt::Gui Qt::Qml)

install_qml_module(mockhfdplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
