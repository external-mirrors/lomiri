set(QMLLAUNCHERPLUGINAS_SRC
    plugin.cpp
    launchermodelas.cpp
    launcheritem.cpp
    quicklistmodel.cpp
    quicklistentry.cpp
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    )

add_library(LomiriLauncherAS-qml MODULE
    ${QMLLAUNCHERPLUGINAS_SRC}
    )

target_include_directories(LomiriLauncherAS-qml PRIVATE ${CMAKE_SOURCE_DIR}/plugins/AccountsService)

target_link_libraries(LomiriLauncherAS-qml PRIVATE
    lomiri-private
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GSETTINGS_QT
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

add_lomiri_greeter_plugin(Lomiri.Launcher 0.1 Lomiri/Launcher TARGETS LomiriLauncherAS-qml)
