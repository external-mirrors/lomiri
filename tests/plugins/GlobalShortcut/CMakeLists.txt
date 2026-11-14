add_executable(GlobalShortcutTestExec GlobalShortcutTest.cpp)

target_compile_definitions(GlobalShortcutTestExec PRIVATE TEST_DIR="plugins/GlobalShortcut")

target_link_libraries(GlobalShortcutTestExec PRIVATE
    globalshortcutplugin
    lomiri-paths
    Qt::Test
    Qt::Quick
)

install(TARGETS GlobalShortcutTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/GlobalShortcut"
)
install(FILES shortcut.qml
    DESTINATION "${SHELL_APP_FULL_DIR}/tests/plugins/GlobalShortcut"
)
add_lomiri_uitest(GlobalShortcut GlobalShortcutTestExec
        DEPENDS globalshortcutplugin
        ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/plugins/GlobalShortcut
)
