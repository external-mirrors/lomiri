# Some tests need to link this as a library while also including
# it as a QML module, so only build it as a single shared library.
add_library(gesturesplugin SHARED plugin.cpp)
qt_add_qml_module(gesturesplugin
    URI Lomiri.Gestures
    VERSION 0.1
    PLUGIN_TARGET gesturesplugin
    SOURCES
        AxisVelocityCalculator.cpp
        Direction.cpp
        MouseEventGenerator.cpp
        PressedOutsideNotifier.cpp
        TouchDispatcher.cpp
        TouchGate.cpp
        TouchGestureArea.cpp
)

target_include_directories(gesturesplugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(gesturesplugin PRIVATE LOMIRIGESTURESQML_LIBRARY)

target_link_libraries(gesturesplugin PRIVATE
    lomiri-gestures-private
    Qt::Core
    Qt::QmlPrivate
    Qt::Quick
    Qt::QuickPrivate
)

install_qml_module(gesturesplugin DESTINATION ${SHELL_INSTALL_QML})
