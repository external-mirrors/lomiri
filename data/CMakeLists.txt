include(FindGettext)

# generate desktop files
configure_file(${DESKTOP_FILE_SHELL}.in.in ${DESKTOP_FILE_SHELL}.in)
add_custom_target(${DESKTOP_FILE_SHELL} ALL
    COMMENT "Merging translations into ${DESKTOP_FILE_SHELL}..."
    COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
            --desktop --template=${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_SHELL}.in
            -o ${DESKTOP_FILE_SHELL}
            -d ${CMAKE_SOURCE_DIR}/po
)

configure_file(${DESKTOP_FILE_GREETER}.in.in ${DESKTOP_FILE_GREETER}.in)
add_custom_target(${DESKTOP_FILE_GREETER} ALL
    COMMENT "Merging translations into ${DESKTOP_FILE_GREETER}..."
    COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
            --desktop --template=${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_GREETER}.in
            -o ${DESKTOP_FILE_GREETER}
            -d ${CMAKE_SOURCE_DIR}/po
)

configure_file(${DESKTOP_FILE_INDICATORSCLIENT}.in.in ${DESKTOP_FILE_INDICATORSCLIENT}.in)
add_custom_target(${DESKTOP_FILE_INDICATORSCLIENT} ALL
    COMMENT "Merging translations into ${DESKTOP_FILE_INDICATORSCLIENT}..."
    COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
            --desktop --template=${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_INDICATORSCLIENT}.in
            -o ${DESKTOP_FILE_INDICATORSCLIENT}
            -d ${CMAKE_SOURCE_DIR}/po
)

# install desktop files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${SHELL_APP}.desktop
    ${CMAKE_CURRENT_BINARY_DIR}/${INDICATORS_CLIENT_APP}.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${GREETER_APP}.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/lightdm/greeters
    )

install(FILES
    51-lomiri-greeter.conf
    DESTINATION ${CMAKE_INSTALL_DATADIR}/lightdm/lightdm.conf.d
    )

add_custom_target(pkgversion ALL COMMAND echo ${PROJECT_VERSION} | head -n1 > ${CMAKE_CURRENT_BINARY_DIR}/version)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/version DESTINATION ${CMAKE_INSTALL_LOCALSTATEDIR}/lib/lomiri)

add_subdirectory(systemd-user)
