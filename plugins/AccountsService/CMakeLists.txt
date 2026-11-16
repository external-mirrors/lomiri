qt_add_qml_module(accountsserviceplugin
    URI AccountsService
    VERSION 0.1
    PLUGIN_TARGET accountsserviceplugin
    SOURCES
        AccountsService.cpp
        AccountsServiceDBusAdaptor.cpp
        plugin.cpp
)

if(ENABLE_UBUNTU_ACCOUNTSSERVICE)
    target_compile_definitions(accountsserviceplugin PRIVATE ENABLE_UBUNTU_ACCOUNTSSERVICE)
endif()

target_link_libraries(accountsserviceplugin PRIVATE
    lomiri-paths
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

install_qml_module(accountsserviceplugin DESTINATION ${SHELL_INSTALL_QML})

# This is installed in <datadir>/dbus-1/interfaces, but then we also
# need to place a symlink to it in <datadir>/accountsservice/interfaces
set(DBUS_IFACE_FILE com.lomiri.shell.AccountsService.xml)

install(FILES ${DBUS_IFACE_FILE}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/dbus-1/interfaces
)

file(CREATE_LINK ../../dbus-1/interfaces/${DBUS_IFACE_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/${DBUS_IFACE_FILE}
    SYMBOLIC
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${DBUS_IFACE_FILE}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/accountsservice/interfaces
)
