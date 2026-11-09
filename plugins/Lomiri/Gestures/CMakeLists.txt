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

target_link_libraries(LomiriGesturesQml PRIVATE
    PkgConfig::LOMIRIGESTURES
    Qt::Core
    Qt::QmlPrivate
    Qt::Quick
    Qt::QuickPrivate
)

# So that Foo.cpp can #include "Foo.moc"
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(
    SYSTEM
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)

add_lomiri_plugin(Lomiri.Gestures 0.1 Lomiri/Gestures TARGETS LomiriGesturesQml)
