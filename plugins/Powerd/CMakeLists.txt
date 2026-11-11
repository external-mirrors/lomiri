add_library(Powerd-qml MODULE
    plugin.cpp
    Powerd.cpp
    )

target_link_libraries(Powerd-qml PRIVATE
    PkgConfig::GIO
    Qt::DBus
    Qt::Qml
)

add_lomiri_plugin(Powerd 0.1 Powerd TARGETS Powerd-qml)
