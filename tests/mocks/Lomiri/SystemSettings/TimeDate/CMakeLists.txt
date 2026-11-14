qt_add_qml_module(mocktimedateplugin
    URI Lomiri.SystemSettings.TimeDate
    VERSION 1.1
    PLUGIN_TARGET mocktimedateplugin
    QML_FILES
        MockTimeDate.qml
)

install_qml_module(mocktimedateplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
