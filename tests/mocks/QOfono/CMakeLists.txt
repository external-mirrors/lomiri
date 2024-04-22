set(MOCK_QOFONO_SOURCES
    plugin.cpp
    MockQOfono.cpp
    MockQOfonoManager.cpp
)

add_library(MockQOfono MODULE ${MOCK_QOFONO_SOURCES})

target_link_libraries(MockQOfono Qt5::Qml Qt5::Quick Qt5::Core)

add_lomiri_mock(QOfono 0.2 QOfono TARGETS MockQOfono)
