qt_add_qml_module(mockupdateplugin
    URI Lomiri.SystemSettings.Update
    VERSION 1.0
    PLUGIN_TARGET mockupdateplugin
    QML_FILES
        MockSystemImage.qml
)

install_qml_module(mockupdateplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
