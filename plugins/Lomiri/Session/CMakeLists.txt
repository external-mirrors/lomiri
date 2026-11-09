include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${liblomiri-private_SOURCE_DIR}
)

add_definitions(-DSM_BUSNAME=systemBus)

set(QMLSESSIONPLUGIN_SRC
    plugin.cpp
    dbuslomirisessionservice.cpp
    orientationlock.cpp
    )

add_library(LomiriSession-qml MODULE
    ${QMLSESSIONPLUGIN_SRC}
    )

target_link_libraries(LomiriSession-qml PRIVATE
    lomiri-private
    PkgConfig::GIO
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

# export the qmldir and qmltypes files
add_lomiri_plugin(Lomiri.Session 0.1 Lomiri/Session TARGETS LomiriSession-qml)
