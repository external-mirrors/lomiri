qt_add_qml_module(mockmodemconnectivityplugin
    URI Lomiri.ModemConnectivity
    VERSION 0.1
    PLUGIN_TARGET mockmodemconnectivityplugin
    SOURCES
        MockModemConnectivity.cpp
        plugin.cpp
)

target_link_libraries(mockmodemconnectivityplugin PRIVATE
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(mockmodemconnectivityplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
