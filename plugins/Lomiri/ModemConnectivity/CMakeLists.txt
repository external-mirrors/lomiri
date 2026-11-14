qt_add_qml_module(modemconnectivityplugin
    URI Lomiri.ModemConnectivity
    VERSION 0.1
    PLUGIN_TARGET modemconnectivityplugin
    SOURCES
        ModemConnectivity.cpp
        plugin.cpp
)

target_link_libraries(modemconnectivityplugin PRIVATE Qt::Core Qt::DBus Qt::Qml)

install_qml_module(modemconnectivityplugin DESTINATION ${SHELL_INSTALL_QML})
