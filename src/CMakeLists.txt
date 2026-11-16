add_subdirectory(liblomiri-private)

add_executable(${SHELL_APP}
    ApplicationArguments.cpp
    main.cpp
    CachingNetworkManagerFactory.cpp
    DisplayConfigurationStorage.cpp
    LomiriApplication.cpp
    LomiriCommandLineParser.cpp
    UnixSignalHandler.cpp
    DebuggingController.cpp
    WindowManagementPolicy.cpp
)

target_link_libraries(${SHELL_APP} PRIVATE
    lomiri-paths
    lomiri-private
    Intl::Intl
    PkgConfig::APPLICATION_API
    PkgConfig::CONNECTIVITY
    PkgConfig::DEVICEINFO
    PkgConfig::GSETTINGS_QT
    PkgConfig::LIBSYSTEMD
    PkgConfig::LOMIRIGESTURES
    PkgConfig::QTMIRSERVER
    Qt::DBus
    Qt::Gui
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
    Qt::Test
)

if (WITH_MIR2)
    target_link_libraries(${SHELL_APP} PRIVATE PkgConfig::MIROIL)
endif()

install(TARGETS ${SHELL_APP} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
