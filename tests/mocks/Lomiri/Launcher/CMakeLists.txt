include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/
)

set(MockLauncherModel_SOURCES
    plugin.cpp
    MockLauncherModel.cpp
    MockLauncherItem.cpp
    MockQuickListModel.cpp
    MockAppDrawerModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/applicationsfiltermodel.cpp
)

add_library(MockLauncherPlugin MODULE ${MockLauncherModel_SOURCES})

target_link_libraries(MockLauncherPlugin PRIVATE
    lomiri-shell-application
    lomiri-shell-launcher
    Qt::Core
    Qt::Quick
)

add_lomiri_mock(Lomiri.Launcher 0.1 Lomiri/Launcher TARGETS MockLauncherPlugin)
