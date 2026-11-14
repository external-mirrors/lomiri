qt_add_qml_module(greeterlauncherplugin
    URI Lomiri.Launcher
    VERSION 0.1
    PLUGIN_TARGET greeterlauncherplugin
    SOURCES
        launcheritem.cpp
        launchermodelas.cpp
        plugin.cpp
        quicklistentry.cpp
        quicklistmodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
)

target_include_directories(greeterlauncherplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/AccountsService)

target_link_libraries(greeterlauncherplugin PRIVATE
    lomiri-private
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GSETTINGS_QT
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

install_qml_module(greeterlauncherplugin DESTINATION ${SHELL_INSTALL_QML}/Greeter)
