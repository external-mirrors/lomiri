qt_add_dbus_adaptor(generated_srcs
    com.lomiri.MenuRegistrar.xml
    dbusapplicationmenuregistry.h
    DBusApplicationMenuRegistry
)

qt_add_qml_module(applicationmenuplugin
    URI Lomiri.ApplicationMenu
    VERSION 0.1
    PLUGIN_TARGET applicationmenuplugin
    SOURCES
        applicationmenuregistry.cpp
        dbusapplicationmenuregistry.cpp
        plugin.cpp
        ${generated_srcs}
)

target_include_directories(applicationmenuplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(applicationmenuplugin PRIVATE Qt::DBus Qt::Qml)

install_qml_module(applicationmenuplugin DESTINATION ${SHELL_INSTALL_QML})
