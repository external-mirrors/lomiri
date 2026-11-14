qt_add_qml_module(mocklanguageplugin
    URI Lomiri.SystemSettings.LanguagePlugin
    VERSION 1.0
    PLUGIN_TARGET mocklanguageplugin
    QML_FILES
        MockKeyboardPlugin.qml
        MockLanguagePlugin.qml
)

install_qml_module(mocklanguageplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
