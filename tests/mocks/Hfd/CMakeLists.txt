add_library(MockHfd-qml MODULE
    plugin.cpp
    Leds.cpp
    )

target_link_libraries(MockHfd-qml PRIVATE Qt::Qml Qt::Gui)

add_lomiri_mock(Hfd 0.1 Hfd TARGETS MockHfd-qml)
