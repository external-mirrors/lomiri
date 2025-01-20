pkg_search_module(GD3 REQUIRED gnome-desktop-3.0)

include_directories(SYSTEM ${GD3_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${GEONAMES_INCLUDE_DIRS})

add_library(Wizard-qml MODULE
    plugin.cpp
    PageList.cpp
    System.cpp
    LocalePlugin.cpp
    timezonemodel.cpp
    Status.cpp
    keyboardLayoutsModel.cpp
    Changelog.cpp
)

target_link_libraries(Wizard-qml
    Qt5::DBus Qt5::Qml
    ${GD3_LDFLAGS} ${GLIB_LDFLAGS} ${GEONAMES_LDFLAGS}
)

if (NOT "${DISPLAYED_DISTRO_NAME}" STREQUAL "")
    target_compile_definitions(Wizard-qml PRIVATE
        -DLOMIRI_DISPLAYED_DISTRO_NAME="${DISPLAYED_DISTRO_NAME}")
endif ()

add_lomiri_plugin(Wizard 0.1 Wizard TARGETS Wizard-qml)

install(FILES 50-com.lomiri.wizard.rules DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/polkit-1/rules.d")
