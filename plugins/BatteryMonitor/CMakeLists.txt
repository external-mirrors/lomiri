qt_add_qml_module(batterymonitorplugin
    URI BatteryMonitor
    VERSION 1.0
    PLUGIN_TARGET batterymonitorplugin
    SOURCES
        BatteryMonitor.cpp
        plugin.cpp
)

target_link_libraries(batterymonitorplugin PRIVATE Qt::DBus Qt::Qml)

install_qml_module(batterymonitorplugin DESTINATION ${SHELL_INSTALL_QML})
