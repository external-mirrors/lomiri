qt_add_qml_module(processcontrolplugin
    URI ProcessControl
    VERSION 0.1
    PLUGIN_TARGET processcontrolplugin
    SOURCES
        LocationWatcher.cpp
        plugin.cpp
        ProcessControl.cpp
)

target_link_libraries(processcontrolplugin PRIVATE Qt::DBus Qt::Qml)

target_include_directories(processcontrolplugin PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

install_qml_module(processcontrolplugin DESTINATION ${SHELL_INSTALL_QML})

set(DBUS_IFACE_DIR "${CMAKE_INSTALL_DATADIR}/dbus-1/interfaces")

install(FILES com.lomiri.ProcessControl.xml
    DESTINATION "${DBUS_IFACE_DIR}"
)
