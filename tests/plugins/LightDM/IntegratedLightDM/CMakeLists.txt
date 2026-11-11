add_executable(GreeterDBusTestExec
    dbus.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/Greeter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/PromptsModel.cpp
    )

target_link_libraries(GreeterDBusTestExec PRIVATE
    lomiri-paths
    MockLightDM
    Intl::Intl
    Qt::Core
    Qt::DBus
    Qt::Quick
    Qt::Test
)

target_include_directories(GreeterDBusTestExec PUBLIC
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
    )
install(TARGETS GreeterDBusTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
install(FILES greeter.qml
    DESTINATION "${SHELL_APP_FULL_DIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
add_lomiri_uitest(GreeterDBus dbus-test-runner
    ARG_PREFIX "--parameter"
    ARGS --task $<TARGET_FILE:GreeterDBusTestExec>
    DEPENDS MockLightDM
    )

add_executable(GreeterPamTestExec
    pam.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/IntegratedLightDM/liblightdm/GreeterPrivate.cpp
    )

target_link_libraries(GreeterPamTestExec PRIVATE
    integratedLightDM
    PkgConfig::GLIB
    Qt::Concurrent
    Qt::Core
    Qt::Test
)

target_include_directories(GreeterPamTestExec PUBLIC
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/IntegratedLightDM
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/IntegratedLightDM/liblightdm
    )
install(TARGETS GreeterPamTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
add_qmltest_target(testGreeterPam GreeterPamTestExec COMMAND $<TARGET_FILE:GreeterPamTestExec>)

# SessionsModelTest
add_executable(GreeterSessionsModelTestExec
    sessionsmodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/SessionsModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
    )

target_link_libraries(GreeterSessionsModelTestExec PRIVATE
    MockLightDM
    Qt::Core
    Qt::Test
)

target_include_directories(GreeterSessionsModelTestExec PUBLIC
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
    ${CMAKE_SOURCE_DIR}/plugins/Utils
    )
install(TARGETS GreeterSessionsModelTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
add_lomiri_uitest(GreeterSessions GreeterSessionsModelTestExec
    DEPENDS MockLightDM
    )

# UsersModelTest
add_executable(GreeterUsersModelTestExec
    usersmodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/Greeter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/PromptsModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/UsersModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
    )

target_link_libraries(GreeterUsersModelTestExec PRIVATE
    MockLightDM
    Intl::Intl
    Qt::Core
    Qt::Test
)

target_include_directories(GreeterUsersModelTestExec PUBLIC
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
    ${CMAKE_SOURCE_DIR}/plugins/Utils
    ${CMAKE_SOURCE_DIR}/tests/mocks/liblightdm
    )
install(TARGETS GreeterUsersModelTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
add_lomiri_uitest(GreeterUsers GreeterUsersModelTestExec
    DEPENDS MockLightDM
    )

# PromptsModelTest
add_executable(GreeterPromptsModelTestExec
    promptsmodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/Greeter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/PromptsModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
    )

target_link_libraries(GreeterPromptsModelTestExec PRIVATE
    MockLightDM
    Intl::Intl
    Qt::Core
    Qt::Test
)

target_include_directories(GreeterPromptsModelTestExec PUBLIC
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
    ${CMAKE_SOURCE_DIR}/plugins/Utils
    ${CMAKE_SOURCE_DIR}/tests/mocks/liblightdm
    )
install(TARGETS GreeterPromptsModelTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
add_lomiri_uitest(GreeterPrompts GreeterPromptsModelTestExec
    DEPENDS MockLightDM
    )

# IntegratedTest
add_executable(GreeterIntegratedTestExec
    integrated.cpp
    )

target_link_libraries(GreeterIntegratedTestExec PRIVATE
    integratedLightDM
    PkgConfig::GLIB
    Qt::Core
    Qt::DBus
    Qt::Quick
    Qt::Test
)

target_include_directories(GreeterIntegratedTestExec PUBLIC
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/IntegratedLightDM/liblightdm
    )
install(TARGETS GreeterIntegratedTestExec
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/LightDM/IntegratedLightDM"
    )
add_lomiri_unittest(GreeterIntegrated dbus-test-runner
    ARG_PREFIX "--parameter"
    ARGS
        --bus-type both
        --task $<TARGET_FILE:mock-server>
        --task-name server
        --ignore-return
        --task $<TARGET_FILE:GreeterIntegratedTestExec>
        --task-name client
        --wait-for org.freedesktop.Accounts
    DEPENDS integratedLightDM
    )
