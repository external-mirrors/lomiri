qt_add_qml_module(mocktelephonyplugin
    URI Lomiri.Telephony
    VERSION 0.1
    PLUGIN_TARGET mocktelephonyplugin
    SOURCES
        ContactWatcherData.cpp
        MockCallEntry.cpp
        MockCallManager.cpp
        MockContactWatcher.cpp
        MockTelepathyHelper.cpp
        plugin.cpp
)

target_link_libraries(mocktelephonyplugin PRIVATE Qt::Core Qt::Quick)

install_qml_module(mocktelephonyplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
