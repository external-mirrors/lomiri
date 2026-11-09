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

target_link_libraries(Wizard-qml PRIVATE
    PkgConfig::GD4
    PkgConfig::GEONAMES
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

if (NOT "${DISPLAYED_DISTRO_NAME}" STREQUAL "")
    target_compile_definitions(Wizard-qml PRIVATE
        -DLOMIRI_DISPLAYED_DISTRO_NAME="${DISPLAYED_DISTRO_NAME}")
endif ()

add_lomiri_plugin(Wizard 0.1 Wizard TARGETS Wizard-qml)

install(FILES 50-com.lomiri.wizard.rules DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/polkit-1/rules.d")
