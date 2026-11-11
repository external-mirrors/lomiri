add_subdirectory(3rd_party)

set(QMLPLUGIN_SRC
    plugin.cpp
    CursorImageInfo.cpp
    CursorImageProvider.cpp
    MousePointer.cpp
    InputDispatcherFilter.cpp
    )

add_library(Cursor-qml SHARED
    ${QMLPLUGIN_SRC}
    )

target_link_libraries(Cursor-qml PRIVATE
    lomiri-shell-application
    xcursorloader-static
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
    Qt::Svg
)

add_lomiri_plugin(Cursor 1.1 Cursor TARGETS Cursor-qml)
