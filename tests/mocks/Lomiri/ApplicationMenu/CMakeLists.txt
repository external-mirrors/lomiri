qt_add_qml_module(mockapplicationmenuplugin
    URI Lomiri.ApplicationMenu
    VERSION 1.0
    PLUGIN_TARGET mockapplicationmenuplugin
    SOURCES
        mockapplicationmenuregistry.cpp
        plugin.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/ApplicationMenu/applicationmenuregistry.cpp
)

target_include_directories(mockapplicationmenuplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Lomiri/ApplicationMenu)

target_link_libraries(mockapplicationmenuplugin PRIVATE Qt::DBus Qt::Qml)

install_qml_module(mockapplicationmenuplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
