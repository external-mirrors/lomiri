add_executable(uqmlscene
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/DebuggingController.cpp
)

target_include_directories(uqmlscene PRIVATE
    ${CMAKE_SOURCE_DIR}/src
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
