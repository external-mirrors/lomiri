add_executable(GlobalShortcutTestExec GlobalShortcutTest.cpp ${CMAKE_SOURCE_DIR}/plugins/GlobalShortcut/globalshortcut.cpp)

target_include_directories(GlobalShortcutTestExec PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins/GlobalShortcut
)

target_compile_definitions(GlobalShortcutTestExec PRIVATE TEST_DIR="plugins/GlobalShortcut")

target_link_libraries(GlobalShortcutTestExec PRIVATE
    lomiri-paths
    Qt::Test
    Qt::Quick
    GlobalShortcut-qml
)

install(TARGETS GlobalShortcutTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/GlobalShortcut"
)
install(FILES shortcut.qml
    DESTINATION "${SHELL_APP_FULL_DIR}/tests/plugins/GlobalShortcut"
)
add_lomiri_uitest(GlobalShortcut GlobalShortcutTestExec
        DEPENDS GlobalShortcut-qml
        ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/plugins/GlobalShortcut
)
