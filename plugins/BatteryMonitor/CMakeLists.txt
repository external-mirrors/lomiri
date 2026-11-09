set(SRC
    plugin.cpp
    BatteryMonitor.cpp
)

add_library(BatteryMonitor MODULE ${SRC})

target_link_libraries(BatteryMonitor PRIVATE Qt::DBus Qt::Qml)

add_lomiri_plugin(BatteryMonitor 1.0 BatteryMonitor TARGETS BatteryMonitor)
