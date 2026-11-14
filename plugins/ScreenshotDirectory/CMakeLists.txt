qt_add_qml_module(screenshotdirectoryplugin
    URI ScreenshotDirectory
    VERSION 0.1
    PLUGIN_TARGET screenshotdirectoryplugin
    SOURCES
        plugin.cpp
        ScreenshotDirectory.cpp
)

target_link_libraries(screenshotdirectoryplugin PRIVATE Qt::Gui Qt::Qml Qt::Quick)

install_qml_module(screenshotdirectoryplugin DESTINATION ${SHELL_INSTALL_QML})
