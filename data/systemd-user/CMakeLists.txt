pkg_check_modules(SYSTEMD systemd)

if (${SYSTEMD_FOUND})
    find_program(DUAE_BIN dbus-update-activation-environment REQUIRED)
    find_program(XWAYLAND_BIN Xwayland REQUIRED)

    if (${SYSTEMD_VERSION} VERSION_LESS 247)
        pkg_get_variable(SYSTEMD_USER_UNIT_DIR systemd systemduserunitdir)
    else()
        pkg_get_variable(SYSTEMD_USER_UNIT_DIR systemd systemd_user_unit_dir)
    endif()

    # lomiri-<MODE>.service

    set(MODES full-greeter full-shell greeter shell)

    foreach(MODE ${MODES})
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

configure_file(lomiri-systemd-wrapper.in ${CMAKE_CURRENT_BINARY_DIR}/lomiri-systemd-wrapper @ONLY)
install(PROGRAMS
    ${CMAKE_CURRENT_BINARY_DIR}/lomiri-systemd-wrapper
    DESTINATION ${CMAKE_INSTALL_FULL_LIBEXECDIR}
)

# Xwayland startup script

configure_file(Xwayland.lomiri.in ${CMAKE_CURRENT_BINARY_DIR}/Xwayland.lomiri @ONLY)
install(PROGRAMS
    ${CMAKE_CURRENT_BINARY_DIR}/Xwayland.lomiri
    DESTINATION ${CMAKE_INSTALL_FULL_LIBEXECDIR}
)
