add_executable(TopLevelWindowModelTestExec
    tst_TopLevelWindowModel.cpp
    QtMirApplicationMocks.h

    ${CMAKE_SOURCE_DIR}/tests/mocks/QtMir/Application/MirSurfaceListModel.cpp

    )

target_include_directories(TopLevelWindowModelTestExec PRIVATE ${CMAKE_SOURCE_DIR}/tests/mocks)

target_link_libraries(TopLevelWindowModelTestExec PRIVATE
    lomiri-private
    lomiri-shell-application
    windowmanager
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::Test
)

install(TARGETS TopLevelWindowModelTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/WindowManager"
)

add_lomiri_unittest(TopLevelWindowModel TopLevelWindowModelTestExec)
