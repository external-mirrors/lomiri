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

add_library(Aethercast-qml MODULE
    plugin.cpp
    displays.cpp
    ${DBUS_INTERFACE}
    ${FREEDESKTOP_PROPERTIES}
)

target_include_directories(
    Aethercast-qml
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(Aethercast-qml Qt5::Qml Qt5::DBus)
add_lomiri_plugin(Aethercast 0.1 Aethercast TARGETS Aethercast-qml)
