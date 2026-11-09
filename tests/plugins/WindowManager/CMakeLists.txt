include_directories(
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/tests/mocks
    ${liblomiri-private_SOURCE_DIR}
    )

add_executable(TopLevelWindowModelTestExec
    tst_TopLevelWindowModel.cpp
    QtMirApplicationMocks.h

    ${CMAKE_SOURCE_DIR}/tests/mocks/QtMir/Application/MirSurfaceListModel.cpp

    )

target_link_libraries(TopLevelWindowModelTestExec PRIVATE
    lomiri-private
    lomiri-shell-application
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::Test
    windowmanager-qml
)

install(TARGETS TopLevelWindowModelTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/WindowManager"
)

# To find libwindowmanager-qml.so
set_target_properties(TopLevelWindowModelTestExec PROPERTIES
        INSTALL_RPATH "${SHELL_PRIVATE_FULL_LIBDIR}")

add_lomiri_unittest(TopLevelWindowModel TopLevelWindowModelTestExec
    ENVIRONMENT LD_LIBRARY_PATH=${LOMIRI_PLUGINPATH}/WindowManager
)
