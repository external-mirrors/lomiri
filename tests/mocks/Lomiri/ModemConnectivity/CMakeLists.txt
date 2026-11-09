set(MOCK_MODEMCONNECTIVITY_SOURCES
    plugin.cpp
    MockModemConnectivity.cpp
)

add_library(MockModemConnectivity MODULE ${MOCK_MODEMCONNECTIVITY_SOURCES})

target_link_libraries(MockModemConnectivity PRIVATE Qt::Qml Qt::Quick Qt::Core)

add_lomiri_mock(Lomiri.ModemConnectivity 0.1 Lomiri/ModemConnectivity TARGETS MockModemConnectivity)
