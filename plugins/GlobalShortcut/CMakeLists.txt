set(globalshortcutplugin_SRCS
    globalshortcut.cpp
    globalshortcutregistry.cpp
    plugin.cpp)

add_library(GlobalShortcut-qml SHARED ${globalshortcutplugin_SRCS})

target_link_libraries(GlobalShortcut-qml PRIVATE Qt::Quick Qt::Gui)

add_lomiri_plugin(GlobalShortcut 1.0 GlobalShortcut TARGETS GlobalShortcut-qml)
