# Some tests need to link this as a library while also including
# it as a QML module, so only build it as a single shared library.
add_library(globalshortcutplugin SHARED plugin.cpp)
qt_add_qml_module(globalshortcutplugin
    URI GlobalShortcut
    VERSION 1.0
    PLUGIN_TARGET globalshortcutplugin
    SOURCES
        globalshortcut.cpp
        globalshortcutregistry.cpp
)

target_include_directories(globalshortcutplugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(globalshortcutplugin PRIVATE Qt::Gui Qt::Quick)

install_qml_module(globalshortcutplugin DESTINATION ${SHELL_INSTALL_QML})
