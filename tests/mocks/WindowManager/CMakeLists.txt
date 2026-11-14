add_library(mockwindowmanagmentpolicy SHARED
    WindowManagementPolicy.cpp
)

target_link_libraries(mockwindowmanagmentpolicy
    PUBLIC
        lomiri-private
    PRIVATE
        PkgConfig::MIRAL
        Qt::Core
)

install(TARGETS mockwindowmanagmentpolicy
    DESTINATION ${SHELL_INSTALL_QML}/mocks/WindowManager
    )

qt_add_qml_module(mockwindowmanagerplugin
    URI WindowManager
    VERSION 1.0
    PLUGIN_TARGET mockwindowmanagerplugin
    SOURCES
        MockScreens.cpp
        MockScreensConfiguration.cpp
        MockScreenWindow.cpp
        WindowManagerPlugin.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/AvailableDesktopArea.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/InputMethodManager.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Screen.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/ScreenAttached.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Screens.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/ScreenWindow.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/TopLevelWindowModel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Window.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WindowManagerObjects.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WindowMargins.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Workspace.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WorkspaceManager.cpp
        ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WorkspaceModel.cpp
)

target_include_directories(mockwindowmanagerplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/WindowManager)

target_link_libraries(mockwindowmanagerplugin PRIVATE
    lomiri-private
    lomiri-shell-application
    mockwindowmanagmentpolicy
    PkgConfig::QTMIRSERVER
    Qt::Gui
    Qt::GuiPrivate
    Qt::Qml
    Qt::Quick
)

if (WITH_MIR2)
    target_link_libraries(mockwindowmanagerplugin PRIVATE PkgConfig::MIROIL)
endif()

install_qml_module(mockwindowmanagerplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
