qt_add_qml_module(mockcontentplugin
    URI Lomiri.Content
    VERSION 1.1
    PLUGIN_TARGET mockcontentplugin
    QML_FILES
        ContentHandler.qml
        ContentItem.qml
        ContentPeerPicker.qml
        ContentTransfer.qml
        ContentType.qml
)

install_qml_module(mockcontentplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
