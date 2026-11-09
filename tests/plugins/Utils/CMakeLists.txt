include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/Utils
    ${CMAKE_CURRENT_BINARY_DIR}
    )

foreach(util_test
    QLimitProxyModel
    LomiriSortFilterProxyModel
    WindowInputMonitor
    WindowStateStorage
)
    add_executable(${util_test}TestExec ${util_test}Test.cpp ModelTest.cpp)
    target_link_libraries(${util_test}TestExec PRIVATE
        lomiri-shell-application
        Utils-qml
        Qt::Core
        Qt::Qml
        Qt::Test
    )
    install(TARGETS ${util_test}TestExec
        DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Utils"
    )
    add_lomiri_unittest(${util_test} ${util_test}TestExec ADD_TEST
        ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/plugins/Utils
    )

endforeach()

# plain qml test
add_lomiri_qmlunittest(. UtilsStyle)

# URLDispatcher test needs dbus-test-runner because it claims a dbus name
add_executable(URLDispatcherTestExec URLDispatcherTest.cpp)
target_link_libraries(URLDispatcherTestExec PRIVATE Qt::Test Qt::Core Qt::DBus Qt::Qml Utils-qml)
install(TARGETS URLDispatcherTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Utils"
)
add_lomiri_unittest(URLDispatcher dbus-test-runner
    ARG_PREFIX "--parameter"
    ARGS --task $<TARGET_FILE:URLDispatcherTestExec>
    ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/plugins/Utils
)
