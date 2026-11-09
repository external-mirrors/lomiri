include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${liblomiri-private_SOURCE_DIR}
)

set(WINDOWMANAGER_SRC
    AvailableDesktopArea.cpp
    TopLevelWindowModel.cpp
    Window.cpp
    WindowManagerPlugin.cpp
    WindowMargins.cpp
    Screen.cpp
    ScreenAttached.cpp
    Screens.cpp
    ScreensConfiguration.cpp
    ScreenWindow.cpp
    WindowManagerObjects.cpp
    Workspace.cpp
    WorkspaceManager.cpp
    WorkspaceModel.cpp
    InputMethodManager.cpp
)

add_definitions(-DWINDOWMANAGERQML_LIBRARY)

add_library(windowmanager-qml SHARED ${WINDOWMANAGER_SRC})

target_link_libraries(windowmanager-qml
    PUBLIC
        lomiri-shell-application
        PkgConfig::QTMIRSERVER
    PRIVATE
        lomiri-private
        Qt::Gui
        Qt::GuiPrivate
        Qt::Qml
        Qt::Quick
)

if (WITH_MIR2)
    target_link_libraries(windowmanager-qml PRIVATE PkgConfig::MIROIL)
endif()

add_lomiri_plugin(WindowManager 1.0 WindowManager TARGETS windowmanager-qml)
