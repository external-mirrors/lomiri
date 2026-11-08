# in order to include Qt's private headers
remove_definitions(-DQT_NO_KEYWORDS)

set(LomiriGesturesQml_SOURCES
    plugin.cpp
    AxisVelocityCalculator.cpp
    Direction.cpp
    MouseEventGenerator.cpp
    PressedOutsideNotifier.cpp
    TouchDispatcher.cpp
    TouchGate.cpp
    TouchGestureArea.cpp
)

add_definitions(-DLOMIRIGESTURESQML_LIBRARY)

add_library(LomiriGesturesQml SHARED ${LomiriGesturesQml_SOURCES})
target_link_libraries(LomiriGesturesQml ${LOMIRIGESTURES_LIBRARIES} Qt5::Core Qt5::Quick)

# So that Foo.cpp can #include "Foo.moc"
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(
    SYSTEM
    ${LOMIRIGESTURES_INCLUDE_DIRS}
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)

include_directories(
    SYSTEM
    ${Qt5Qml_PRIVATE_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
)

add_lomiri_plugin(Lomiri.Gestures 0.1 Lomiri/Gestures TARGETS LomiriGesturesQml)
