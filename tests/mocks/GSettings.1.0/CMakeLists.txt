include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(GSettingsQML_SOURCES
  fake_gsettings.cpp
  plugin.cpp
)

add_library(FakeGSettingsQml MODULE ${GSettingsQML_SOURCES})

target_link_libraries(FakeGSettingsQml PRIVATE
    Qt::Core
    Qt::Qml
    Qt::Quick
)

add_lomiri_mock(GSettings 1.0 GSettings.1.0 TARGETS FakeGSettingsQml)
