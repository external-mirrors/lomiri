qt_add_qml_module(mocksecurityprivacyplugin
    URI Lomiri.SystemSettings.SecurityPrivacy
    VERSION 1.0
    PLUGIN_TARGET mocksecurityprivacyplugin
    SOURCES
        MockSecurityPrivacy.cpp
        plugin.cpp
)

target_link_libraries(mocksecurityprivacyplugin PRIVATE
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(mocksecurityprivacyplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
