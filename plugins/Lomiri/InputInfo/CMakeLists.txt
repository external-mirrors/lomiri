# This is a temporary snapshot of the WIP QInputInfo API as we
# require this in lomiri now but upstream isn't finished yet.
# Eventually this should be dropped in favor of the upstream
# QInputInfo API.

set(InputInfo_SOURCES
    plugin.cpp
    qinputinfo.cpp
    qdeclarativeinputdevicemodel.cpp
    linux/qinputdeviceinfo_linux.cpp
)

add_library(InputInfo SHARED
    ${InputInfo_SOURCES}
)

target_include_directories(InputInfo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(InputInfo PRIVATE
    PkgConfig::LIBEVDEV
    PkgConfig::LIBUDEV
    Qt::Core
    Qt::Qml
    Qt::Quick
)

add_lomiri_plugin(Lomiri.InputInfo 0.1 Lomiri/InputInfo TARGETS InputInfo)
