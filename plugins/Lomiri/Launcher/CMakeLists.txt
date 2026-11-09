add_definitions(-DSM_BUSNAME=systemBus)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService
    ${liblomiri-private_SOURCE_DIR}
)

set(QMLLAUNCHERPLUGIN_SRC
    plugin.cpp
    launchermodel.cpp
    launcheritem.cpp
    quicklistmodel.cpp
    quicklistentry.cpp
    dbusinterface.cpp
    gsettings.cpp
    asadapter.cpp
    appdrawermodel.cpp
    ualwrapper.cpp
    xdgwatcher.cpp
    iconcachewatcher.cpp
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    )

add_library(LomiriLauncher-qml MODULE
    ${QMLLAUNCHERPLUGIN_SRC}
    )

target_link_libraries(LomiriLauncher-qml PRIVATE
    lomiri-private
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GIO
    PkgConfig::GLIB
    PkgConfig::GSETTINGS_QT
    PkgConfig::LAL
    Qt::Concurrent
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

add_lomiri_plugin(Lomiri.Launcher 0.1 Lomiri/Launcher TARGETS LomiriLauncher-qml)
