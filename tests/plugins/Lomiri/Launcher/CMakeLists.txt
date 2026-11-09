include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher
    ${liblomiri-private_SOURCE_DIR}
    )

add_definitions(-DSM_BUSNAME=sessionBus)
add_definitions(-DTEST_DIR="plugins/Lomiri/Launcher")

### LauncherModelTest
add_executable(launchermodeltestExec
    launchermodeltest.cpp
    gsettings.cpp
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/launchermodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/asadapter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/launcheritem.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/quicklistmodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/dbusinterface.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/quicklistentry.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/ualwrapper.cpp
    )

target_link_libraries(launchermodeltestExec PRIVATE
    lomiri-private
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GLIB
    PkgConfig::GSETTINGS_QT
    PkgConfig::LAL
    Qt::Core
    Qt::DBus
    Qt::Gui
    Qt::Qml
    Qt::Test
    Qt::Xml
)

add_dependencies(launchermodeltestExec mock-server)
install(TARGETS launchermodeltestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Lomiri/Launcher"
    )

add_lomiri_unittest(LauncherModel dbus-test-runner
    ENVIRONMENT "APPDIR=${CMAKE_CURRENT_BINARY_DIR}/applications"
    ARG_PREFIX "--parameter"
    ARGS
        --task $<TARGET_FILE:mock-server>
        --ignore-return
        --task $<TARGET_FILE:launchermodeltestExec>
        --wait-for org.freedesktop.Accounts
)

### AppDrawerModelTest
add_executable(appdrawermodeltestExec
    appdrawermodeltest.cpp
    ualwrapper.cpp
    xdgwatcher.cpp
    iconcachewatcher.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/appdrawermodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/launcheritem.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/quicklistmodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/quicklistentry.cpp
    )

target_link_libraries(appdrawermodeltestExec PRIVATE
    lomiri-private
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GLIB
    PkgConfig::GSETTINGS_QT
    PkgConfig::LAL
    Qt::Concurrent
    Qt::Core
    Qt::DBus
    Qt::Gui
    Qt::Qml
    Qt::Test
    Qt::Xml
)

add_dependencies(appdrawermodeltestExec mock-server)
install(TARGETS appdrawermodeltestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Lomiri/Launcher"
    )

add_lomiri_unittest(AppDrawerModel dbus-test-runner
    ENVIRONMENT "APPDIR=${CMAKE_CURRENT_BINARY_DIR}/applications"
    ARG_PREFIX "--parameter"
    ARGS
        --task $<TARGET_FILE:mock-server>
        --ignore-return
        --task $<TARGET_FILE:appdrawermodeltestExec>
        --wait-for org.freedesktop.Accounts
)

# copy sample application files into build directory for shadow builds
file(COPY applications
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
install(DIRECTORY applications
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Lomiri/Launcher"
    )
