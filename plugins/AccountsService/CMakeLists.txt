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

set(DBUS_IFACE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/dbus-1/interfaces")
set(ACCOUNTS_IFACE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/accountsservice/interfaces")

install(FILES com.lomiri.shell.AccountsService.xml
        DESTINATION "${DBUS_IFACE_DIR}"
    )

# Create accountsservice symlink for above dbus interface
install(CODE "
execute_process(COMMAND mkdir -p \"\$ENV{DESTDIR}${ACCOUNTS_IFACE_DIR}\")
execute_process(COMMAND ln -sf ../../dbus-1/interfaces/com.lomiri.shell.AccountsService.xml \"\$ENV{DESTDIR}${ACCOUNTS_IFACE_DIR}\")
    ")
