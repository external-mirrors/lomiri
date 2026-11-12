pkg_get_variable(LOMIRI_SYSTEM_SETTINGS_PRIVATE_PLUGINDIR LomiriSystemSettings plugin_private_module_dir)
if(LOMIRI_SYSTEM_SETTINGS_PRIVATE_PLUGINDIR STREQUAL "")
    message(FATAL_ERROR "Could not determine LomiriSystemSettings private plugin installation dir.")
endif()

configure_file(paths.h.in ${CMAKE_CURRENT_BINARY_DIR}/paths.h @ONLY)
add_library(lomiri-paths INTERFACE)
target_include_directories(lomiri-paths INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SHELL_APP_HDRS CONFIGURE_DEPENDS
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/*.h
)
add_library(lomiri-shell-application OBJECT ${SHELL_APP_HDRS})
target_link_libraries(lomiri-shell-application PUBLIC
    PkgConfig::APPLICATION_API
    Qt::Core
    Qt::Gui
    Qt::Quick
)

file(GLOB SHELL_LAUNCHER_HDRS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/lomiri/shell/launcher/*.h
)
add_library(lomiri-shell-launcher OBJECT ${SHELL_LAUNCHER_HDRS})
target_include_directories(lomiri-shell-launcher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lomiri-shell-launcher PUBLIC lomiri-shell-application)
