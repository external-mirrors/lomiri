add_definitions(-DTEST_DIR="plugins/Greeter/Lomiri/Launcher")

### LauncherModelASTest
add_executable(launchermodelastestExec
    launchermodelastest.cpp
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Greeter/Lomiri/Launcher/launchermodelas.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Greeter/Lomiri/Launcher/launcheritem.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Greeter/Lomiri/Launcher/quicklistmodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Greeter/Lomiri/Launcher/quicklistentry.cpp
    )

target_include_directories(launchermodelastestExec PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService
    ${CMAKE_SOURCE_DIR}/plugins/Greeter/Lomiri/Launcher
)

target_link_libraries(launchermodelastestExec PRIVATE
    lomiri-paths
    lomiri-private
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GSETTINGS_QT
    Qt::Core
    Qt::DBus
    Qt::Gui
    Qt::Qml
    Qt::Test
)

add_dependencies(launchermodelastestExec mock-server)
install(TARGETS launchermodelastestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Greeter/Lomiri/Launcher"
)
add_lomiri_unittest(LauncherModelAS dbus-test-runner
    ARG_PREFIX "--parameter"
    ARGS
        --bus-type both
        --task $<TARGET_FILE:mock-server>
        --ignore-return
        --task $<TARGET_FILE:launchermodelastestExec>
        --wait-for org.freedesktop.Accounts
)
