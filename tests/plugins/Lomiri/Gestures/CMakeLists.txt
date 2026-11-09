include(QmlTest)

include_directories(
    SYSTEM
    ${LOMIRIGESTURES_INCLUDEDIR}/LomiriGestures/${LOMIRIGESTURES_VERSION}
)

include_directories(
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/Gestures
    ${CMAKE_CURRENT_BINARY_DIR}
    )

macro(build_gesture_test CLASSNAME)
    add_executable(${CLASSNAME}TestExec tst_${CLASSNAME}.cpp GestureTest.cpp TestItem.cpp)
    target_link_libraries(${CLASSNAME}TestExec PRIVATE
        LomiriGesturesQml
        PkgConfig::LOMIRIGESTURES
        Qt::Core
        Qt::Gui
        Qt::GuiPrivate
        Qt::Qml
        Qt::Quick
        Qt::QuickPrivate
        Qt::Test
    )
    install(TARGETS ${CLASSNAME}TestExec
        DESTINATION "${SHELL_PRIVATE_FULL_LIBEXECDIR}/tests/plugins/Lomiri/Gestures"
    )
    # To find libLomiriGestures.so
    set_target_properties(${CLASSNAME}TestExec PROPERTIES INSTALL_RPATH "${SHELL_PRIVATE_FULL_LIBDIR}")
endmacro()

set(LOMIRI_IMPORT_PATHS
    ${CMAKE_BINARY_DIR}/tests/utils/modules
    ${LOMIRI_PLUGINPATH}
)

macro(add_gesture_unit_test CLASSNAME)
    build_gesture_test(${CLASSNAME})
    add_lomiri_unittest(${CLASSNAME} ${CLASSNAME}TestExec
        ENVIRONMENT LD_LIBRARY_PATH=${LOMIRI_PLUGINPATH}/Lomiri/Gestures
        ${ARGN}
    )
endmacro()

macro(add_gesture_ui_test CLASSNAME)
    build_gesture_test(${CLASSNAME})
    add_lomiri_uitest(${CLASSNAME} ${CLASSNAME}TestExec
        ENVIRONMENT LD_LIBRARY_PATH=${LOMIRI_PLUGINPATH}/Lomiri/Gestures
        ${ARGN}
    )
    add_manual_qml_test(. ${CLASSNAME} IMPORT_PATHS ${LOMIRI_IMPORT_PATHS})
endmacro()

add_qml_test_data(. empty.qml)
add_qml_test_data(. touchGateExample.qml)

add_gesture_ui_test(FloatingFlickable)
add_gesture_ui_test(PressedOutsideNotifier)
add_gesture_ui_test(TouchDispatcher)
add_gesture_ui_test(TouchGate)
add_gesture_unit_test(AxisVelocityCalculator)
add_gesture_ui_test(TouchGestureArea)
