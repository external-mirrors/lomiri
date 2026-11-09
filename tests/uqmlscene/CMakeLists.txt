add_executable(uqmlscene
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/DebuggingController.cpp
    )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${liblomiri-private_SOURCE_DIR}
)

target_link_libraries(uqmlscene PRIVATE
    lomiri-private
    PkgConfig::LOMIRIGESTURES
    Qt::DBus
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
    Qt::Test
)

install(TARGETS uqmlscene
    RUNTIME DESTINATION ${SHELL_PRIVATE_FULL_LIBEXECDIR}
    )
