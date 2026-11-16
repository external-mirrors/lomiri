qt_add_qml_module(wizardplugin
    URI Wizard
    VERSION 0.1
    PLUGIN_TARGET wizardplugin
    SOURCES
        Changelog.cpp
        keyboardLayoutsModel.cpp
        LocalePlugin.cpp
        PageList.cpp
        plugin.cpp
        Status.cpp
        System.cpp
        timezonemodel.cpp
)

target_link_libraries(wizardplugin PRIVATE
    lomiri-paths
    PkgConfig::GD4
    PkgConfig::GEONAMES
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

if (NOT "${DISPLAYED_DISTRO_NAME}" STREQUAL "")
    target_compile_definitions(wizardplugin PRIVATE
        -DLOMIRI_DISPLAYED_DISTRO_NAME="${DISPLAYED_DISTRO_NAME}")
endif ()

install_qml_module(wizardplugin DESTINATION ${SHELL_INSTALL_QML})

install(FILES 50-com.lomiri.wizard.rules DESTINATION "${CMAKE_INSTALL_DATADIR}/polkit-1/rules.d")
