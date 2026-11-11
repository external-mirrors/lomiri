set(MockNotificationsPlugin_SOURCES
    plugin.cpp
    MockNotification.cpp
    MockNotificationModel.cpp
    MockActionModel.cpp
)

add_library(MockNotificationsPlugin MODULE ${MockNotificationsPlugin_SOURCES})

target_link_libraries(MockNotificationsPlugin PRIVATE
    PkgConfig::NOTIFICATIONS_API
    Qt::Core
    Qt::Quick
)

add_lomiri_mock(Lomiri.Notifications 1.0 Lomiri/Notifications TARGETS MockNotificationsPlugin)
