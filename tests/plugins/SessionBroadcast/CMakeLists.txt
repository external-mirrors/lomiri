macro(make_dbus_class NAME INTERFACE)
    if(${CMAKE_CURRENT_SOURCE_DIR}/interfaces.xml IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor.h)
        execute_process(COMMAND ${QDBUSXML2CPP_EXECUTABLE} -c ${NAME}Adaptor -a ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor ${CMAKE_CURRENT_SOURCE_DIR}/interfaces.xml ${INTERFACE})
    endif()
endmacro(make_dbus_class)

make_dbus_class(Broadcast com.lomiri.Shell.Greeter.Broadcast)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/SessionBroadcast
)

add_executable(MockBroadcastServer
    ${CMAKE_CURRENT_BINARY_DIR}/BroadcastAdaptor.cpp
    server.cpp
    BroadcastServer.cpp
)

target_link_libraries(MockBroadcastServer PRIVATE Qt::Core Qt::DBus)

install(TARGETS MockBroadcastServer
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/SessionBroadcast"
)

### SessionBroadcastTest
add_executable(sessionbroadcasttestExec
    ${CMAKE_SOURCE_DIR}/plugins/SessionBroadcast/SessionBroadcast.cpp
    sessionbroadcasttest.cpp
)

target_link_libraries(sessionbroadcasttestExec PRIVATE
    PkgConfig::GLIB
    Qt::Core
    Qt::DBus
    Qt::Qml
    Qt::Test
)

install(TARGETS sessionbroadcasttestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/SessionBroadcast"
)

add_lomiri_unittest(SessionBroadcast dbus-test-runner
    ARG_PREFIX "--parameter"
    ARGS
        --bus-type both
        --task $<TARGET_FILE:MockBroadcastServer>
        --task-name server
        --ignore-return
        --task $<TARGET_FILE:sessionbroadcasttestExec>
        --task-name client
        --wait-for com.lomiri.Shell.Greeter.Broadcast
)
