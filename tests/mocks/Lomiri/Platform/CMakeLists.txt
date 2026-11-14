qt_add_qml_module(mockplatformplugin
    URI Lomiri.Platform
    VERSION 1.0
    PLUGIN_TARGET mockplatformplugin
    QML_FILES
        MockPlatform.qml
)

install_qml_module(mockplatformplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
