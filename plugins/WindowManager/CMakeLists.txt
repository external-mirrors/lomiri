add_library(windowmanagerplugin MODULE WindowManagerPlugin.cpp)
qt_add_qml_module(windowmanager STATIC
    URI WindowManager
    VERSION 1.0
    PLUGIN_TARGET windowmanagerplugin
    SOURCES
        AvailableDesktopArea.cpp
        InputMethodManager.cpp
        Screen.cpp
        ScreenAttached.cpp
        Screens.cpp
        ScreensConfiguration.cpp
        ScreenWindow.cpp
        TopLevelWindowModel.cpp
        Window.cpp
        WindowManagerObjects.cpp
        WindowMargins.cpp
        Workspace.cpp
        WorkspaceManager.cpp
        WorkspaceModel.cpp
)

target_include_directories(windowmanager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(windowmanager PRIVATE WINDOWMANAGERQML_LIBRARY)

target_link_libraries(windowmanager
    PUBLIC
        lomiri-shell-application
        PkgConfig::QTMIRSERVER
        Qt::Gui
        Qt::Qml
        Qt::Quick
    PRIVATE
        lomiri-private
        Qt::GuiPrivate
)

if (WITH_MIR2)
    target_link_libraries(windowmanager PRIVATE PkgConfig::MIROIL)
endif()

install_qml_module(windowmanager DESTINATION ${SHELL_INSTALL_QML})
