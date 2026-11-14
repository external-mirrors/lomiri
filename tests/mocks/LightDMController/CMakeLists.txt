qt_add_qml_module(lightdmcontrollerplugin
    URI LightDMController
    VERSION 0.1
    PLUGIN_TARGET lightdmcontrollerplugin
    SOURCES
        plugin.cpp
)

target_link_libraries(lightdmcontrollerplugin PRIVATE MockLightDM Qt::Qml)

install_qml_module(lightdmcontrollerplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
