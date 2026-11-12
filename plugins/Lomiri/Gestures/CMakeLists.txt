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

add_library(LomiriGesturesQml SHARED ${LomiriGesturesQml_SOURCES})

target_compile_definitions(LomiriGesturesQml PRIVATE LOMIRIGESTURESQML_LIBRARY)

target_link_libraries(LomiriGesturesQml PRIVATE
    lomiri-gestures-private
    Qt::Core
    Qt::QmlPrivate
    Qt::Quick
    Qt::QuickPrivate
)

add_lomiri_plugin(Lomiri.Gestures 0.1 Lomiri/Gestures TARGETS LomiriGesturesQml)
