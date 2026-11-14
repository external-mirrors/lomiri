qt_add_qml_module(mockuinputplugin
    URI UInput
    VERSION 0.1
    PLUGIN_TARGET mockuinputplugin
    SOURCES
        mockuinput.cpp
        plugin.cpp
)

target_link_libraries(mockuinputplugin PRIVATE Qt::Qml)

install_qml_module(mockuinputplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
