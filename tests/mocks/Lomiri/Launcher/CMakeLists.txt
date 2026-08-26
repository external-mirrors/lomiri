include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Launcher/
)

set(MockLauncherModel_SOURCES
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationManagerInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/launcher/LauncherItemInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/launcher/LauncherModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/launcher/QuickListModelInterface.h
    ${CMAKE_SOURCE_DIR}/include/lomiri/shell/launcher/AppDrawerModelInterface.h
    plugin.cpp
    MockLauncherModel.cpp
    MockLauncherItem.cpp
    MockQuickListModel.cpp
    MockAppDrawerModel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/applicationsfiltermodel.cpp
)

add_library(MockLauncherPlugin MODULE ${MockLauncherModel_SOURCES})

target_link_libraries(MockLauncherPlugin Qt5::Core Qt5::Quick)

add_lomiri_mock(Lomiri.Launcher 0.1 Lomiri/Launcher TARGETS MockLauncherPlugin)
