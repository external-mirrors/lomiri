# TODO: This is a copy of the plugin in plugins/Lomiri/InputInfo which in
# turn is a copy of the WIP upstream InputInfo API. This needs to be updated
# and brought in sync if our snapshot is updated.
# Long term goal is to merge the InputInfo API upstream.

add_definitions(-DLOMIRI_MOCKS)

set(MockInputInfo_SOURCES
    plugin.cpp
    qinputdeviceinfo_mock.cpp
    mockcontroller.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/InputInfo/qinputinfo.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/InputInfo/qdeclarativeinputdevicemodel.cpp
)

add_library(MockInputInfo SHARED
    ${MockInputInfo_SOURCES}
)

target_include_directories(MockInputInfo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/InputInfo
)

target_link_libraries(MockInputInfo PRIVATE
    lomiri-paths
    Qt::Core
    Qt::Qml
    Qt::Quick
)

add_lomiri_mock(Lomiri.InputInfo 0.1 Lomiri/InputInfo TARGETS MockInputInfo)
