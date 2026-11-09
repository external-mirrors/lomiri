include_directories(
    ${liblomiri-private_SOURCE_DIR}
)

set(FakeQtMirApplicationQml_SOURCES
    plugin.cpp
    ApplicationInfo.cpp
    ApplicationManager.cpp
    MirSurface.cpp
    MirSurfaceItem.cpp
    MirSurfaceListModel.cpp
    MirMock.cpp
    ObjectListModel.h
    SurfaceManager.cpp
    VirtualKeyboard.cpp
    resources/surfaces.qrc
)

add_library(FakeQtMirApplicationQml MODULE
    ${FakeQtMirApplicationQml_SOURCES}
)

target_link_libraries(FakeQtMirApplicationQml PRIVATE
    lomiri-shell-application
    mockwindowmanagmentpolicy
    PkgConfig::MIRAL
    Qt::Core
    Qt::DBus
    Qt::Quick
)

add_library(NonMirQtMirApplicationQml MODULE ${FakeQtMirApplicationQml_SOURCES})
set_target_properties(NonMirQtMirApplicationQml PROPERTIES OUTPUT_NAME FakeQtMirApplicationQml)

target_link_libraries(NonMirQtMirApplicationQml PRIVATE
    lomiri-shell-application
    mockwindowmanagmentpolicy
    PkgConfig::MIRAL
    Qt::Core
    Qt::DBus
    Qt::Quick
)

add_lomiri_mock(QtMir.Application 0.1 QtMir/Application TARGETS FakeQtMirApplicationQml)
add_lomiri_mock(QtMir.Application 0.1 QtMir/Application
                PREFIX nonmirplugins
                TARGETS NonMirQtMirApplicationQml
                BINARY_DIR ${CMAKE_BINARY_DIR}/nonmirplugins
                NO_TYPES)
