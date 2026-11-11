add_library(MockWizard-qml MODULE
    mockplugin.cpp
    MockSystem.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/Changelog.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/PageList.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/timezonemodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/LocalePlugin.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/Status.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Wizard/keyboardLayoutsModel.cpp
)

target_include_directories(MockWizard-qml PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins/Wizard
)

target_link_libraries(MockWizard-qml PRIVATE
    lomiri-paths
    PkgConfig::GD4
    PkgConfig::GEONAMES
    PkgConfig::GLIB
    Qt::DBus
    Qt::Qml
)

add_lomiri_mock(Wizard 0.1 Wizard TARGETS MockWizard-qml)
