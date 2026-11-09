
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Platform
)

add_executable(platformtest
    platformtest.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Platform/platform.cpp
    )

target_link_libraries(platformtest PRIVATE
    PkgConfig::QTDBUSTEST
    Qt::Core
    Qt::DBus
    Qt::Test
)


install(TARGETS platformtest
    DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Lomiri/Platform"
)

add_lomiri_unittest(Platform qdbus-simple-test-runner
    ARGS $<TARGET_FILE:platformtest>
    )
