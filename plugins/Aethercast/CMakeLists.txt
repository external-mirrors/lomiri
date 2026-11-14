qt_add_dbus_interface(
    DBUS_INTERFACE
    org.aethercast.xml
    org_aethercast
)

qt_add_dbus_interface(
    FREEDESKTOP_PROPERTIES
    org.freedesktop.DBus.Properties.xml
    freedesktop_properties
)

qt_add_qml_module(aethercastplugin
    URI Aethercast
    VERSION 1.0
    PLUGIN_TARGET aethercastplugin
    SOURCES
        displays.cpp
        plugin.cpp
        ${DBUS_INTERFACE}
        ${FREEDESKTOP_PROPERTIES}
)

target_include_directories(aethercastplugin PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(aethercastplugin PRIVATE Qt::Qml Qt::DBus)

install_qml_module(aethercastplugin DESTINATION ${SHELL_INSTALL_QML})
