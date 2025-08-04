add_library(Aethercast-qml MODULE
    plugin.cpp
    aethercast_device.cpp
    aethercast_manager.cpp
    displays.cpp
    freedesktop_objectmanager.cpp
    freedesktop_properties.cpp
)

target_link_libraries(Aethercast-qml Qt5::Qml Qt5::DBus)
add_lomiri_plugin(Aethercast 0.1 Aethercast TARGETS Aethercast-qml)
