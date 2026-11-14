qt_add_qml_module(mockwizardplugin
    URI Wizard
    VERSION 0.1
    PLUGIN_TARGET mockwizardplugin
    SOURCES
        mockplugin.cpp
        MockSystem.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Wizard/Changelog.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Wizard/keyboardLayoutsModel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Wizard/LocalePlugin.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Wizard/PageList.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Wizard/Status.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Wizard/timezonemodel.cpp
)

target_include_directories(mockwizardplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Wizard)

target_link_libraries(mockwizardplugin PRIVATE
    lomiri-paths
    PkgConfig::GD4
    PkgConfig::GEONAMES
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

install_qml_module(mockwizardplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
