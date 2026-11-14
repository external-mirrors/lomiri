qt_add_qml_module(launcherplugin
    URI Lomiri.Launcher
    VERSION 0.1
    PLUGIN_TARGET launcherplugin
    SOURCES
        appdrawermodel.cpp
        asadapter.cpp
        dbusinterface.cpp
        gsettings.cpp
        iconcachewatcher.cpp
        launcheritem.cpp
        launchermodel.cpp
        plugin.cpp
        quicklistentry.cpp
        quicklistmodel.cpp
        ualwrapper.cpp
        xdgwatcher.cpp
        ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
)

target_include_directories(launcherplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/AccountsService)

target_link_libraries(launcherplugin PRIVATE
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

install_qml_module(launcherplugin DESTINATION ${SHELL_INSTALL_QML})
