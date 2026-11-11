add_library(SessionBroadcast-qml MODULE
    SessionBroadcast.cpp
    plugin.cpp
    )

target_link_libraries(SessionBroadcast-qml PRIVATE
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

add_lomiri_plugin(SessionBroadcast 0.1 SessionBroadcast TARGETS SessionBroadcast-qml)
