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

set(WINDOWMANAGER_SRC
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/AvailableDesktopArea.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Screen.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/ScreenAttached.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Screens.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/ScreenWindow.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/TopLevelWindowModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Window.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WindowMargins.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WindowManagerObjects.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WorkspaceManager.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/WorkspaceModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/Workspace.cpp
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager/InputMethodManager.cpp
    MockScreens.cpp
    MockScreenWindow.cpp
    MockScreensConfiguration.cpp
    WindowManagerPlugin.cpp
)

add_library(MockWindowManager-qml SHARED ${WINDOWMANAGER_SRC})

target_include_directories(MockWindowManager-qml PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins/WindowManager
)

target_link_libraries(MockWindowManager-qml PRIVATE
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
    target_link_libraries(MockWindowManager-qml PRIVATE PkgConfig::MIROIL)
endif()
add_lomiri_mock(WindowManager 1.0 WindowManager TARGETS MockWindowManager-qml)
