qt_add_qml_module(powerdplugin
    URI Powerd
    VERSION 0.1
    PLUGIN_TARGET powerdplugin
    SOURCES
        plugin.cpp
        Powerd.cpp
)

target_link_libraries(powerdplugin PRIVATE
    PkgConfig::GIO
    Qt::DBus
    Qt::Qml
)

install_qml_module(powerdplugin DESTINATION ${SHELL_INSTALL_QML})
