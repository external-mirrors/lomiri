add_executable(lomiri-mock-indicator-service
    mock-indicator-service.c
)

target_link_libraries(lomiri-mock-indicator-service PRIVATE PkgConfig::GIO)

install(TARGETS lomiri-mock-indicator-service
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
