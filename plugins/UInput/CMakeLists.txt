qt_add_qml_module(uinputplugin
    URI UInput
    VERSION 0.1
    PLUGIN_TARGET uinputplugin
    SOURCES
        plugin.cpp
        uinput.cpp
)

target_link_libraries(uinputplugin PRIVATE Qt::Qml)

install_qml_module(uinputplugin DESTINATION ${SHELL_INSTALL_QML})
