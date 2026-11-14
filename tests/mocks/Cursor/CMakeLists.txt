qt_add_qml_module(mockcursorplugin
    URI Cursor
    VERSION 1.1
    PLUGIN_TARGET mockcursorplugin
    QML_FILES
        Cursor.qml
)

install_qml_module(mockcursorplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
