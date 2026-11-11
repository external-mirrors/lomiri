set(applicationMenu_SRCS
    applicationmenuregistry.cpp
    dbusapplicationmenuregistry.cpp
    plugin.cpp)

qt5_add_dbus_adaptor(applicationMenu_SRCS com.lomiri.MenuRegistrar.xml dbusapplicationmenuregistry.h DBusApplicationMenuRegistry)

add_library(ApplicationMenu-qml MODULE ${applicationMenu_SRCS})

target_include_directories(ApplicationMenu-qml PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(ApplicationMenu-qml PRIVATE Qt::DBus Qt::Qml)

add_lomiri_plugin(Lomiri.ApplicationMenu 0.1 Lomiri/ApplicationMenu TARGETS ApplicationMenu-qml)
