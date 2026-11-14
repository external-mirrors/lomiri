add_subdirectory(3rd_party)

qt_add_qml_module(cursorplugin
    URI Cursor
    VERSION 1.1
    PLUGIN_TARGET cursorplugin
    SOURCES
        CursorImageInfo.cpp
        CursorImageProvider.cpp
        InputDispatcherFilter.cpp
        MousePointer.cpp
        plugin.cpp
    QML_FILES
        Cursor.qml
)

target_link_libraries(cursorplugin PRIVATE
    lomiri-shell-application
    xcursorloader-static
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::Svg
)

install_qml_module(cursorplugin DESTINATION ${SHELL_INSTALL_QML})
