qt_add_qml_module(mocknotificationsplugin
    URI Lomiri.Notifications
    VERSION 1.0
    PLUGIN_TARGET mocknotificationsplugin
    SOURCES
        MockActionModel.cpp
        MockNotification.cpp
        MockNotificationModel.cpp
        plugin.cpp
)

target_link_libraries(mocknotificationsplugin PRIVATE
    PkgConfig::NOTIFICATIONS_API
    Qt::Core
    Qt::Quick
)

install_qml_module(mocknotificationsplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
