foreach(util_test
    QLimitProxyModel
    LomiriSortFilterProxyModel
    WindowInputMonitor
    WindowStateStorage
)
    add_executable(${util_test}TestExec ${util_test}Test.cpp ModelTest.cpp)
    target_link_libraries(${util_test}TestExec PRIVATE
        lomiri-shell-application
        lomiriutils
        Qt::Core
        Qt::Qml
        Qt::Test
    )
    install(TARGETS ${util_test}TestExec
        DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Utils"
    )
    add_lomiri_unittest(${util_test} ${util_test}TestExec ADD_TEST)

endforeach()

# plain qml test
add_lomiri_qmlunittest(. UtilsStyle)

# URLDispatcher test needs dbus-test-runner because it claims a dbus name
add_executable(URLDispatcherTestExec URLDispatcherTest.cpp)
target_link_libraries(URLDispatcherTestExec PRIVATE
    lomiriutils
    Qt::Core
    Qt::DBus
    Qt::Qml
    Qt::Test
)
install(TARGETS URLDispatcherTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Utils"
)
add_lomiri_unittest(URLDispatcher dbus-test-runner
    ARG_PREFIX "--parameter"
    ARGS --task $<TARGET_FILE:URLDispatcherTestExec>
)
