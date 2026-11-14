qt_add_qml_module(mockgsettingsplugin
    URI GSettings
    VERSION 1.0
    PLUGIN_TARGET mockgsettingsplugin
    SOURCES
        fake_gsettings.cpp
        plugin.cpp
)

target_link_libraries(mockgsettingsplugin PRIVATE
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(mockgsettingsplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
