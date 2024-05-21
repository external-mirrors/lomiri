pkg_check_modules(SYSTEMD systemd)

if (${SYSTEMD_FOUND})

    if (${SYSTEMD_VERSION} VERSION_LESS 247)
        pkg_get_variable(SYSTEMD_USER_UNIT_DIR systemd systemduserunitdir)
    else()
        pkg_get_variable(SYSTEMD_USER_UNIT_DIR systemd systemd_user_unit_dir)
    endif()

    # lomiri-<MODE>.service

    set(MODES full-greeter full-shell greeter shell)

    foreach(MODE ${MODES})
        set(CONFLICT_UNITS "")
        foreach(OTHER_MODE ${MODES})
            if(NOT ${OTHER_MODE} STREQUAL ${MODE})
                set(CONFLICT_UNITS "${CONFLICT_UNITS} lomiri-${OTHER_MODE}.service")
            endif()
        endforeach()
        string(STRIP "${CONFLICT_UNITS}" CONFLICT_UNITS)

        configure_file(
            lomiri-MODE.service.in
            ${CMAKE_CURRENT_BINARY_DIR}/lomiri-${MODE}.service
            @ONLY
        )

        install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/lomiri-${MODE}.service
            DESTINATION ${SYSTEMD_USER_UNIT_DIR}
        )
    endforeach()

    # lomiri-indicators.target

    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/lomiri-indicators.target" DESTINATION "${SYSTEMD_USER_UNIT_DIR}")

endif()

# lomiri-systemd-wrapper

install(PROGRAMS
    lomiri-systemd-wrapper
    DESTINATION ${CMAKE_INSTALL_FULL_LIBEXECDIR}
)

# Xwayland startup script

install(PROGRAMS
    Xwayland.lomiri
    DESTINATION ${CMAKE_INSTALL_FULL_LIBEXECDIR}
)
